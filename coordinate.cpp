#include "coordinate.h"
#include "configreader.h"

Coordinate::Coordinate(unsigned int xCoordinate,
                       unsigned int yCoordinate,
                       unsigned int, // frameWidth,
                       unsigned int) // frameHeight )
    :m_xCoordinate(xCoordinate),m_yCoordinate(yCoordinate)
    //,m_frameWidth(frameWidth),m_frameHeight(frameHeight)
{
}

// Added in Stage 2
Coordinate::Coordinate(QPointF coordinate) :
    m_xCoordinate(coordinate.x()),
    m_yCoordinate(getFrameHeight() - coordinate.y())
{
}

int Coordinate::getQtRenderingXCoordinate() const
{
    return m_xCoordinate;
}

int Coordinate::getQtRenderingYCoordinate() const
{
    return getFrameHeight() - m_yCoordinate;
}

void Coordinate::changeInXCoordinate(int change)
{
    m_xCoordinate += change;
}

void Coordinate::changeInYCoordinate(int change)
{
    m_yCoordinate += change;
}

void Coordinate::setXCoordinateToZero(int offset)
{
    m_xCoordinate = 0 + offset;
}

void Coordinate::setYCoordinateToZero(int offset)
{
    m_yCoordinate = 0 + offset;
}

// Modified in Stage 2
unsigned int Coordinate::getFrameHeight() const
{
    return ConfigReader::getInstance()->getBoxHeight();
}

// Modified in Stage 2
unsigned int Coordinate::getFrameWidth() const
{
    return ConfigReader::getInstance()->getBoxWidth();
}

unsigned int Coordinate::xCoordinate() const
{
    return m_xCoordinate;
}

void Coordinate::setXCoordinate(unsigned int xCoordinate)
{
    m_xCoordinate = xCoordinate;
}
unsigned int Coordinate::yCoordinate() const
{
    return m_yCoordinate;
}

void Coordinate::setYCoordinate(unsigned int yCoordinate)
{
    m_yCoordinate = yCoordinate;
}

//unsigned int Coordinate::frameWidth() const
//{
//    return m_frameWidth;
//}

//void Coordinate::setFrameWidth(unsigned int frameWidth)
//{
//    m_frameWidth = frameWidth;
//}
//unsigned int Coordinate::frameHeight() const
//{
//    return m_frameHeight;
//}

//void Coordinate::setFrameHeight(unsigned int frameHeight)
//{
//    m_frameHeight = frameHeight;
//}


