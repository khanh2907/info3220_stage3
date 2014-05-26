#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
    Player(int lives, bool levelGen, bool powerUps);

    int getLives();
    int getScore();
    int getCurrentLevel();
    bool getRoundStarted();

    int incrementLife();
    int decrementLife();
    int increaseScore(int val);
    int increaseCurrentLevel();
    bool setRoundStarted(bool val);

    bool getLevelGen();
    bool getPowerUps();

    void resetStats();

private:
    int m_lives;
    int m_score;
    int m_currentLevel;
    bool m_roundStarted;
    bool m_levelGen;
    bool m_powerUps;
};

#endif // PLAYER_H
