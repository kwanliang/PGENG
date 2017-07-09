#include "SpriteSheetAnimation.h"

#include "HelloWorldScene.h"

void SSAnimation::SetAnimation(const char *plist, const char *image, int FrameCount)
{	
	frames = FrameCount;
	spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile(plist);

	char str[100];
	for (int i = 1; i <= FrameCount; i++) 
	{
		sprintf(str, image, i);
		animFrames.pushBack(spritecache->getSpriteFrameByName(str));
	}
	animSprite = Sprite::createWithSpriteFrame(animFrames.front());
}

void SSAnimation::runAnimation()
{
	//Run the animation
	auto animation = Animation::createWithSpriteFrames(animFrames, 1.0f / frames);
	animSprite->runAction(RepeatForever::create(Animate::create(animation)));
}

void SSAnimation::changeAnimation(const char *image, int FrameCount)
{
	//Stops current animation and clears it
	animSprite->stopAllActions();
	animFrames.clear();

	char str[100];
	for (int i = 1; i <= FrameCount; i++)
	{
		sprintf(str, image, i);
		animFrames.pushBack(spritecache->getSpriteFrameByName(str));
	}
	//animSprite = Sprite::createWithSpriteFrame(animFrames.front());
	auto animation = Animation::createWithSpriteFrames(animFrames, 1.0f / frames);
	animSprite->runAction(RepeatForever::create(Animate::create(animation)));
}

void SSAnimation::SetPos(Vec2 pos)
{
	//Set the pos
	this->pos = pos;
	animSprite->setPosition(this->pos);
}

void SSAnimation::SetScale(Vec2 scale)
{
	//Set the scale
	this->scale = scale;
	animSprite->setScaleX(this->scale.x);
	animSprite->setScaleY(this->scale.y);
}