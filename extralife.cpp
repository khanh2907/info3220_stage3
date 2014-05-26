#include "extralife.h"
#include <iostream>
#include "tablescene.h"
#include <QGraphicsScene>
#include <sstream>

void ExtraLife::applyBonus() {
    TableScene * tableScene = dynamic_cast<TableScene *>(scene());

    if (tableScene != NULL) {
        qreal current_life = tableScene->getPlayer()->incrementLife();
        std::stringstream ss;
        ss << "Lives: " << current_life;
        tableScene->updateOverlay(0, QString::fromStdString(ss.str()));
    }
}
