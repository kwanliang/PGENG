#include "SceneManager.h"

void SceneManager::SwitchScene(cocos2d::Scene* scene)
{
    CCDirector::getInstance()->replaceScene(TransitionFade::create(1.5, scene, Color3B(0, 255, 255)));
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}