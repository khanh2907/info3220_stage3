#include "tableview.h"

#include <QResizeEvent>
#include <stdexcept>
#include <QLayout>

/*!
 * \brief TableView constructor
 *
 * \param table pointer to the table for this tableview
 */
TableView::TableView(QGraphicsScene *table) :
    QGraphicsView(table)
{
    setRenderHint(QPainter::Antialiasing);
    setFixedSize(this->sceneRect().size().width(), this->sceneRect().size().height());
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff) ;
}
