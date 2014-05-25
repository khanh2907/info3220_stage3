#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
    Player(int lives);

    int getLives();
    int getScore();
    int getCurrentLevel();
    bool getRoundStarted();

    int decrementLife();
    int increaseScore(int val);
    int increaseCurrentLevel();
    bool setRoundStarted(bool val);

    void resetStats();

private:
    int m_lives;
    int m_score;
    int m_currentLevel;
    bool m_roundStarted;
};

#endif // PLAYER_H
