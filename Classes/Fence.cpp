#include "Fence.h"
#include "GameInstance.h"

Sprite* Fence::init(int lane)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	this->lane = lane;
	auto fenceSprite = Sprite::create("fence.png");
	//fenceSprite->setAnchorPoint(Vec2::ZERO);
	switch (lane) {
	case LANE::LANE1:
	{
		fenceSprite->setPosition(Vec2((visibleSize.width / 6) * 0.95, (visibleSize.height * 0.45)));
		break;
	}
	case LANE::LANE2:
	{
		fenceSprite->setPosition(Vec2((visibleSize.width / 6) * 1.7, (visibleSize.height * 0.45)));
		break;
	}
	case LANE::LANE3:
	{
		fenceSprite->setPosition(Vec2((visibleSize.width / 6) * 2.5, (visibleSize.height * 0.45)));
		break;
	}
	case LANE::LANE4:
	{
		fenceSprite->setPosition(Vec2((visibleSize.width / 6) * 3.3, (visibleSize.height * 0.45)));
		break;
	}
	case LANE::LANE5:
	{
		fenceSprite->setPosition(Vec2((visibleSize.width / 6) * 4.1, (visibleSize.height * 0.45)));
		break;
	}
	case LANE::LANE6:
	{
		fenceSprite->setPosition(Vec2((visibleSize.width / 6) * 4.9, (visibleSize.height * 0.45)));
		break;
	}
	default:
		break;
	}

	fenceSprite->setScale(1.8, 1);
	return fenceSprite;
}