#include "tablescene.h"

#include <stdexcept>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QThread>
#include <time.h>
#include "powerup.h"
#include "ballpowerbonus.h"
#include "ballsizebonus.h"
#include "extralife.h"

/*!
 * \brief TableScene constructor
 *
 * \param width width of table
 * \param height height of table
 * \param bgColour QColor background colour of table
 * \param minWidth minimum width of the table (if resizable)
 * \param minHeight minimum height of the table (if resizable)
 * \param maxWidth maximum width of the table (if resizable)
 * \param maxHeight maximum height of the table (if resizable)
 * \param resizable indicates whether the table window is resizable
 *
 */
TableScene::TableScene(int width, int height,
                       QColor bgColour, bool playGame) :
    QGraphicsScene(0, 0, width, height),
    m_view(this),
    m_playGame(playGame)
{
    this->setBackgroundBrush(QBrush(bgColour));

    // connect the timer for animation
    QObject::connect(&m_timer, SIGNAL(timeout()), this, SLOT(advance()));

    m_view.setRenderHint(QPainter::Antialiasing);


    if (m_playGame){
        QApplication::setOverrideCursor(Qt::BlankCursor);
        m_view.setMouseTracking(true);
    }
}

//! TableScene destructor
TableScene::~TableScene() {
    delete m_table_instance;
}

/*!
 * \brief Start the timer with the provided framerate
 * \param framerate
 */
void TableScene::startAnimation (int framerate) {
    m_timer.start(1000/framerate);
}

//! Stop the timer
void TableScene::stopAnimation () {
    m_timer.stop();
}

//! Restart the timer
void TableScene::restartAnimation () {
    m_timer.start();
}

//! Toggles the timer
void TableScene::toggleAnimation () {
    if (this->m_timer.isActive()) {
        this->stopAnimation();
    } else {
        this->restartAnimation();
    }
}

/*!
 * \brief Overidden keyPressEvent to handle animation toggle
 * \param e
 */
void TableScene::keyPressEvent (QKeyEvent *e) {

    if ((e->key() == Qt::Key_Space)){
        this->toggleAnimation();
    }
}

/*!
 * \brief Handles mouse movement events. This method controls the paddle's movement.
 *
 * \return void
 */
void TableScene::mouseMoveEvent(QGraphicsSceneMouseEvent *e){
    if (m_playGame){
        // move the paddle
        Paddle * paddle = this->getPaddle();
        qreal paddleWidth = paddle->boundingRect().width();
        qreal paddleY = paddle->pos().y();
        qreal mouseX = e->scenePos().x();

        qreal newPaddleX = mouseX - paddleWidth/2;

        if (newPaddleX < 0)
            paddle->setX(0);
        else if (newPaddleX > this->width()-paddleWidth)
            paddle->setX(this->width()-paddleWidth);
        else
            paddle->setPos(mouseX - paddleWidth/2, paddleY);


    }
}

/*!
 * \brief Handles mouse press events. This method controls the launching of the ball.
 *
 * \return void
 */
void TableScene::mousePressEvent(QGraphicsSceneMouseEvent *e) {
    if (m_playGame) {
        if (!m_player->getRoundStarted()) {
            m_ball->setYVelocity(-5);
            m_player->setRoundStarted(true);
        }
    }
}

/*!
 * \brief Adds the ball to the scene
 *
 * A wrapper for addItem that additionally keeps track of the ball pointer
 * for easy reference.
 *
 * Transfers ownership of the ball to the table.
 *
 *
 *
 * \param Ball pointer to the ball
 */
TableScene & TableScene::addBall(Ball *ball){
    this->addItem(ball);
    m_ball = ball;

    if (ball->collidingItems().size() > 0) {
        throw std::runtime_error("Ball is overlapping another object");
    }

    if (ball->coordinate().x() < 0
            || ball->coordinate().x() + ball->getRadius()*2 > this->width()
            || ball->coordinate().y() < 0
            || ball->coordinate().y() + ball->getRadius()*2 > this->height()) {
        throw std::runtime_error("Ball is outside box.");
    }

    return *this;
}

//! Getter for ball
Ball * TableScene::getBall() {
    return m_ball;
}

/*!
 * \brief Getter for the single table instance.
 *
 * If the table doesn't yet exist, this method creates it. Otherwise
 * it raises an exception.
 *
 * \param width width of table
 * \param height height of table
 * \param bgColour QColor background colour of table
 *
 * \return the table instance
 *
 *
 *
 *
 */
TableScene * TableScene::instance(int width, int height,
                                 QColor bgColour, bool playGame)
{
    if (m_table_instance == 0) {
        m_table_instance = new TableScene(width, height,
                                          bgColour, playGame);
        return m_table_instance;
    }

    throw std::logic_error("Attempted to create a second instance of Table. Only a single instance is allowed of this class.");

}

//! Initialise static instance variable
TableScene * TableScene::m_table_instance = 0;

//! Getter for the TableView of the table
QGraphicsView & TableScene::view() {
    return m_view;
}

/*!
 * \brief Adds the brick to the scene
 *
 * A wrapper for addItem that additionally keeps track of the brick pointers
 * for easy reference.
 *
 * Transfers ownership of the brick to the table.
 *
 * Bricks that overlap with existing objects are abandoned
 *
 * \param Brick pointer to the brick
 */
