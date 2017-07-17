#pragma once

#include <vector>
#include <sstream>
#include <SimpleAudioEngine.h>
#include "cocos2d.h"
#include "GridMap.h"
#include "Frog.h"
#include "Butterfly.h"
#include "Timer.h"
#include "Projectile.h"
#include "WaveSystem.h"
#include "Fence.h"

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
    Projectile* FetchProjectile();
	void FreezeAllFrog();
    // implement the "static create()" method manually
    CREATE_FUNC(Game);

private:
    GridMap m_GridMap;
    Grid* SelectedGrid;

	std::vector<Frog*> frogList;
    std::vector<Projectile*> projectileList;


	Wave wave;
	Fence fence;
	cocos2d::Label* waveDisplay;
	std::stringstream Text;
	cocos2d::Label* scoreDisplay;
	Sprite* fenceSprite;

	int score;

	CTimer timer;
	Frog frogHealthBar;

	//Health stuff
	float frogLimit;
	float currHealth;
	float maxHealth;

	int speed;
	int playerHealth;
	bool tookDamage;
	bool isHoldingBlock;
	bool EnableInput;
	bool CheckMatches;

	//Powerup stuff
	cocos2d::Sprite* FreezePowerup;
	void ClickFreeze(Vec2 pos);
};
