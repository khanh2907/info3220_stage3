#include "paddle.h"

Paddle::Paddle(const QRectF &rect,
               const QBrush &fill_brush) :
    QGraphicsRectItem(rect),
    m_fillBrush(fill_brush)
{
}

/*!
 * \brief Sets the state of the brick as the frame of the scene is advancing
 *
 * Called by the advance method of the parent Table.
 *
 * This method is called twice. The first time with step == 0
 * to indicate the scene is about to advance, and a second time
 * with step == 1 to indicate the scene is advancing.
 *
 * \param step
 */
void Paddle::advance(int step) {

    if (step == 0) {
        // ignore that we are _about_ to advance
        return;
    }
}

/*!
 * \brief Paints the paddle object
 *
 * Performs the painting of the brick in the parent Table object using the given painter.
 *
 * \param painter in which to perform painting
 */

void Paddle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setBrush(m_fillBrush);
    painter->drawRect(this->rect());
}
