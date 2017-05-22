#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class GameChar
{
private:
	cocos2d::Sprite* mainSprite;
	int intDirX, intDirY;
	float fSpeed, fmaxSpeed;

public:
	void init(const char* SourceName, const char* CharName, float posX, float posY);
	void MoveChar(int DirX, int DirY);
	void MoveCharByCoord(float fX, float fY);
	void Stop(void);
	void update(float delta);

	cocos2d::Sprite* getSprite(void) { return mainSprite; }
};