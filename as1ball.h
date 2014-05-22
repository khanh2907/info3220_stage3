#ifndef AS1BALL_H
#define AS1BALL_H

#include <iostream>
#include "coordinate.h"
#include <QPainter>
#include <QColor>

class as1Ball
{

public:
    as1Ball(Coordinate coordinate);
    as1Ball(Coordinate coordinate,
        unsigned int radius);
    as1Ball(Coordinate coordinate,
        unsigned int radius,
        double gravity,
        double xVelocity,
        double yVelocity,
        QColor color = "yellow");

    virtual ~as1Ball();

    virtual void loadConfig();
    virtual void render(QPainter &painter, unsigned int time);

    bool isBottomCollision();
    bool isCeilCollision();
    bool isLeftCollision();
    bool isRightCollision();

    virtual unsigned int getRadius();
    virtual void setRadius(unsigned int radius);

    virtual QColor getColor() const;
    virtual void setColor(const QColor &color);

    Coordinate coordinate() const;
    void setCoordinate(const Coordinate &coordinate);

    virtual double gravity() const;
    virtual void setGravity(double gravity);

    virtual double xVelocity() const;
    virtual void setXVelocity(double xVelocity);

    virtual double yVelocity() const;
    virtual void setYVelocity(double yVelocity);

protected:
    as1Ball();

    Coordinate m_coordinate;
    unsigned int m_radius;
    double m_gravity;
    double m_xVelocity;
    double m_yVelocity;
    QColor m_color;
};

#endif // AS1BALL_H
