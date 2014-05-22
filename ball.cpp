#include "ball.h"
#include "configreader.h"
#include "brick.h"
#include <string>
#include <iomanip>
#include <sstream>
#include "coordinate.h"
#include <cmath>

using namespace std;

Ball::Ball(QPointF coordinate,
           unsigned int radius,
           double xVelocity,
           double yVelocity,
           QColor color) :
    as1Ball(Coordinate(coordinate), radius, 0, xVelocity, yVelocity, color),
    m_linePen(QPen(Qt::black)),
    m_fillBrush(QBrush(color))
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

    bool x_collided = false;
    bool y_collided = false;

    // Check for a collision with the sizes of the box

    if (isBottomCollision()) {
        coordinate.setY(this->scene()->height() - this->boundingRect().bottom());
        y_collided = true;
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

    QList<QGraphicsItem *> collidingItems = scene()->collidingItems(this);

    foreach (QGraphicsItem *item, collidingItems) {

        Brick * brick = dynamic_cast<Brick *>(item);
        if (brick != NULL) { // if the dynamic cast is successful, the item is a brick

            brick->decLife();

            // Calculate lines for the edges of the brick
            QRectF brickBoundingRect = mapFromItem(brick, brick->boundingRect()).boundingRect();
            QLineF brickLeftEdge(brickBoundingRect.topLeft(), brickBoundingRect.bottomLeft());
            QLineF brickRightEdge(brickBoundingRect.topRight(), brickBoundingRect.bottomRight());
            QLineF brickTopEdge(brickBoundingRect.topLeft(), brickBoundingRect.topRight());
            QLineF brickBottomEdge(brickBoundingRect.bottomLeft(), brickBoundingRect.bottomRight());

            // For each of the edges of the brick, calculate the point of intersection (if it exists)
            // between the edge of the brick, and the line between the centres of the brick and ball

            QLineF lineBetweenCentres(brickBoundingRect.center(), this->boundingRect().center());

            QPointF *intersectionPoint = new QPointF();

            // Top collision
            if (lineBetweenCentres.intersect(brickBottomEdge, intersectionPoint) == QLineF::BoundedIntersection) {
                coordinate.setY(mapToParent(0, brickBoundingRect.bottom()).y());
                y_collided = true;
            }

            // Bottom collision
            if (lineBetweenCentres.intersect(brickTopEdge, intersectionPoint) == QLineF::BoundedIntersection) {
                coordinate.setY(mapToParent(0, brickBoundingRect.top() - this->boundingRect().height()).y());
                y_collided = true;
            }

            // Left collision
            if (lineBetweenCentres.intersect(brickRightEdge, intersectionPoint) == QLineF::BoundedIntersection) {
                coordinate.setX(mapToParent(brickBoundingRect.right(), 0).x());
                x_collided = true;
            }

            // Right collision
            if (lineBetweenCentres.intersect(brickLeftEdge, intersectionPoint) == QLineF::BoundedIntersection) {
                coordinate.setX(mapToParent(brickBoundingRect.left() - this->boundingRect().width(), 0).x());
                x_collided = true;
            }

            delete intersectionPoint;

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
