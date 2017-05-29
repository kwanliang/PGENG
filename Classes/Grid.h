#pragma once

#include "cocos2d.h"
#include "Butterfly.h"

using namespace cocos2d;

enum GridType
{
	GREEN = 0,
	YELLOW,
	BLUE,
	RED,
	RAINBOW,
};

class Grid
{
public:
    Grid() {};
    ~Grid() {};

    inline GridType GetType(void) { return type; }
    inline Vec2 GetPosition(void) { return position; }
    inline Butterfly* GetAnimation(void) { return animation; }
	inline Sprite* GetSprite(void) { return lilypad; }

    inline void SetType(GridType type) { this->type = type; }
    inline void SetPosition(Vec2 pos) { this->position = pos; }
	inline void SetSprite(Sprite* spr) { this->lilypad = spr; }
    inline void SetAnimation(Butterfly* spr) { this->animation = spr; }

private:
    GridType type;
    Vec2 position;
	Sprite* lilypad;
	Butterfly* animation;
};