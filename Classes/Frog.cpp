#include "Frog.h"
#include "GameInstance.h"

void Frog::init(TYPE frog, int lane)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	clearFrames();
	//STATS ARE GONNA BE CHANGED WHEN GAMEPLAY IS IMPLETEMENTED FOR GAME BALANCING
	switch (frog)
	{
		case TYPE::GREEN:
		{
			HP = 2;
			damage = 2;
			//speed = randomFloatBetween(0.1f, 0.5f);
			speed = 0.2f;
			SetAnimation("frog.plist", "frog_green/%04d.png", 4);
			break;
		}
		case TYPE::YELLOW:
		{
			HP = 1;
			damage = 1;
			//speed = randomFloatBetween(0.1f, 0.5f);
			speed = 0.5f;
			SetAnimation("frog.plist", "frog_yellow/%04d.png", 4);
			break;
		}
		case TYPE::BLUE:
		{
			HP = 3;
			damage = 2;
			//speed = randomFloatBetween(0.1f, 0.5f);
			speed = 0.1f;
			SetAnimation("frog.plist", "frog_blue/%04d.png", 4);
			break;
		}
		case TYPE::RED:
		{
			HP = 4;
			damage = 4;
			//speed = randomFloatBetween(0.1f, 0.5f);
			speed = 0.4f;
			SetAnimation("frog.plist", "frog_red/%04d.png", 4);
			break;
		}
		default:
			break;
	
	//STATS ARE GONNA BE CHANGED WHEN GAMEPLAY IS IMPLETEMENTED FOR GAME BALANCING
	switch (frog)
	{
	case TYPE::GREEN:
	{
		HP = 2;
		damage = 2;
		speed = randomFloatBetween(0.1f, 0.5f);
		//healthBarInit();

		SetAnimation("frog.plist", "frog_green/%04d.png", 4);
		break;
	}
	case TYPE::YELLOW:
	{
		HP = 1;
		damage = 1;
		speed = randomFloatBetween(0.1f, 0.5f);
		//healthBarInit();

		SetAnimation("frog.plist", "frog_yellow/%04d.png", 4);
		break;
	}
	case TYPE::BLUE:
	{
		HP = 3;
		damage = 2;
		speed = randomFloatBetween(0.1f, 0.5f);
		//healthBarInit();

		SetAnimation("frog.plist", "frog_blue/%04d.png", 4);
		break;
	}
	case TYPE::RED:
	{
		HP = 4;
		damage = 4;
		speed = randomFloatBetween(0.1f, 0.5f);
		//healthBarInit();

		SetAnimation("frog.plist", "frog_red/%04d.png", 4);
		break;
	}
	default:
		break;
	}

	this->lane = lane;

	switch (lane) {
	case LANE::LANE1:
	{
		SetPos(Vec2((visibleSize.width / 6) * 0.95, (visibleSize.height * 0.8)));
		break;
	}
	case LANE::LANE2:
	{
		SetPos(Vec2((visibleSize.width / 6) * 1.7, (visibleSize.height * 0.8)));
		break;
	}
	case LANE::LANE3:
	{
		SetPos(Vec2((visibleSize.width / 6) * 2.5, (visibleSize.height * 0.8)));
		break;
	}
	case LANE::LANE4:
	{
		SetPos(Vec2((visibleSize.width / 6) * 3.3, (visibleSize.height * 0.8)));
		break;
	}
	case LANE::LANE5:
	{
		SetPos(Vec2((visibleSize.width / 6) * 4.1, (visibleSize.height * 0.8)));
		break;
	}
	case LANE::LANE6:
	{
		SetPos(Vec2((visibleSize.width / 6) * 4.9, (visibleSize.height * 0.8)));
		break;
	}
	default:
		break;
	}
	isDead = false;
	SetScale(Vec2(3, 3));

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
		GameInstance::GetInstance()->IncrementScore();
		isActive = false;
		isDead = true;
		return;
	}
	

	//currHp -= GetDamage();
	//frogHealthBar->setPercentage(100 * (currHp / maxHp));
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

float Frog::GetDamage(void)
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
float Frog::randomFloatBetween(float smallNumber, float bigNumber) {
	float diff = bigNumber - smallNumber;
	return (((float)rand() / RAND_MAX) * diff) + smallNumber;

}

void Frog::healthBarInit() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	frogHealthBar = CCProgressTimer::create(CCSprite::create("frogHealthBar.png"));
	if (frogHealthBar != NULL)
	{
		frogHealthBar->setType(kCCProgressTimerTypeBar);
		frogHealthBar->setMidpoint(Vec2(0, 0));
		frogHealthBar->setBarChangeRate(Vec2(1, 0));
		frogHealthBar->setPercentage(100);
		frogHealthBar->setPosition(Vec2(getPos().x, getPos().y + 10));
		frogHealthBar->setScale(0.5f);

		
	}
	maxHp = 10;
	currHp = maxHp;
}

