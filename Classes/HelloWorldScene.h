#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include <vector>
#include "cocos2d.h"
#include "Character.h"
#include "Frog.h"
#include "Butterfly.h"
#include "Timer.h"
#include <map>

using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

	//std::vector<EventKeyboard::KeyCode> heldKeys;
	std::vector<int> heldMouse;

    virtual bool init();
	virtual void update(float dt);

	Frog* FetchFrog();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	//void onKeyHold(float interval);
	//void onMouseHold(float interval);
	virtual void onKeyPressed(EventKeyboard::KeyCode, Event*);
	virtual void onKeyReleased(EventKeyboard::KeyCode, Event*);
	virtual void onMousePressed(Event*);
	virtual void onMouseReleased(Event*);
	virtual void onMouseMoved(Event*);
	virtual void onMouseHold(float interval);
    
	inline GameChar* getChar() { return &hero; }

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
	GLProgram* shaderCharEffect;
	GLProgram* proPostProcess;
	RenderTexture* rendtex;
	Sprite* rendtexSprite;
	cocos2d::Label * label;
	Vec2 mLoc;
	Vec2 mLocInc;
	float maxTime;
	float currTime;
	GameChar hero;
	CTimer timer;
	int speed;
	std::vector<Frog*> frogList;
	std::vector<Butterfly*> butterflyList;

	bool isHoldingBlock;
};

#endif // __HELLOWORLD_SCENE_H__
