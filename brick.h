#ifndef BRICK_H
#define BRICK_H

#include <QGraphicsItem>
#include <QPainter>

class Brick : public QGraphicsRectItem
{

public:
    Brick(const QRectF &rect,
          int lives,
          bool visible,
          const QBrush &fill_brush = QBrush());

    Brick(const Brick &other);

    Brick & setNumLives(int lives);
    int getNumLives();
    Brick & decLife();

    Brick & setLinePen(const QPen &linePen);
    Brick & setFillBrush(const QBrush &fillBrush);

protected:
    virtual void advance(int step);

    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget);

private:

    int m_lives; /*!< number of remaining lives */

    QPen m_linePen;        /*!< QPen used to paint the outline of the brick */
    QBrush m_fillBrush;    /*!< QBrush used to paint the fill of the brick */

};

#endif // BRICK_H
