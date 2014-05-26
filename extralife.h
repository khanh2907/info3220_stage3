#ifndef EXTRALIFE_H
#define EXTRALIFE_H

#include "powerup.h"

class ExtraLife : public PowerUp
{
public:
    ExtraLife(const QRectF &rect,
              QString m_title,
              qreal dropVelocity,
              const QBrush &fill_brush = QBrush()) : PowerUp(rect, m_title, dropVelocity, fill_brush) {}

    virtual void applyBonus();
};

#endif // EXTRALIFE_H
