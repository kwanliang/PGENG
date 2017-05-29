#include "Butterfly.h"

void Butterfly::init(TYPE Butterfly, Vec2 Grid)
{
	//STATS ARE GONNA BE CHANGED WHEN GAMEPLAY IS IMPLETEMENTED FOR GAME BALANCING
	switch (Butterfly)
	{
	case TYPE::GREEN:
	{
		SetAnimation("butterfly.plist", "butterfly_green/%04d.png", 4);
		break;
	}
	case TYPE::YELLOW:
	{
		SetAnimation("butterfly.plist", "butterfly_yellow/%04d.png", 4);
		break;
	}
	case TYPE::BLUE:
	{
		SetAnimation("butterfly.plist", "butterfly_blue/%04d.png", 4);
		break;
	}
	case TYPE::RED:
	{
		SetAnimation("butterfly.plist", "butterfly_red/%04d.png", 4);
		break;
	}
	case TYPE::RAINBOW:
	{
		SetAnimation("butterfly.plist", "butterfly_rainbow/%04d.png", 4);
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