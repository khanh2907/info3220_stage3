#ifndef PADDLE_H
#define PADDLE_H

#include <QGraphicsItem>
#include <QPainter>

class Paddle : public QGraphicsRectItem
{
public:
    Paddle(const QRectF &rect,
           const QBrush &fill_brush = QBrush());

protected:
    virtual void advance(int step);

    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget);

private:
    QPen m_linePen;        /*!< QPen used to paint the outline of the brick */
    QBrush m_fillBrush;    /*!< QBrush used to paint the fill of the brick */
};

#endif // PADDLE_H