TableScene & TableScene::addBrick(Brick *brick) {

    m_bricks.push_back(brick);
    this->addItem(brick);


    if (brick->collidingItems().size() > 0 && !m_playGame) {
        this->removeItem(brick);
        delete brick;
    }


    return *this;
}

/*!
 * \brief Gets the vector of Brick pointers
 *
 * \return TableScene for chaining
 */
std::vector<Brick *> & TableScene::getBricks()  {
    return m_bricks;
}

/*!
 * \brief Removes the brick from the scene.
 *
 * Removes the brick from the scene and if it was the last brick and the game is on,
 * generate the next level.
 *
 * \param brick which is the brick to be deleted.
 * \return Updated TableScene
 */
TableScene & TableScene::removeBrick(Brick *brick) {

    this->removeItem(brick);

    std::vector<Brick *>::iterator idx = std::find(m_bricks.begin(), m_bricks.end(), brick);

    if (idx != m_bricks.end()) {
        m_bricks.erase(idx);
    }

    delete brick;

    if (m_bricks.size() == 0 && m_player->getLevelGen()) {
        // level completed

        m_ball->setXVelocity(0);
        m_ball->setYVelocity(0);
        m_player->setRoundStarted(false);
        resetPowerUps();
        generateLevel();

        std::stringstream ss;
        ss << "Level: " << m_player->increaseCurrentLevel();
        OverlayObject * levelOverlay = getOverlayObjects().at(1);
        levelOverlay->setText(QString::fromStdString(ss.str()));
        levelOverlay->update();

    }

    return *this;
}

//! adder for OverlayObjects
TableScene & TableScene::addOverlayObject(OverlayObject *overlay) {
    m_overlays.push_back(overlay);
    this->addItem(overlay);

    return *this;
}

//! getter for OverlayObjects
std::vector<OverlayObject *> & TableScene::getOverlayObjects() {
    return m_overlays;
}

//! mutator for overlays
void TableScene::updateOverlay(int index, QString text) {
    OverlayObject * livesOverlay = m_overlays.at(index);

    livesOverlay->setText(text);
    livesOverlay->update();
}

//! Adder for Paddle objects
TableScene & TableScene::addPaddle(Paddle *paddle){
    m_paddle = paddle;
    this->addItem(paddle);

    return *this;
}

//! Getter for ball
Paddle * TableScene::getPaddle() {
    return m_paddle;
}

//! Getter for the playGame bool
bool TableScene::getPlayGame() {
    return m_playGame;
}

//! Setter for player member variable
void TableScene::setPlayer(Player *player) {
    m_player = player;
}

//! Getter for the player
Player * TableScene::getPlayer() {
    return m_player;
}

/*!
 * \brief Generate next level using the LevelGenerator
 */
void TableScene::generateLevel() {
    LevelGenerator lvlGen(this->width(), this->height());

    std::vector<Brick *> levelBricks = lvlGen.generate(m_player->getCurrentLevel());

    for (int i = 0; i < levelBricks.size(); i++) {
        this->addBrick(levelBricks[i]);
    }

}

/*!
 * \brief Restarts the game.
 *
 * This is called when the player wants to play again.
 * All the player stats are reset to initial values and the game will start from the begin.
 * Bricks will be cleared and a new level will be generated.
 *
 */
void TableScene::restartGame() {

    m_player->resetStats();
    resetPowerUps();

    for (int i = 0; i < m_overlays.size(); i++) {
        m_overlays.at(i)->restoreDefaultText();
    }

    this->removeItem(m_ball);
    qreal startBallX = m_paddle->boundingRect().right() + m_paddle->boundingRect().width()/2 - m_ball->getRadius();
    qreal startBallY = m_paddle->boundingRect().top() - m_ball->getRadius()*2 - 1;

    m_ball->setCoordinate(QPointF(startBallX, startBallY));
    this->addItem(m_ball);

    for (int i = 0; i < m_bricks.size(); i++) {
        delete m_bricks[i];
    }

    m_bricks.clear();

    generateLevel();

    m_ball->setXVelocity(0);
    m_ball->setYVelocity(0);

    m_player->setRoundStarted(false);
}

/*!
 * \brief Chance for a PowerUp to drop after a brick has died.
 */
void TableScene::addPowerup(qreal x, qreal y) {
    if (rand()%6 == 0) {
        int randBonus = rand()%3;
        QRectF rect = QRectF(x, 0, 45, 15);
        if (randBonus == 0) {
            this->addItem(new BallPowerBonus(rect, "POWER", 1, QBrush(Qt::yellow)));
        }
        else if (randBonus == 1) {
            if (m_ball->getRadius() < 15)
                this->addItem(new BallSizeBonus(rect, "SIZE", 1, QBrush(Qt::magenta)));
        }
        else if (randBonus == 2) {
            this->addItem(new ExtraLife(rect, "LIFE", 1, QBrush(Qt::red)));
        }
    }
}

/*!
 * \brief Resets PowerUp bonuses.
 */
void TableScene::resetPowerUps() {
    m_ball->restoreDefaultRadius();
    m_ball->setPower(1);
}
