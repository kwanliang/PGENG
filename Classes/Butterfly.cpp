#include "Butterfly.h"

void Butterfly::init(TYPE Butterfly)
{
	//STATS ARE GONNA BE CHANGED WHEN GAMEPLAY IS IMPLETEMENTED FOR GAME BALANCING
	switch (Butterfly)
	{
	case TYPE::GREEN:
	{
		SetAnimation("butterfly.plist", "butterfly_green/%04d.png", 4);
		BUTTERFLY_TYPE = GREEN;
		break;
	}
	case TYPE::YELLOW:
	{
		SetAnimation("butterfly.plist", "butterfly_yellow/%04d.png", 4);
		BUTTERFLY_TYPE = YELLOW;
		break;
	}
	case TYPE::BLUE:
	{
		SetAnimation("butterfly.plist", "butterfly_blue/%04d.png", 4);
		BUTTERFLY_TYPE = BLUE;
		break;
	}
	case TYPE::RED:
	{
		SetAnimation("butterfly.plist", "butterfly_red/%04d.png", 4);
		BUTTERFLY_TYPE = RED;
		break;
	}
	case TYPE::RAINBOW:
	{
		SetAnimation("butterfly.plist", "butterfly_rainbow/%04d.png", 4);
		BUTTERFLY_TYPE = RAINBOW;
		break;
	}
	default:
		break;
	}
	isCombined = false;
	runAnimation();
}

void Butterfly::update(float dt)
{
}

void Butterfly::changeSprite(TYPE newType)
{
	switch (newType)
	{
	case TYPE::GREEN:
	{
		changeAnimation("butterfly_green/%04d.png", 4);
		BUTTERFLY_TYPE = GREEN;
		break;
	}
	case TYPE::YELLOW:
	{
		changeAnimation("butterfly_yellow/%04d.png", 4);
		BUTTERFLY_TYPE = YELLOW;
		break;
	}
	case TYPE::BLUE:
	{
		changeAnimation("butterfly_blue/%04d.png", 4);
		BUTTERFLY_TYPE = BLUE;
		break;
	}
	case TYPE::RED:
	{
		changeAnimation("butterfly_red/%04d.png", 4);
		BUTTERFLY_TYPE = RED;
		break;
	}
	case TYPE::RAINBOW:
	{
		changeAnimation("butterfly_rainbow/%04d.png", 4);
		BUTTERFLY_TYPE = RAINBOW;
		break;
	}
	default:
		break;
	}
}

//Setter-ish
void Butterfly::SendDownLane(int lane)
{
	//send down lane
}

//Getters
bool Butterfly::GetisCombined(void)
{
	return isCombined;
}