#include "ballsizebonus.h"
#include <iostream>
#include "tablescene.h"
#include <QGraphicsScene>
#include <sstream>

void BallSizeBonus::applyBonus() {
    TableScene * tableScene = dynamic_cast<TableScene *>(scene());

    if (tableScene != NULL) {
        Ball * ball = tableScene->getBall();

        ball->setRadius(2 * ball->getRadius());

    }
}
