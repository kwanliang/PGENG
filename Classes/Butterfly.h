#ifndef BUTTERFLY_H
#define BUTTERFLY_H

#include "SpriteSheetAnimation.h"

class Butterfly : public SSAnimation
{
private:
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

	void init(TYPE Butterfly);

	void update(float dt);
	void SendDownLane(int lane);
	void changeSprite(TYPE newType);

	//Getter
	bool GetisCombined(void);
};

#endif