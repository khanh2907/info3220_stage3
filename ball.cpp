#include "ball.h"
#include "configreader.h"
#include "brick.h"
#include <string>
#include <iomanip>
#include <sstream>
#include "coordinate.h"
#include <cmath>
#include "paddle.h"
#include "tablescene.h"
#include <QMessageBox>
#include <QApplication>
#include "overlayobject.h"

using namespace std;

Ball::Ball(QPointF coordinate,
           unsigned int radius,
           double xVelocity,
           double yVelocity,
           QColor color) :
    as1Ball(Coordinate(coordinate), radius, 0, xVelocity, yVelocity, color),
    m_defaultRadius(radius),
    m_linePen(QPen(Qt::black)),
    m_fillBrush(QBrush(color)),
    m_power(1)
{
    // Sets the position of the Ball in the parent scene
    setPos(this->coordinate());
}

Ball::~Ball()
{
}


QPointF Ball::coordinate() const
{
    return QPointF(m_coordinate.getQtRenderingXCoordinate(), m_coordinate.getQtRenderingYCoordinate());
}

/*!
 * \brief Sets coordinate of the ball
 *
 * Takes in QPointF which is a coordinate, and sets it to the Ball object
 *
 * \param QPointF coordinate which is the coordinate that the ball will be set to
 */
void Ball::setCoordinate(const QPointF &coordinate)
{
    m_coordinate.setXCoordinate(coordinate.x());
    m_coordinate.setYCoordinate(m_coordinate.getFrameHeight() - coordinate.y());
}


/*!
 * \brief Ball copy constructor
 *
 * Explict copy constructor as base class 'QGraphicsItem' has private copy constructor
 *
 * \param other The object to copy to
 */
Ball::Ball(const Ball &other) :
    as1Ball(other),
    m_linePen(other.m_linePen),
    m_fillBrush(other.m_fillBrush)
{}

/*!
 * \brief Detects whether the ball has hit the bottom of the scene
 * \return bool
 */
bool Ball::isBottomCollision() const {
    return mapToParent(0, this->boundingRect().bottom()).y() > scene()->height();
}

/*!
 * \brief Detects whether the ball has hit the top of the scene
 * \return bool
 */
bool Ball::isCeilCollision() const {
    return mapToParent(0, this->boundingRect().top()).y() < 0;
}

/*!
 * \brief Detects whether the ball has hit the right side of the scene
 * \return bool
 */
bool Ball::isRightCollision() const {
    return mapToParent(this->boundingRect().right(), 0).x() > scene()->width();
}

/*!
 * \brief Detects whether the ball has hit the left side of the scene
 * \return bool
 */
bool Ball::isLeftCollision() const {
    return mapToParent(this->boundingRect().left(), 0).x() < 0;
}

/*!
 * \brief Returns the power of the ball
 * \return int
 */
int Ball::getPower() {
    return m_power;
}

/*!
 * \brief Sets the power of the ball
 * \param int value of new power value
 * \return int value of the new power
 */
int Ball::setPower(int newPower) {
    m_power = newPower;
    return m_power;
}

/*!
 * \brief Sets the radius to the default radius set at initialisation
 * \return void
 */
void Ball::restoreDefaultRadius() {
    this->setRadius(m_defaultRadius);
}

/*!
 * \brief Overloaded QGraphicsItem::boundingRect
 *
 * Defines the approximate size of the object. This is used to determine
 * whether the object requires redrawing in the scene.
 *
 * \return QRectF defining the obejct in the local coordinate system
 */
QRectF Ball::boundingRect() const {
    int pen_line_width = 1;

    return QRectF(mapFromParent(coordinate().x(), coordinate().y()),
                  QSizeF((m_radius * 2 + pen_line_width),
                        (m_radius * 2 + pen_line_width)));

}

/*!
 * \brief Overloaded QGraphicsItem::shape
 *
 * Defines the detailed size and shape of the object. This is used
 * for collission detection.
 *
 * \return QPainterPath defining the shape in the local coordinate system
 */
