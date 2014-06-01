#include "configreader.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
ConfigReader *ConfigReader::_instance=0;
int ConfigReader::errorType=ERROR_OK;
unsigned int ConfigReader::boxWidth=600;
unsigned int ConfigReader::boxHeight=1000;
unsigned int ConfigReader::ballRadius=20;
unsigned int ConfigReader::ballX=10;
unsigned int ConfigReader::ballY=10;
double ConfigReader::ballXSpeed=5;
double ConfigReader::ballYSpeed=5;

// Stage 2 additions
vector<ConfigReader::brickConfig> ConfigReader::bricks;
int ConfigReader::framerate = 32; // from Stage 1
int ConfigReader::tableColor = 0x82CAFF; // from Stage 1
int ConfigReader::ballColor = QColor("yellow").rgb(); // from Stage 1
bool ConfigReader::enableBrickRegenerate = false;
int ConfigReader::regeneratedBrickColor = 0x0;
double ConfigReader::regeneratedBrickProbability = 0;
int ConfigReader::regeneratedBrickMaxLives = 0;
bool ConfigReader::showBrickLives = false;
bool ConfigReader::playGame = false;
int ConfigReader::initialLives = 3;
bool ConfigReader::levelsOn = false;
bool ConfigReader::powerUpsOn = false;
qreal ConfigReader::paddleWidth = 100;

ConfigReader *ConfigReader::instance(string file)
{
    if(_instance==0)
        _instance = new ConfigReader(file);
    return _instance;
}

ConfigReader *ConfigReader::getInstance()
{
    return _instance;
}

void ConfigReader::resetInstance()
{
    delete(_instance);
    _instance=0;
}

ConfigReader::ConfigReader(string file)
{

    ifstream ifs(file.c_str());

    if(ifs.is_open()){

        string line;
        errorType=ERROR_OK;
        vector<string> line_tokens;

        while(getline(ifs,line)){

            if (line.length() <= 1) { //blank line
                continue;
            }
            if (line.substr(0,1).compare("#") == 0) { //commented line
                continue;
            }
            else {
                line_tokens = tokenise(line, ':');
            }

            if (line_tokens.size() == 2) {
                // Use original logic to handle original parameters

                string paramName = line_tokens[0];
                string paramVal = line_tokens[1];

                stringstream ss;

                if (paramVal.substr(0, 2).compare("0x") == 0) {
                    ss << hex;
                } else {
                    ss << dec;
                }

                ss<<paramVal;

                if (!paramName.compare(std::string("boxWidth"))) ss>>boxWidth;
                else if (!paramName.compare(std::string("boxHeight"))) ss>>boxHeight;
                else if (!paramName.compare(std::string("ballRadius"))) ss>>ballRadius;
                else if (!paramName.compare(std::string("ballX"))) ss>>ballX;
                else if (!paramName.compare(std::string("ballY"))) ss>>ballY;
                else if (!paramName.compare(std::string("ballXSpeed"))) ss>>ballXSpeed;
                else if (!paramName.compare(std::string("ballYSpeed"))) ss>>ballYSpeed;

                else if (!paramName.compare(std::string("framerate"))) ss>>framerate;
                else if (!paramName.compare(std::string("tableColor"))) ss>>tableColor;
                else if (!paramName.compare(std::string("ballColor"))) ss>>ballColor;
                else if (!paramName.compare(std::string("enableBrickRegenerate"))) ss>>enableBrickRegenerate;
                else if (!paramName.compare(std::string("regeneratedBrickColor"))) ss>>regeneratedBrickColor;
                else if (!paramName.compare(std::string("regeneratedBrickProbability"))) ss>>regeneratedBrickProbability;
                else if (!paramName.compare(std::string("regeneratedBrickMaxLives"))) ss>>regeneratedBrickMaxLives;
                else if (!paramName.compare(std::string("showBrickLives"))) ss>>showBrickLives;

                else if (!paramName.compare(std::string("playGame"))) ss>>playGame;
                else if (!paramName.compare(std::string("initialLives"))) ss>>initialLives;
                else if (!paramName.compare(std::string("levelsOn"))) ss>>levelsOn;
                else if (!paramName.compare(std::string("powerUpsOn"))) ss>>powerUpsOn;
                else if (!paramName.compare(std::string("paddleWidth"))) ss>>paddleWidth;


                else errorType=ERROR_UNKNOWN_PARAM;

            } else {
                // Use new logic to handle brick definitions

                if (!line_tokens[0].compare("brick")) {

                    struct brickConfig brick;
                    stringstream ss;

                    ss.clear();
                    ss << hex << line_tokens[7];
                    int color;
                    ss >> color;
                    ss << dec;
                    brick.color = QColor(color);

                    ss.clear();
                    ss << line_tokens[6];
                    ss >> brick.visible;

                    ss.clear();
                    ss << line_tokens[5];
                    ss >> brick.lives;

                    ss.clear();
                    ss << line_tokens[4];
                    ss >> brick.height;

                    ss.clear();
                    ss << line_tokens[3];
                    ss >> brick.width;

                    ss.clear();
                    ss << line_tokens[2];
                    ss >> brick.y;

                    ss.clear();
                    ss << line_tokens[1];
                    ss >> brick.x;

                    bricks.push_back(brick);

                } else {
                    errorType=ERROR_UNKNOWN_PARAM;
                }

            }

        }

    } else {
        errorType=ERROR_NOFILE;
    }

}
double ConfigReader::getBallYSpeed()
{
    return ballYSpeed;
}

