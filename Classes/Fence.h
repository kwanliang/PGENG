#pragma once

#include "SpriteSheetAnimation.h"

class Fence
{
private:
	//Which lane does the frog belong to?
	int lane;

public:
	enum LANE {
		//Lane1
		LANE1 = 0,

		LANE2,

		LANE3,

		LANE4,

		LANE5,

		LANE6,
	}LANE_NUMBER;

	Sprite* init(int lane);

	void update(float dt);

	//Getter
	int GetLane(void);
	bool isActive = false;

};

