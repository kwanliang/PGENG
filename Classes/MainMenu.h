#pragma once

#include <vector>
#include "cocos2d.h"

using namespace cocos2d;

class MainMenu : public cocos2d::Layer
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

    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);

private:
};
