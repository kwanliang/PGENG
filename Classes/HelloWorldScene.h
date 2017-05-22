#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include <vector>
#include "cocos2d.h"
#include "Character.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

	//std::vector<EventKeyboard::KeyCode> heldKeys;
	//std::vector<int> heldButtons;

    virtual bool init();
	virtual void update(float);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	//void onKeyHold(float interval);
	//void onMouseHold(float interval);
	virtual void onKeyPressed(EventKeyboard::KeyCode, Event*);
	virtual void onKeyReleased(EventKeyboard::KeyCode, Event*);
	virtual void onMousePressed(Event*);
	virtual void onMouseReleased(Event*);
    
	inline GameChar* getChar() { return &hero; }

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
	GLProgram* shaderCharEffect;
	GLProgram* proPostProcess;
	RenderTexture* rendtex;
	Sprite* rendtexSprite;

	Vec2 mLoc;
	Vec2 mLocInc;

	GameChar hero;
};

#endif // __HELLOWORLD_SCENE_H__
