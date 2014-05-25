#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H
#include <iostream>
#include <string>
#include <vector>
#include <QColor>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "brick.h"


class LevelGenerator
{
public:
    LevelGenerator(int width, int height);

    std::vector<Brick *> generate(int level);

private:
    int m_sceneWidth;
    int m_sceneHeight;
};

#endif // LEVELGENERATOR_H
