#ifndef POWERUP_H
#define POWERUP_H
#include <QGraphicsItem>
#include <QPainter>

class PowerUp : public QGraphicsRectItem, public QObject
{
public:
    PowerUp(const QRectF &rect,
            QString m_title,
            qreal dropVelocity,
            const QBrush &fill_brush = QBrush());

    virtual void applyBonus() = 0;

protected:
    virtual void advance(int step);

    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget);

private:
    QString m_title;
    qreal m_dropVelocity;
    QPen m_linePen;        /*!< QPen used to paint the outline of the brick */
    QBrush m_fillBrush;    /*!< QBrush used to paint the fill of the brick */
};

#endif // POWERUP_H
