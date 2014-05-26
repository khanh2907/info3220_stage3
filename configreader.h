#ifndef CONFIGREADER_H
#define CONFIGREADER_H
#include <iostream>
#include <string>
#include <vector>
#include <QColor>

enum configError{
    ERROR_OK=0,
    ERROR_NOFILE,
    ERROR_UNKNOWN_PARAM
};

class ConfigReader
{
public:
    static ConfigReader *instance(std::string file);
    static ConfigReader *getInstance();
    static void resetInstance();

    static int getErrorType();
    static void setErrorType(int value);

    static unsigned int getBoxWidth();
    static void setBoxWidth(unsigned int value);

    static unsigned int getBoxHeight();
    static void setBoxHeight(unsigned int value);

    static unsigned int getBallRadius();
    static void setBallRadius(unsigned int value);

    static unsigned int getBallX();
    static void setBallX(unsigned int value);

    static unsigned int getBallY();
    static void setBallY(unsigned int value);

    static double getBallXSpeed();
    static void setBallXSpeed(double value);

    static double getBallYSpeed();
    static void setBallYSpeed(double value);

    // added in as2
    struct brickConfig {
        int x;
        int y;
        int width;
        int height;
        int lives;
        bool visible;
        QColor color;
    };

    static const std::vector<brickConfig> & getBricks();
    static int getFramerate();
    static QColor getTableColor();
    static QColor getBallColor();
    static bool getEnableBrickRegenerate();
    static QColor getRegeneratedBrickColor();
    static double getRegeneratedBrickProbability();
    static int getRegeneratedBrickMaxLives();
    static bool getShowBrickLives();
    static bool getPlayGame();
    static bool getLevelsOn();

protected:
    ConfigReader(std::string file);

    // added in as2
    std::vector<std::string> tokenise(const std::string &str, char delim = ':');

private:
    static ConfigReader *_instance;

    static unsigned int boxWidth;
    static unsigned int boxHeight;
    static unsigned int ballRadius;
    static unsigned int ballX;
    static unsigned int ballY;
    static double ballXSpeed;
    static double ballYSpeed;
    static int errorType;

    static std::vector<brickConfig> bricks;

    static int framerate;
    static int tableColor;
    static int ballColor;
    static bool enableBrickRegenerate;
    static int regeneratedBrickColor;
    static double regeneratedBrickProbability;
    static int regeneratedBrickMaxLives;
    static bool showBrickLives;

    static bool playGame;
    static bool levelsOn;

};
#endif // CONFIGREADER_H