void ConfigReader::setBallYSpeed(double value)
{
    ballYSpeed = value;
}

double ConfigReader::getBallXSpeed()
{
    return ballXSpeed;
}

void ConfigReader::setBallXSpeed(double value)
{
    ballXSpeed = value;
}

unsigned int ConfigReader::getBallY()
{
    return ballY;
}

void ConfigReader::setBallY(unsigned int value)
{
    ballY = value;
}

unsigned int ConfigReader::getBallX()
{
    return ballX;
}

void ConfigReader::setBallX(unsigned int value)
{
    ballX = value;
}

unsigned int ConfigReader::getBallRadius()
{
    return ballRadius;
}

void ConfigReader::setBallRadius(unsigned int value)
{
    ballRadius = value;
}

unsigned int ConfigReader::getBoxHeight()
{
    return boxHeight;
}

void ConfigReader::setBoxHeight(unsigned int value)
{
    boxHeight = value;
}

unsigned int ConfigReader::getBoxWidth()
{
    return boxWidth;
}

void ConfigReader::setBoxWidth(unsigned int value)
{
    boxWidth = value;
}

int ConfigReader::getErrorType()
{
    return errorType;
}

void ConfigReader::setErrorType(int value)
{
    errorType = value;
}

/*
 * Stage 2 additions
 */

//! getter for bricks vector
const vector<ConfigReader::brickConfig> & ConfigReader::getBricks() {
    return bricks;
}


//! getter for framerate
int ConfigReader::getFramerate() {
    return framerate;
}

//! getter for tableColor
QColor ConfigReader::getTableColor() {
    return QColor(tableColor);
}

//! getter for ballColor
QColor ConfigReader::getBallColor() {
    return QColor(ballColor);
}

//! getter for enableBrickRegenerate
bool ConfigReader::getEnableBrickRegenerate() {
    return enableBrickRegenerate;
}

//! getter for regeneratedBrickColor
QColor ConfigReader::getRegeneratedBrickColor() {
    return QColor(regeneratedBrickColor);
}

//! getter for regeneratedBrickProbability
double ConfigReader::getRegeneratedBrickProbability() {
    return regeneratedBrickProbability;
}

//! getter for getRegeneratedBrickMaxLives
int ConfigReader::getRegeneratedBrickMaxLives() {
    return regeneratedBrickMaxLives;
}

//! getter for getShowBrickLives
bool ConfigReader::getShowBrickLives() {
    return showBrickLives;
}

//! getter for getPlayGame
bool ConfigReader::getPlayGame() {
    return playGame;
}

//! getter for getLevelsOn
bool ConfigReader::getLevelsOn() {
    return levelsOn;
}

//! getter for getPowerUpsOn
bool ConfigReader::getPowerUpsOn() {
    return powerUpsOn;
}

//! getter for getInitialLives
int ConfigReader::getIntialLives() {
    return initialLives;
}

//! getter for getInitialLives
qreal ConfigReader::getPaddleWidth() {
    return paddleWidth;
}

/*!
 * \brief Splits a string at delim into elements of a vector
 * \param str
 * \param delim
 * \return vector of tokens
 */
vector<string> ConfigReader::tokenise(const string &str, char delim) {
    vector<string> vec;
    stringstream ss(str);
    string token;

    while(getline(ss, token, delim)) {
        vec.push_back(token);
    }
    return vec;
}
