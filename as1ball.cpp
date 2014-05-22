#include "as1ball.h"
#include "configreader.h"
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;
as1Ball::as1Ball(Coordinate coordinate)
    :m_coordinate(coordinate)
{
}
double as1Ball::yVelocity() const
{
    return m_yVelocity;
}

void as1Ball::setYVelocity(double yVelocity)
{
    m_yVelocity = yVelocity;
}

double as1Ball::xVelocity() const
{
    return m_xVelocity;
}

void as1Ball::setXVelocity(double xVelocity)
{
    m_xVelocity = xVelocity;
}

double as1Ball::gravity() const
{
    return m_gravity;
}

void as1Ball::setGravity(double gravity)
{
    m_gravity = gravity;
}

Coordinate as1Ball::coordinate() const
{
    return m_coordinate;
}

void as1Ball::setCoordinate(const Coordinate &coordinate)
{
    m_coordinate = coordinate;
}


QColor as1Ball::getColor() const
{
    return m_color;
}

void as1Ball::setColor(const QColor &color)
{
    m_color = color;
}

as1Ball::as1Ball(Coordinate coordinate, unsigned int radius)
    :m_coordinate(coordinate),m_radius(radius)
{
}

as1Ball::as1Ball(Coordinate coordinate,
           unsigned int radius,
           double gravity,
           double xVelocity,
           double yVelocity,
           QColor color)
    :m_coordinate(coordinate),m_radius(radius),m_gravity(gravity),m_xVelocity(xVelocity),m_yVelocity(yVelocity),m_color(color)
{
}

as1Ball::~as1Ball()
{
}

void as1Ball::loadConfig()
{
    ConfigReader* reader=ConfigReader::getInstance();

    m_coordinate.setXCoordinate(reader->getBallX());
    m_coordinate.setYCoordinate(reader->getBallY());
//    m_coordinate.setFrameHeight(reader->getBoxHeight());
//    m_coordinate.setFrameWidth(reader->getBoxWidth());

    m_radius=reader->getBallRadius();

    m_xVelocity=reader->getBallXSpeed();

    m_yVelocity=reader->getBallYSpeed();

    unsigned int frameW;
    unsigned int frameH;
    frameW = m_coordinate.getFrameWidth();
    frameH = m_coordinate.getFrameHeight();

//    if(frameW<2*m_radius) m_coordinate.setFrameWidth(5*m_radius);
//    if(frameH<2*m_radius) m_coordinate.setFrameHeight(5*m_radius);
}

void as1Ball::setRadius(unsigned int radius)
{
    m_radius = radius;
}

unsigned int as1Ball::getRadius()
{
    return m_radius;
}

bool as1Ball::isBottomCollision()
{
    return m_coordinate.getQtRenderingYCoordinate() >
        (signed int) (m_coordinate.getFrameHeight() - (signed int) m_radius);
}

bool as1Ball::isCeilCollision()
{
    return m_coordinate.getQtRenderingYCoordinate() < 0 + (signed int) m_radius;
}

bool as1Ball::isLeftCollision()
{
    return m_coordinate.getQtRenderingXCoordinate() < 0 + (signed int) m_radius;
}

bool as1Ball::isRightCollision()
{
    return m_coordinate.getQtRenderingXCoordinate()>
            (signed int) (m_coordinate.getFrameWidth() - (signed int) m_radius);
}

void as1Ball::render(QPainter &painter, __attribute__((unused)) unsigned int time)
{
    if (isBottomCollision()) {
        this->setColor("blue");
        m_coordinate.setYCoordinateToZero(this->getRadius());
        // velocity decreases after hitting the ground
        m_yVelocity *= -0.8;

    }

    if(isCeilCollision()){
        this->setColor("red");
        m_coordinate.setYCoordinateToZero(m_coordinate.getFrameHeight()-this->getRadius());
        // velocity decreases after hitting the ground
        m_yVelocity *= -0.8;
    }

    if(isLeftCollision()){
        this->setColor("yellow");
        m_coordinate.setXCoordinateToZero(this->getRadius());
        // velocity decreases after hitting the ground
        m_xVelocity *= -0.8;

    }

    if(isRightCollision()){
        this->setColor("green");
        m_coordinate.setXCoordinateToZero(m_coordinate.getFrameWidth()-this->getRadius());
        // velocity decreases after hitting the ground
        m_xVelocity *= -0.8;

    }

    painter.setPen ( Qt::black  );
    painter.setBrush( QBrush( this->getColor()) );
    painter.drawEllipse(m_coordinate.getQtRenderingXCoordinate() - (int) m_radius,
        m_coordinate.getQtRenderingYCoordinate() -(int) m_radius,
        m_radius * 2,
        m_radius * 2);
    m_yVelocity += m_gravity / 32.0;
    m_coordinate.changeInXCoordinate(m_xVelocity);
    m_coordinate.changeInYCoordinate(m_yVelocity);
}
