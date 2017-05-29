#ifndef SPRITE_SHEET_ANIMATION_H
#define SPRITE_SHEET_ANIMATION_H

#include "cocos2d.h"
using namespace cocos2d;

class SSAnimation
{
private:
	SpriteFrameCache* spritecache;
	Vector<SpriteFrame*> animFrames;
	Sprite* animSprite;

	//Transform stuff
	Vec2 pos;
	Vec2 scale;

	int frames;

public:
	void SetAnimation(const char *plist, const char *image, int FrameCount);
	void runAnimation();

	//Setter
	void SetPos(Vec2 pos);
	void SetScale(Vec2 scale);

	//Getter
	Sprite* getSprite(void) { return animSprite; }
	Vec2 getPos(void) { return animSprite->getPosition(); }
};

#endif