#ifndef OVERLAYOBJECT_H
#define OVERLAYOBJECT_H

#include <QGraphicsItem>
#include <QPainter>

class OverlayObject : public QGraphicsRectItem, public QObject
{
public:
    OverlayObject(const QRectF &rect, bool visible, QString title, QString text);

    void setText(QString newText);

    void restoreDefaultText();

protected:
    virtual void advance(int step);

    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget);

private:
    QString m_title;
    QString m_text;
    QString m_defaultText;
};

#endif // OVERLAYOBJECT_H
