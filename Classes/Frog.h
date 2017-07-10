#ifndef FROG_H
#define FROG_H

#include "SpriteSheetAnimation.h"

class Frog : public SSAnimation
{
private:
	//Which lane does the frog belong to?
	int lane;

	//Stats of the frog
	int HP;
	float damage;
	float speed;
	//Is the frog ded?
	bool isDead;

	float currHp;
	float maxHp;
	cocos2d::CCProgressTimer* frogHealthBar;

public:
	//What type is the frog?
	enum TYPE
	{
		//Normal type
		GREEN = 0,

		//Speedy type
		YELLOW,

		//Tanky type
		BLUE,

		//Upgraded normal type
		RED,

	}FROG_TYPE;

	enum LANE {
		//Lane1
		LANE1 = 0,

		LANE2,

		LANE3,

		LANE4,

		LANE5,

		LANE6,
	}LANE_NUMBER;

	void init(TYPE frog, int lane);
	void healthBarInit();
	void runItDown(void);

	void attack(void);

	void update(float dt);

	//Setter-ish
	void takeDamage(int amount);
	void augmentSpeed(float newSpeed);
	float randomFloatBetween(float smallNumber, float bigNumber);
	//Getter
	int GetLane(void);
	int GetHP(void);
	float GetDamage(void);
	float GetSpeed(void);
	bool GetisDead(void);
	bool isActive = false;

	cocos2d::CCProgressTimer* getHealthSprite(void) { return frogHealthBar; }
};

#endif