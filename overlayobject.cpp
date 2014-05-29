#include "overlayobject.h"

/*!
 * \brief Constructor for the OverlayObject class
 * \param QRectF &rect which is the rectangle (coordinate and size)
 * \param bool visible which determines if the overlay will be visible on the scene or not
 * \param QString title which identifies the overlay
 * \param QString text which is the text displayed on the scene
 * \return OverlayObject
 */
OverlayObject::OverlayObject(const QRectF &rect, bool visible, QString title, QString text) :
    QGraphicsRectItem(rect),
    m_title(title),
    m_text(text),
    m_defaultText(text)
{
    this->setVisible(visible);
}

/*!
 * \brief Handles the animation of the scene object
 * \return void
 */
void OverlayObject::advance(int step) {
    if (step == 0) {
        return;
    }
}

/*!
 * \brief Draws the OverlayObject onto the scene
 * \return void
 */
void OverlayObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawText(this->boundingRect(), Qt::AlignCenter, m_text);
}

/*!
 * \brief Setter for the text
 * \param QString newText which is the text that the OverlayObject take on.
 * \return void
 */
void OverlayObject::setText(QString newText) {
    m_text = newText;
}

/*!
 * \brief Restores to the default text.
 * \return void
 */
void OverlayObject::restoreDefaultText() {
    m_text = m_defaultText;
}
