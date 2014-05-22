#include "tablescene.h"

#include <stdexcept>
#include <QKeyEvent>

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
                       QColor bgColour) :
    QGraphicsScene(0, 0, width, height),
    m_view(this)
{
    this->setBackgroundBrush(QBrush(bgColour));

    // connect the timer for animation
    QObject::connect(&m_timer, SIGNAL(timeout()), this, SLOT(advance()));

    m_view.setRenderHint(QPainter::Antialiasing);
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
 */
TableScene * TableScene::instance(int width, int height,
                                 QColor bgColour)
{
    if (m_table_instance == 0) {
        m_table_instance = new TableScene(width, height,
                                          bgColour);
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

    if (brick->collidingItems().size() > 0) {
        this->removeItem(brick);
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
