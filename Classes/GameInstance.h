#pragma once

#include "SingletonTemplate.h"

class GameInstance : public Singleton<GameInstance>
{
    friend Singleton<GameInstance>;
public:
    inline void IncrementScore(void) { score++; }
    inline int GetScore(void) { return score; }

private:
    GameInstance() { score = 0; };
    ~GameInstance() {};

    int score;

};