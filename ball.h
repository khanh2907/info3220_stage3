#ifndef BALL_H
#define BALL_H

#include <QColor>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include "as1ball.h"

class Ball : public QGraphicsItem, private as1Ball
{

public:
    Ball(QPointF coordinate,
        unsigned int radius,
        double xVelocity,
        double yVelocity,
        QColor color);

    ~Ball();

    Ball(const Ball &other);

    bool isBottomCollision() const;
    bool isCeilCollision() const;
    bool isLeftCollision() const;
    bool isRightCollision() const;

    using as1Ball::getRadius;
    using as1Ball::setRadius;

    using as1Ball::getColor;
    using as1Ball::setColor;

    QPointF coordinate() const;
    void setCoordinate(const QPointF &coordinate);

    using as1Ball::xVelocity;
    using as1Ball::setXVelocity;

    using as1Ball::yVelocity;
    using as1Ball::setYVelocity;

    int getPower();
    int setPower(int newPower);

protected:
    virtual void advance(int step);

    virtual QRectF boundingRect() const;
    virtual QPainterPath shape() const;

    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget);
private:

    QPen m_linePen;
    QBrush m_fillBrush;
    int m_power;
    using as1Ball::m_coordinate;
    using as1Ball::m_radius;
    using as1Ball::m_xVelocity;
    using as1Ball::m_yVelocity;
    using as1Ball::m_color;
};

#endif // BALL_H
