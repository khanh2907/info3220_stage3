#include "brick.h"
#include "configreader.h"
#include <sstream>
#include <QGraphicsScene>
#include "tablescene.h"

//! Brick constructor
Brick::Brick(const QRectF &rect,
             int lives,
             bool visible,
             const QBrush &fill_brush) :
    QGraphicsRectItem(rect),
    m_lives(lives),
    m_fillBrush(fill_brush)
{
    this->setVisible(visible);
}

/*!
 * \brief Brick copy constructor
 *
 * Explict copy constructor as base class 'QGraphicsItem' has private copy constructor
 *
 * \param other The object to copy to
 */
Brick::Brick(const Brick &other) :
    QGraphicsRectItem(other.rect()),
    m_lives(other.m_lives),
    m_linePen(other.m_linePen),
    m_fillBrush(other.m_fillBrush)
{
}

/*!
 * \brief Sets the state of the brick as the frame of the scene is advancing
 *
 * Called by the advance method of the parent Table.
 *
 * This method is called twice. The first time with step == 0
 * to indicate the scene is about to advance, and a second time
 * with step == 1 to indicate the scene is advancing.
 *
 * \param step
 */
void Brick::advance(int step) {

    if (step == 0) {
        // ignore that we are _about_ to advance
        return;
    }

    TableScene * tableScene = dynamic_cast<TableScene *>(scene());

    if (m_lives <= 0) {
        this->setVisible(false);

        qreal x = this->boundingRect().left();
        qreal y = this->boundingRect().top();
        tableScene->addPowerup(x, y);

        tableScene->removeBrick(this);




    }

    if (!tableScene->getPlayGame()) {

        ConfigReader *the_reader = ConfigReader::getInstance();

        if (the_reader->getEnableBrickRegenerate() && !this->isVisible()) {
            float rand_val = ((float) rand()) / (float) RAND_MAX; // random float between 0 and 1
            if (rand_val < the_reader->getRegeneratedBrickProbability()) {
                this->setVisible(true);
                this->m_lives = (rand() % the_reader->getRegeneratedBrickMaxLives()) + 1;
                m_fillBrush = QBrush(the_reader->getRegeneratedBrickColor());
            }
        }
    }

}

/*!
 * \brief Paints the brick object
 *
 * Performs the painting of the brick in the parent Table object using the given painter.
 *
 * \param painter in which to perform painting
 */

void Brick::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {

    painter->setBrush(m_fillBrush);
    painter->drawRect(this->rect());

    if (ConfigReader::getInstance()->getShowBrickLives()) {
        std::stringstream ss;
        ss << m_lives;
        painter->drawText(this->boundingRect(), Qt::AlignCenter, QString::fromStdString(ss.str()));
    }

}

/*
 * Getters and setters
 */

//! Setter for lives
Brick & Brick::setNumLives(int lives) {
    m_lives = lives;
    return *this;
}

//! Getter for lives
int Brick::getNumLives() {
    return m_lives;
}

//! Decrementor for lives
Brick & Brick::decLife() {
    m_lives--;
    this->update();
    return *this;
}

Brick & Brick::decLife(int damage) {
    m_lives -= damage;
    this->update();
    return *this;
}

//! Setter for fill brush
Brick & Brick::setFillBrush(const QBrush &fillBrush) {
    m_fillBrush = fillBrush;
    return *this;
}
