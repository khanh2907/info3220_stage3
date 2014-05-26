#include "player.h"

Player::Player(int lives, bool levelGen, bool powerUps) : m_lives(lives),
    m_score(0),
    m_currentLevel(1),
    m_roundStarted(false),
    m_levelGen(levelGen),
    m_powerUps(powerUps)
{}

int Player::getLives() {
    return m_lives;
}

int Player::getScore() {
    return m_score;
}

int Player::getCurrentLevel() {
    return m_currentLevel;
}

bool Player::getRoundStarted() {
    return m_roundStarted;
}

int Player::incrementLife() {
    m_lives += 1;
    return m_lives;
}

int Player::decrementLife() {
    m_lives -= 1;
    return m_lives;
}

int Player::increaseScore(int val) {
    m_score += val;
    return m_score;
}

int Player::increaseCurrentLevel() {
    m_currentLevel += 1;
    return m_currentLevel;
}

bool Player::setRoundStarted(bool val) {
    m_roundStarted = val;
}

bool Player::getLevelGen() {
    return m_levelGen;
}

bool Player::getPowerUps() {
    return m_powerUps;
}

void Player::resetStats() {
    m_score = 0;
    m_lives = 3;
    m_currentLevel = 1;
}
