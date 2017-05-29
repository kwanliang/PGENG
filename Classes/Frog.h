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
	int damage;
	float speed;

	//Is the frog ded?
	bool isDead;

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

	void init(TYPE frog, int lane);
	void runItDown(void);
	void attack(void);

	void update(float dt);

	//Setter-ish
	void takeDamage(int amount);
	void augmentSpeed(float newSpeed);

	//Getter
	int GetLane(void);
	int GetHP(void);
	int GetDamage(void);
	float GetSpeed(void);
	bool GetisDead(void);
};

#endif