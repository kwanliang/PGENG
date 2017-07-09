#pragma once

#include <vector>
#include <SimpleAudioEngine.h>
#include "cocos2d.h"
#include "GridMap.h"
#include "Frog.h"
#include "Butterfly.h"
#include "Timer.h"

using namespace cocos2d;

class Game : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    virtual void update(float dt);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    virtual void onKeyPressed(EventKeyboard::KeyCode, Event*);
    virtual void onKeyReleased(EventKeyboard::KeyCode, Event*);
    virtual void onMousePressed(Event*);
    virtual void onMouseReleased(Event*);
    virtual void onMouseMove(Event*);
	Frog* FetchFrog();
    // implement the "static create()" method manually
    CREATE_FUNC(Game);

private:
    GridMap m_GridMap;
    Grid* SelectedGrid;

	std::vector<Frog*> frogList;

	CTimer timer;

	float maxTime;
	float currTime;
	int frogLimit;
	int speed;
	int playerHealth;
	bool tookDamage;
	bool isHoldingBlock;
};
