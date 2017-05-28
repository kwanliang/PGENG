#pragma once

#include "cocos2d.h"

enum GridType
{
    Green,
    Blue,
    Purple,
    Orange,
    Yellow,
    Red,
    Rainbow,
};

class Grid
{
public:
    Grid() {};
    ~Grid() {};

    inline GridType GetType(void) { return type; }
    inline cocos2d::Vec2 GetPosition(void) { return position; }

    inline void SetType(GridType type) { this->type = type; }
    inline void SetPosition(cocos2d::Vec2 pos) { this->position = pos; }

private:
    GridType type;
    cocos2d::Vec2 position;
};