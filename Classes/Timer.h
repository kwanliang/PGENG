#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class CTimer
{
private:
	cocos2d::CCProgressTimer* progressTimer;
	float maxTime;
	float currTime;

public:
	void init(float timeAmt);
	void reset(float timeAmt);
	
	void update(float delta);

	cocos2d::CCProgressTimer* getSprite(void) { return progressTimer; }
};