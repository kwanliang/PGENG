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
    inline int GetLane(void) { return lane; }
    inline bool GetIsIterated(void) { return IsIterated; }
    inline bool GetHasMatch(void) { return HasMatch; }

    inline void SetType(GridType type) { this->type = type; }
    inline void SetPosition(Vec2 pos) { this->position = pos; }
    inline void SetIndex(Vec2 index) { this->index = index; }
	inline void SetSprite(Sprite* spr) { this->lilypad = spr; }
    inline void SetAnimation(Butterfly* spr) { this->animation = spr; }
    inline void SetLane(int lane) { this->lane = lane; }
    inline void SetIsIterated(bool iterated) { this->IsIterated = iterated; }
    inline void SetHasMatch(bool match) { this->HasMatch = match; }

private:
    GridType type;
    Vec2 index;
    Vec2 position;
	Sprite* lilypad;
	Butterfly* animation;
    int lane;
    bool IsIterated;
    bool HasMatch;
};