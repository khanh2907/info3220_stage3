#ifndef BALLSIZEBONUS_H
#define BALLSIZEBONUS_H

#include "powerup.h"

class BallSizeBonus : public PowerUp
{
public:
    BallSizeBonus(const QRectF &rect,
              QString m_title,
              qreal dropVelocity,
              const QBrush &fill_brush = QBrush()) : PowerUp(rect, m_title, dropVelocity, fill_brush) {}

    virtual void applyBonus();
};

#endif // BALLSIZEBONUS_H
