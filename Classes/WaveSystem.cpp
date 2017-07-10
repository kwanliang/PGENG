#include "WaveSystem.h"

void Wave::init()
{
	//Max time per wave
	maxTime = 60.0f;
	timer.init(maxTime);

	spawnInterval = 2.0f;
	intervalTimer = 0.0f;

	currFrog = 0;
	leftoverFrog = 0;
	waveNumber = 1;
	//nextWave = false;

	frogLimit = 2 + waveNumber;
}

void Wave::update(float delta)
{
	//Times up
	if (timer.getcurrTime() <= 0.0f)
	{
		resetWaveLogic();
	}
	if (currFrog == frogLimit)
	{
		resetWaveLogic();
	}
	updateInterval();
}

void Wave::resetWaveLogic()
{
	//nextWave = true;
	waveNumber++;
	leftoverFrog = frogLimit - currFrog;
	if (leftoverFrog != 0)
	{
		frogLimit = 2 + waveNumber + leftoverFrog;
	}
	else
	{
		frogLimit = 2 + waveNumber;
	}
	currFrog = 0;
	timer.reset(maxTime);
	//nextWave = false;
}

void Wave::updateInterval()
{
	switch (waveNumber)
	{
	case 3:
		spawnInterval = 1.5f;
		break;
	case 6:
		spawnInterval = 1.0f;
		break;
	case 9:
		spawnInterval = 0.5f;
		break;
	default:
		break;
	}
}

bool Wave::spawnFrog(float dt)
{
	intervalTimer += dt;
	if (intervalTimer >= spawnInterval)
	{
		intervalTimer = 0.0f;
		return true;
	}
	return false;
}

int Wave::getFrogLimit()
{
	return frogLimit;
}

int Wave::getWave()
{
	return waveNumber;
}