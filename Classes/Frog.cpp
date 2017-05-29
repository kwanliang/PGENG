#include "Frog.h"

void Frog::init(TYPE frog, int lane)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//STATS ARE GONNA BE CHANGED WHEN GAMEPLAY IS IMPLETEMENTED FOR GAME BALANCING
	switch (frog)
	{
		case TYPE::GREEN:
		{
			HP = 2;
			damage = 2;
			speed = 2;
			SetAnimation("frog.plist", "frog_green/%04d.png", 4);
			break;
		}
		case TYPE::YELLOW:
		{
			HP = 1;
			damage = 1;
			speed = 3;
			SetAnimation("frog.plist", "frog_yellow/%04d.png", 4);
			break;
		}
		case TYPE::BLUE:
		{
			HP = 3;
			damage = 2;
			speed = 1;
			SetAnimation("frog.plist", "frog_blue/%04d.png", 4);
			break;
		}
		case TYPE::RED:
		{
			HP = 4;
			damage = 4;
			speed = 2;
			SetAnimation("frog.plist", "frog_red/%04d.png", 4);
			break;
		}
		default:
			break;
	}
	switch (lane) {
		case LANE::LANE1:
		{
			SetPos(Vec2((visibleSize.width / 6) * 0.5 , (visibleSize.height * 0.8)));
			break;
		}
		case LANE::LANE2:
		{
			SetPos(Vec2((visibleSize.width /6) * 1.5 , (visibleSize.height * 0.8)));
			break;
		}
		case LANE::LANE3:
		{
			SetPos(Vec2((visibleSize.width / 6) * 2.5, (visibleSize.height * 0.8)));
			break;
		}
		case LANE::LANE4:
		{
			SetPos(Vec2((visibleSize.width / 6) * 3.5, (visibleSize.height * 0.8)));
			break;
		}
		case LANE::LANE5:
		{
			SetPos(Vec2((visibleSize.width / 6) * 4.5, (visibleSize.height * 0.8)));
			break;
		}
		case LANE::LANE6:
		{
			SetPos(Vec2((visibleSize.width / 6) * 5.5, (visibleSize.height * 0.8)));
			break;
		}
		default:
			break;
	}
	isDead = false;
	
	runAnimation();
}

void Frog::runItDown(void)
{
	auto move = MoveBy::create(0, Vec2(0, speed));
	
	
	//run down the lane
}

void Frog::attack(void)
{
	//attack the barrier, attack delay MIGHT be added next time idk
}

void Frog::update(float dt)
{
	if (HP <= 0)
	{
		isDead = true;
		return;
	}
	runItDown();
	//runAnimation();
}

//Setter-ish
void Frog::takeDamage(int amount)
{
	if (isDead)
	{
		return;
	}
	HP -= amount;
}
void Frog::augmentSpeed(float newSpeed)
{
	if (isDead)
	{
		return;
	}
	speed = newSpeed;
}

//Getters
int Frog::GetLane(void)
{
	return lane;
}
int Frog::GetHP(void)
{
	return HP;
}
int Frog::GetDamage(void)
{
	return damage;
}
float Frog::GetSpeed(void)
{
	return speed;
}
bool Frog::GetisDead(void)
{
	return isDead;
}