QPainterPath Ball::shape() const {
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

/*!
 * \brief Sets the state of the ball as the frame of the scene is advancing
 *
 * Called by the advance method of the parent Table.
 *
 * This method is called twice. The first time with step == 0
 * to indicate the scene is about to advance, and a second time
 * with step == 1 to indicate the scene is advancing.
 *
 * \param step
 */
void Ball::advance(int step) {

    if (step == 0) {
        // ignore that we are _about_ to advance
        return;
    }

    QPointF coordinate = mapToParent(0 + m_xVelocity, 0 + m_yVelocity);

    TableScene * tablescene = dynamic_cast<TableScene *>(scene());

    bool playGameOn = tablescene->getPlayGame();


    // move the ball sitting on the paddle
    if (playGameOn) {
        if (!tablescene->getPlayer()->getRoundStarted()){
            Paddle * paddle = tablescene->getPaddle();
            qreal newBallX = paddle->sceneBoundingRect().center().x() - m_radius;
            qreal newBallY = paddle->sceneBoundingRect().top() - m_radius*2 - 1;

            coordinate.setX(newBallX);
            coordinate.setY(newBallY);
        }
    }

    bool x_collided = false;
    bool y_collided = false;

    // Check for a collision with the sizes of the box

    if (isBottomCollision()) {
        if (!playGameOn) {
            coordinate.setY(this->scene()->height() - this->boundingRect().bottom());
            y_collided = true;
        }
        else {
            if (tablescene->getPlayer()->getRoundStarted()){
                qreal current_life = tablescene->getPlayer()->decrementLife();
                std::stringstream ss;
                ss << "Lives: " << current_life;

                tablescene->updateOverlay(0, QString::fromStdString(ss.str()));

                if (current_life <= 0) {
                    QApplication::setOverrideCursor(Qt::ArrowCursor);

                    std::stringstream scoreSS;
                    scoreSS << "You scored " << tablescene->getPlayer()->getScore() << " points.";

                    QMessageBox msgBox;
                    msgBox.setText("GGWP!");
                    msgBox.setInformativeText(QString::fromStdString(scoreSS.str()));
                    msgBox.addButton("Play Again", QMessageBox::YesRole);
                    msgBox.addButton("Exit", QMessageBox::NoRole);
                    msgBox.exec();


                    if (msgBox.buttonRole(msgBox.clickedButton()) == QMessageBox::YesRole){
                        //decrement life - TODO create player object
                        tablescene->getPlayer()->setRoundStarted(false);
                        tablescene->restartGame();
                    }
                    else if (msgBox.buttonRole(msgBox.clickedButton()) == QMessageBox::NoRole) {
                        QCoreApplication::instance()->exit();
                    }
                }
                else {
                    coordinate.setX(300);
                    coordinate.setY(300);
                    setXVelocity(0);
                    setYVelocity(0);
                    tablescene->resetPowerUps();
                    tablescene->getPlayer()->setRoundStarted(false);
                }
            }

        }
    }

    if (isCeilCollision()) {
        coordinate.setY(-this->boundingRect().top());
        y_collided = true;
    }

    if (isLeftCollision()) {
        coordinate.setX(-this->boundingRect().left());
        x_collided = true;
    }

    if (isRightCollision()) {
        coordinate.setX(this->scene()->width() - this->boundingRect().right());
        x_collided = true;
    }


    // Check for collisions with other objects
    // (At this stage this only covers Bricks)

    QList<QGraphicsItem *> items = scene()->items();

    qreal currentXPos = this->pos().x();
    qreal currentYPos = this->pos().y();
    qreal diameter = m_radius * 2;

    qreal futureBallTop = coordinate.y();
    qreal futureBallBottom = coordinate.y() + diameter;
    qreal futureBallLeft = coordinate.x();
    qreal futureBallRight = coordinate.x() + diameter;


    foreach (QGraphicsItem *item, items) {

        Brick * thisBrick = dynamic_cast<Brick *>(item);

        if (thisBrick != NULL && thisBrick->isVisible()) {
            qreal brickTop = thisBrick->boundingRect().top();
            qreal brickBottom = thisBrick->boundingRect().bottom();
            qreal brickLeft = thisBrick->boundingRect().left();
            qreal brickRight = thisBrick->boundingRect().right();

            if (futureBallLeft <= brickRight && futureBallRight >= brickLeft && futureBallBottom >= brickTop && futureBallTop <= brickBottom) {
                 // if it is inside then check which side the ball is going to hit
                // then send it back the other way
                if (currentXPos + diameter <= brickLeft) {
                   x_collided = true;
                   coordinate.setX(brickLeft - diameter);
                }
                else if (currentXPos >= brickRight) {
                   x_collided = true;
                   coordinate.setX(brickRight);
                }
                if (currentYPos + diameter <= brickTop) {
                   y_collided = true;
                   coordinate.setY(brickTop - diameter);
                }
                else if (currentYPos >= brickBottom) {
                   y_collided = true;
                   coordinate.setY(brickBottom);
                }


                if (playGameOn) {
                    // reduce brick life by ball power
                    int currentLife = thisBrick->getNumLives();
                    thisBrick->decLife(this->getPower());
                    int newLife = thisBrick->getNumLives();

                    if (newLife < 0)
                        newLife = 0;

                    qreal currentScore = tablescene->getPlayer()->increaseScore(currentLife-newLife);
                    std::stringstream ss;
                    ss << "Score: " << currentScore;
                    tablescene->updateOverlay(2, QString::fromStdString(ss.str()));
                }
                else {
                    // reduce brick life by one
                    thisBrick->decLife();
                }

            }
        }

        if (playGameOn) {
            if (tablescene->getPlayer()->getRoundStarted()) {
                Paddle * paddle = dynamic_cast<Paddle *>(item);

                if (paddle != NULL) {
                    qreal paddleTop = paddle->sceneBoundingRect().top();
                    qreal paddleLeft = paddle->sceneBoundingRect().left();
                    qreal paddleRight = paddle->sceneBoundingRect().right();

                    if (futureBallLeft <= paddleRight && futureBallRight >= paddleLeft && futureBallBottom >= paddleTop) {

                         // if it is inside then check which side the ball is going to hit
                        // then send it back the other way

                        if (currentYPos + diameter <= paddleTop) {
                           y_collided = true;
                           coordinate.setY(paddleTop - diameter);

                           qreal paddleCenter = paddle->sceneBoundingRect().center().x();
                           qreal paddleWidth = paddle->sceneBoundingRect().width();

                           if (coordinate.x() + m_radius < paddleCenter - paddleWidth/3) {
                               setXVelocity(-5);
                           }
                           else if (coordinate.x() + m_radius > paddleCenter + paddleWidth/3) {
                               setXVelocity(5);
                           }
                           else if (coordinate.x() + m_radius < paddleCenter - paddleWidth/6 && coordinate.x() + m_radius >= paddleCenter - paddleWidth/3) {
                               setXVelocity(-3);
                           }
                           else if (coordinate.x() + m_radius > paddleCenter + paddleWidth/6 && coordinate.x() + m_radius <= paddleCenter + paddleWidth/3) {
                               setXVelocity(3);
                           }
                        }
                    }
                }
            }
        }

    }

    // only update the velocity once per scene update
    // this eliminates the scenario where multiple collision events in the same frame cancel each other out
    // (e.g. hitting 2 bricks at once)

    if (y_collided) {
        m_yVelocity *= -1;
    }

    if (x_collided) {
        m_xVelocity *= -1;
    }

    setCoordinate(coordinate);

    // set coordinates in the parent coordinate system
    setPos(coordinate);


}

/*!
 * \brief Paints the ball object
 *
 * Performs the painting of the ball in the parent Table object using the given painter.
 *
 * \param painter in which to perform painting
 */
void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setPen(m_linePen);
    painter->setBrush(m_fillBrush);
    painter->drawEllipse(0, 0, m_radius * 2, m_radius * 2);
}
