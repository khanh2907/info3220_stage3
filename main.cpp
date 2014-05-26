/*
 * Comment from Stage 1:
 *
 * Author: Guilherme Jovanini Montagner
 * 31/03/2014
 * Parts of this code were taken from INFO3220 Tutorials taken on weeks 1-4.
 * Namely, the classes "coordinate" and "ball",
 * albeit being modified. Also, parts on the main file and on dialog.cpp and dialog.h were kept similar to what was
 * used on these tutorials.
*/

//#include "dialog.h"
#include "configreader.h"
#include <QApplication>
#include "tablescene.h"
#include "ball.h"
#include <stdexcept>
#include "brick.h"
#include <vector>
#include <QErrorMessage>
#include "paddle.h"
#include "player.h"
#include "overlayobject.h"
#include "levelgenerator.h"
#include "powerup.h"
#include "extralife.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    srand(3220); // initialise rand seed

    try {

        #ifdef Q_OS_MAC
            std::string config_file = "/Users/khanh/INFO3220_Assignment/AssignmentThreeBaseTwo/config.txt";
        #else
            std::string config_file = "config.txt";
        #endif

        ConfigReader* the_reader=ConfigReader::instance(config_file);

        if (the_reader->getErrorType() == ERROR_NOFILE) {
            throw std::runtime_error("Error reading config file. File not found.");
        } else if (the_reader->getErrorType() == ERROR_UNKNOWN_PARAM) {
            throw std::runtime_error("Error reading config file. Invalid definition: check for unknown parameter or whitespace.");
        } else if (the_reader->getErrorType() != ERROR_OK) {
            throw std::runtime_error("Error reading config file. Unknown error.");
        }

        // Initialise scene
        TableScene *table = TableScene::instance(the_reader->getBoxWidth(),
                                                 the_reader->getBoxHeight(),
                                                 the_reader->getTableColor(),
                                                 the_reader->getPlayGame());


        if (!the_reader->getPlayGame()) {
            // Add ball
            table->addBall(new Ball(  QPoint(the_reader->getBallX(), the_reader->getBallY()),
                                      the_reader->getBallRadius(),
                                      the_reader->getBallXSpeed(),
                                      the_reader->getBallYSpeed(),
                                      the_reader->getBallColor()));


        }


        if (the_reader->getPlayGame()) {
            table->setPlayer(new Player(3));

            table->addOverlayObject(new OverlayObject(QRectF(280, 0, 100, 20), true, "lives","Lives: 3"));
            table->addOverlayObject(new OverlayObject(QRectF(380, 0, 100, 20), true, "level","Level: 1"));
            table->addOverlayObject(new OverlayObject(QRectF(480, 0, 100, 20), true, "score","Score: 0"));

            table->addItem(new ExtraLife(QRectF(0, 0, 40, 15), "P", 2));

            // Add paddle
            Paddle * paddle = new Paddle (QRectF(0, 550, 100, 10));
            table->addPaddle(paddle);

            unsigned int radius = the_reader->getBallRadius();

            qreal startBallX = paddle->boundingRect().right() + paddle->boundingRect().width()/2 - radius;
            qreal startBallY = paddle->boundingRect().top() - radius*2 - 1;

            table->addBall(new Ball(  QPoint(startBallX, startBallY),
                                      the_reader->getBallRadius(),
                                      0,
                                      0,
                                      the_reader->getBallColor()));


        }

        // Add bricks
        if (the_reader->getLevelsOn()) {
            table->generateLevel();
        }
        else {
            foreach (ConfigReader::brickConfig brick, the_reader->getBricks()) {
                table->addBrick(new Brick( QRectF(brick.x, brick.y, brick.width, brick.height),
                                           brick.lives,
                                           brick.visible,
                                           QBrush(brick.color)));
            }
        }

        table->startAnimation(the_reader->getFramerate());
        table->view().show();

        return a.exec();

    } catch (std::exception &e) {
        // Catch any exceptions, and display an error message.
        QErrorMessage em;
        em.showMessage(QString::fromStdString(e.what()));
        return a.exec();
    }
}
