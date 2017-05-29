#ifndef BUTTERFLY_H
#define BUTTERFLY_H

#include "SpriteSheetAnimation.h"

class Butterfly : public SSAnimation
{
private:
	//Which lane does the frog belong to?
	Vec2 Grid;

	//Is the butterfly matched?
	bool isCombined;

public:
	enum TYPE
	{
		GREEN = 0,
		YELLOW,
		BLUE,
		RED,
		RAINBOW,

	}BUTTERFLY_TYPE;

	void init(TYPE Butterfly, Vec2 Grid);

	void update(float dt);
	void SendDownLane(int lane);

	//Getter
	bool GetisCombined(void);
};

#endif