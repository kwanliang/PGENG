#ifndef WAVESYSTEM_H
#define WAVESYSTEM_H

#include "Timer.h"

class Wave
{
private:
	float maxTime;
	float spawnInterval;
	float intervalTimer;
	int frogLimit;
	int leftoverFrog;
	int waveNumber;
	//bool nextWave;

	void resetWaveLogic();

public:
	CTimer timer;
	int currFrog;

	void init();
	void update(float delta);
	void updateInterval();

	//Should a frog spawn?
	bool spawnFrog(float dt);

	//Amount of frogs to spawn per wave / interval
	int getFrogLimit();
	int getWave();
};

//-0.5f sec interval every 3 wave, cap at 0.5f
//yellow start wave 2
//blue start wave 4
//red start wave 6

#endif	