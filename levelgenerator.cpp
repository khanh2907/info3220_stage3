#include "levelgenerator.h"
#include <time.h>
LevelGenerator::LevelGenerator(int width, int height) :
    m_sceneWidth(width), m_sceneHeight(height)
{
}

std::vector<Brick *> LevelGenerator::generate(int level) {
    std::vector<Brick *> bricks;

    srand(time(NULL));

    int numOfBricks = 30 * level;

    int width = 50;
    int height = 20;

    int maxLives = 2 * level;

    std::vector<QColor> colors;

    for (int k = 0; k < maxLives; k++)
        colors.push_back(QColor::fromHsv(qrand() % 256, 255, 190));

    qreal x, y;

    for (int i = 0; i < m_sceneHeight/(2*height); i++) {
        for (int j = 0; j < m_sceneWidth/width; j++) {
            bool create = rand()%2;
            if (bricks.size() < numOfBricks && create) {
                x = j*width;
                y = i*height + 60;

                int lives = 1 + rand() % maxLives;

                bricks.push_back(new Brick( QRectF(x, y, width, height), lives, true, QBrush(colors[lives-1])));

            }
        }
    }

    return bricks;
}
