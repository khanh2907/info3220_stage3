#include "player.h"

Player::Player(int lives) : m_lives(lives),
    m_score(0),
    m_currentLevel(0),
    m_roundStarted(false)
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