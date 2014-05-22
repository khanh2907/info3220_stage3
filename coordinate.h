
#ifndef COORDINATE_H
#define COORDINATE_H

#include <stdlib.h>
#include <QPointF>

class Coordinate
{
public:
    Coordinate(unsigned
        int xCoordinate,
        unsigned int yCoordinate,
        unsigned int frameWidth,
        unsigned int frameHeight);

    // Added in Stage 2
    Coordinate(QPointF coordinate);

    int getQtRenderingXCoordinate() const;
    int getQtRenderingYCoordinate() const;

    void changeInXCoordinate(int change);
    void changeInYCoordinate(int change);

    void setXCoordinateToZero(int offset);
    void setYCoordinateToZero(int offset);

    unsigned int getFrameHeight() const;

    unsigned int getFrameWidth() const;

    unsigned int xCoordinate() const;
    void setXCoordinate(unsigned int xCoordinate);

    unsigned int yCoordinate() const;
    void setYCoordinate(unsigned int yCoordinate);

    //unsigned int frameWidth() const;
    //void setFrameWidth(unsigned int frameWidth);

    //unsigned int frameHeight() const;
    //void setFrameHeight(unsigned int frameHeight);

private:
    unsigned int m_xCoordinate;
    unsigned int m_yCoordinate;
    //unsigned int m_frameWidth;
    //unsigned int m_frameHeight;
};

#endif // COORDINATE_H

