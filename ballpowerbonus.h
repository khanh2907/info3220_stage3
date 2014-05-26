#ifndef BALLPOWERBONUS_H
#define BALLPOWERBONUS_H

#include "powerup.h"

class BallPowerBonus : public PowerUp
{
public:
    BallPowerBonus(const QRectF &rect,
              QString m_title,
              qreal dropVelocity,
              const QBrush &fill_brush = QBrush()) : PowerUp(rect, m_title, dropVelocity, fill_brush) {}

    virtual void applyBonus();
};

#endif // BALLPOWERBONUS_H
