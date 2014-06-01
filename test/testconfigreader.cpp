#include "testconfigreader.h"
#include "../configreader.cpp"

void TestConfigReader::testBoxConfig() {
    std::string config_file = "/Users/khanh/INFO3220_Assignment/AssignmentThreeBaseTwo/Test/config.txt";
    ConfigReader* the_reader = ConfigReader::instance(config_file);

    qreal boxHeight = the_reader->getBoxHeight();
    qreal boxWidth = the_reader->getBoxWidth();
    QColor tableColor = the_reader->getTableColor();
    qreal framerate = the_reader->getFramerate();

    QVERIFY(boxHeight == 600);
    QVERIFY(boxWidth == 600);
    QVERIFY(tableColor != Qt::yellow);
    QVERIFY(framerate == 100);
}

void TestConfigReader::testBallConfig() {
    std::string config_file = "/Users/khanh/INFO3220_Assignment/AssignmentThreeBaseTwo/Test/config.txt";
    ConfigReader* the_reader = ConfigReader::instance(config_file);

    qreal radius = the_reader->getBallRadius();
    qreal x = the_reader->getBallX();
    qreal y = the_reader->getBallY();
    qreal xSpeed = the_reader->getBallXSpeed();
    qreal ySpeed = the_reader->getBallYSpeed();

    QVERIFY(radius == 5);
    QVERIFY(x == 300);
    QVERIFY(y == 400);
    QVERIFY(xSpeed == -6);
    QVERIFY(ySpeed == 7);
}

void TestConfigReader::testBricksConfig() {
    std::string config_file = "/Users/khanh/INFO3220_Assignment/AssignmentThreeBaseTwo/Test/config.txt";
    ConfigReader* the_reader = ConfigReader::instance(config_file);

    std::vector<ConfigReader::brickConfig> bricks = the_reader->getBricks();

    QVERIFY(bricks.size() == 40);
}

void TestConfigReader::testExtensions() {
    std::string config_file = "/Users/khanh/INFO3220_Assignment/AssignmentThreeBaseTwo/Test/config.txt";
    ConfigReader* the_reader = ConfigReader::instance(config_file);

    QVERIFY(the_reader->getEnableBrickRegenerate() == true);
    QVERIFY(the_reader->getRegeneratedBrickMaxLives() == 20);
    QVERIFY(the_reader->getRegeneratedBrickProbability() == 0.0005);

    QVERIFY(the_reader->getShowBrickLives() == true);
    QVERIFY(the_reader->getPlayGame() == true);
    QVERIFY(the_reader->getIntialLives() == 3);
    QVERIFY(the_reader->getLevelsOn() == true);
    QVERIFY(the_reader->getPowerUpsOn() == true);
}
