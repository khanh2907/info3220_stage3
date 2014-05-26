#include "powerup.h"
#include <QGraphicsScene>
#include "tablescene.h"
#include "paddle.h"

PowerUp::PowerUp(const QRectF &rect, QString title, qreal dropVelocity, const QBrush &fill_brush) :
    QGraphicsRectItem(rect),
    m_title(title),
    m_dropVelocity(dropVelocity),
    m_fillBrush(fill_brush)
{

}

/*!
 * \brief Sets the state of the powerup as the frame of the scene is advancing
 *
 * Called by the advance method of the parent Table.
 *
 * This method is called twice. The first time with step == 0
 * to indicate the scene is about to advance, and a second time
 * with step == 1 to indicate the scene is advancing.
 *
 * \param step
 */
void PowerUp::advance(int step) {

    if (step == 0) {
        // ignore that we are _about_ to advance
        return;
    }

    qreal currentY = this->pos().y();

    qreal newY = currentY + m_dropVelocity;

    TableScene * tableScene = dynamic_cast<TableScene *>(scene());

    if (tableScene != NULL) {
        Paddle * paddle = tableScene->getPaddle();
        qreal paddleTop = paddle->sceneBoundingRect().top();
        qreal paddleLeft = paddle->sceneBoundingRect().left();
        qreal paddleRight = paddle->sceneBoundingRect().right();

        if (this->sceneBoundingRect().left() <= paddleRight && this->sceneBoundingRect().right() >= paddleLeft && newY + this->sceneBoundingRect().height() >= paddleTop) {
            applyBonus();
            this->setVisible(false);
            scene()->removeItem(this);
            return;
        }

    }

    setY(newY);

}

/*!
 * \brief Paints the powerup object
 *
 * Performs the painting of the powerup in the parent Table object using the given painter.
 *
 * \param painter in which to perform painting
 */

void PowerUp::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {

    qreal currentY = this->pos().y();
    if (!this->isVisible() ||currentY >= scene()->height()) {
        delete this;
        return;
    }

    painter->setBrush(m_fillBrush);
    painter->drawRect(this->rect());

    painter->drawText(this->boundingRect(), Qt::AlignCenter, m_title);
}
