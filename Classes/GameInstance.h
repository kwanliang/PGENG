#pragma once

#include "SingletonTemplate.h"

class GameInstance : public Singleton<GameInstance>
{
    friend Singleton<GameInstance>;
public:
    inline void IncrementScore(void) { score++; }
    inline int GetScore(void) { return score; }
	inline void IncrementFreeze(void) { freezePower++; }
	inline void DecrementFreeze(void) { freezePower--; }
	inline int GetFreeze(void) { return freezePower; }

private:
    GameInstance() { score = 0; 
					freezePower = 5;
					};
    ~GameInstance() {};

    int score;
	int freezePower;

};