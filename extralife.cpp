#include "extralife.h"
#include <iostream>
#include "tablescene.h"
#include <QGraphicsScene>
#include <sstream>

/*!
 * \brief Pure virtual class of the strategy design pattern.
 * \return void
 */
void ExtraLife::applyBonus() {
    TableScene * tableScene = dynamic_cast<TableScene *>(scene());

    if (tableScene != NULL) {
        qreal current_life = tableScene->getPlayer()->incrementLife();
        std::stringstream ss;
        ss << "Lives: " << current_life;
        tableScene->updateOverlay(0, QString::fromStdString(ss.str()));
    }
}
