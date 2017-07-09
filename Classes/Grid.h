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
    inline Vec2 GetIndex(void) { return index; }
    inline Butterfly* GetAnimation(void) { return animation; }
	inline Sprite* GetSprite(void) { return lilypad; }
    inline bool GetHaveMatch(void) { return HaveMatch; }

    inline void SetType(GridType type) { this->type = type; }
    inline void SetPosition(Vec2 pos) { this->position = pos; }
    inline void SetIndex(Vec2 index) { this->index = index; }
	inline void SetSprite(Sprite* spr) { this->lilypad = spr; }
    inline void SetAnimation(Butterfly* spr) { this->animation = spr; }
    inline void SetHaveMatch(bool match) { this->HaveMatch = match; }

private:
    GridType type;
    Vec2 index;
    Vec2 position;
	Sprite* lilypad;
	Butterfly* animation;
    bool HaveMatch;
};