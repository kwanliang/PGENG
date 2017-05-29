#include "Timer.h"
#include "HelloWorldScene.h"

void CTimer::init(float timeAmt){
	auto visibleSize = Director::getInstance()->getVisibleSize();
	progressTimer = CCProgressTimer::create(CCSprite::create("SAOHealth.png"));
	if (progressTimer != NULL)
	{
		progressTimer->setType(kCCProgressTimerTypeBar);
		progressTimer->setMidpoint(Vec2(0, 0));
		progressTimer->setBarChangeRate(Vec2(1, 0));
		progressTimer->setPercentage(100);
		progressTimer->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.9f));
	}
	maxTime = timeAmt;
	currTime = maxTime;
}

void CTimer::update(float delta){
	currTime -= delta;
	progressTimer->setPercentage(100 * (currTime / maxTime));
	
}

void CTimer::reset(float timeAmt){
	currTime = timeAmt;
}