#include "ballsizebonus.h"
#include <iostream>
#include "tablescene.h"
#include <QGraphicsScene>
#include <sstream>

/*!
 * \brief Pure virtual class of the strategy design pattern.
 * \return void
 */
void BallSizeBonus::applyBonus() {
    TableScene * tableScene = dynamic_cast<TableScene *>(scene());

    if (tableScene != NULL) {
        Ball * ball = tableScene->getBall();

        ball->setRadius(2 * ball->getRadius());

    }
}
