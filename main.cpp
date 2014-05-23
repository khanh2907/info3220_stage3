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

        // Add ball
        table->addBall(new Ball(  QPoint(the_reader->getBallX(), the_reader->getBallY()),
                                  the_reader->getBallRadius(),
                                  the_reader->getBallXSpeed(),
                                  the_reader->getBallYSpeed(),
                                  the_reader->getBallColor()));

        // Add bricks
        foreach (ConfigReader::brickConfig brick, the_reader->getBricks()) {
            table->addBrick(new Brick( QRectF(brick.x, brick.y, brick.width, brick.height),
                                       brick.lives,
                                       brick.visible,
                                       QBrush(brick.color)));
        }

        // Add paddle
        if (the_reader->getPlayGame()) {
            table->addPaddle(new Paddle (QRectF(0, 550, 70, 10)));
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
