#pragma once

#include "SingletonTemplate.h"
#include "cocos2d.h"

using namespace cocos2d;

class SceneManager : public Singleton<SceneManager>
{
	friend Singleton<SceneManager>;
public:
    void SwitchScene(Scene* scene);

private:
	SceneManager();
	~SceneManager();
};