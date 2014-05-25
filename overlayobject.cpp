#include "overlayobject.h"

OverlayObject::OverlayObject(const QRectF &rect, bool visible, QString title, QString text) :
    QGraphicsRectItem(rect),
    m_title(title),
    m_text(text)
{
    this->setVisible(visible);
}

void OverlayObject::advance(int step) {
    if (step == 0) {
        return;
    }
}

void OverlayObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
//    painter->drawRect(this->rect());

    painter->drawText(this->boundingRect(), Qt::AlignCenter, m_text);
}

void OverlayObject::setText(QString newText) {
    m_text = newText;
}
