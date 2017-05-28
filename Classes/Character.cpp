#include "Character.h"
#include "HelloWorldScene.h"

void GameChar::init(const char* SourceName, const char* CharName, float posX, float posY)
{
	mainSprite = Sprite::create(SourceName);
	mainSprite->setAnchorPoint(Vec2::ZERO);
	mainSprite->setPosition(posX, posY);
	mainSprite->setName(CharName);
	intDirX = 0;
	intDirY = 0;
	fSpeed = 0.01f;
	fmaxSpeed = 5.f;

	Stop();
}

void GameChar::MoveChar(int DirX, int DirY)
{
	if (intDirX < fmaxSpeed && intDirX > -fmaxSpeed)
		intDirX += DirX;
	if (intDirY < fmaxSpeed && intDirY > -fmaxSpeed)
		intDirY += DirY;

	mainSprite->stopAllActions();

	Vector<SpriteFrame*> animFrames;
	if (intDirX > 0)
	{
		animFrames.reserve(3);
		animFrames.pushBack(SpriteFrame::create("Blue_Right1.png", Rect(0, 0, 59, 81)));
		animFrames.pushBack(SpriteFrame::create("Blue_Right2.png", Rect(0, 0, 59, 81)));
		animFrames.pushBack(SpriteFrame::create("Blue_Right3.png", Rect(0, 0, 59, 81)));
	}
	else if (intDirX < 0)
	{
		animFrames.reserve(3);
		animFrames.pushBack(SpriteFrame::create("Blue_Left1.png", Rect(0, 0, 59, 81)));
		animFrames.pushBack(SpriteFrame::create("Blue_Left2.png", Rect(0, 0, 59, 81)));
		animFrames.pushBack(SpriteFrame::create("Blue_Left3.png", Rect(0, 0, 59, 81)));
	}
	else
	{
		animFrames.reserve(4);
		if (intDirY > 0)
		{
			animFrames.pushBack(SpriteFrame::create("Blue_Back2.png", Rect(0, 0, 65, 81)));
			animFrames.pushBack(SpriteFrame::create("Blue_Back1.png", Rect(0, 0, 65, 81)));
			animFrames.pushBack(SpriteFrame::create("Blue_Back3.png", Rect(0, 0, 65, 81)));
			animFrames.pushBack(SpriteFrame::create("Blue_Back1.png", Rect(0, 0, 65, 81)));
		}
		else
		{
			animFrames.pushBack(SpriteFrame::create("Blue_Front2.png", Rect(0, 0, 65, 81)));
			animFrames.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0, 0, 65, 81)));
			animFrames.pushBack(SpriteFrame::create("Blue_Front3.png", Rect(0, 0, 65, 81)));
			animFrames.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0, 0, 65, 81)));
		}
	}

	// Create the animation out of the frames
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	Animate* animateWalk = Animate::create(animation);

	// Run it and repeat it forever
	mainSprite->runAction(RepeatForever::create(animateWalk));
}

void GameChar::MoveCharByCoord(float fX, float fY)
{
	mainSprite->stopAllActions();
	float diffX = fX - mainSprite->getPosition().x;
	float diffY = fY - mainSprite->getPosition().y;
	Vec2 vec = Vec2(diffX, diffY);
	auto moveEvent = MoveBy::create(vec.length() * fSpeed, vec);
	mainSprite->stopAllActions();

	auto callbackStop = CallFunc::create([]() {
		auto scene = Director::getInstance()->getRunningScene();
		auto layer = scene->getChildByTag(999);
		HelloWorld* helloLayer = dynamic_cast<HelloWorld*>(layer);
		if (helloLayer != NULL)
			helloLayer->getChar()->Stop();
	});
	auto seq = Sequence::create(moveEvent, callbackStop, nullptr);
	mainSprite->runAction(seq);

	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(4);
	animFrames.pushBack(SpriteFrame::create("Blue_Back2.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Blue_Back1.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Blue_Back3.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Blue_Back1.png", Rect(0, 0, 65, 81)));

	// Create the animation out of the frames
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.5f);
	Animate* animateBack = Animate::create(animation);

	// Run it and repeat it forever
	mainSprite->runAction(RepeatForever::create(animateBack));
}

void GameChar::Stop(void)
{
	intDirX = 0;
	intDirY = 0;

	mainSprite->stopAllActions();
	// Allow sprite to animate

	Vector<SpriteFrame*> animFrames;
	animFrames.reserve(4);
	animFrames.pushBack(SpriteFrame::create("Blue_Front2.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Blue_Front3.png", Rect(0, 0, 65, 81)));
	animFrames.pushBack(SpriteFrame::create("Blue_Front1.png", Rect(0, 0, 65, 81)));

	// Create the animation out of the frames
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.5f);
	Animate* animateIdle = Animate::create(animation);

	// Run it and repeat it forever
	mainSprite->runAction(RepeatForever::create(animateIdle));
}

void GameChar::update(float delta)
{
	if (intDirX != 0 || intDirY != 0)
	{
		auto moveEvent = MoveBy::create(fSpeed, Vec2(intDirX, intDirY));
		mainSprite->runAction(moveEvent);
	}
}