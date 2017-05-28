#pragma once

#include <vector>
#include "cocos2d.h"
#include "Grid.h"

using namespace cocos2d;

class GridMap
{
public:
    GridMap();
    ~GridMap();

    void init(Vec2 windowsize);

    inline Grid* GetGrid(int index) { return gridmap[index]; }
    inline Vec2 GetGridSize(void) { return gridsize; }
    inline int GetNumGrid(void) { return numgrid; }

private:
    std::vector<Grid*> gridmap;
    Vec2 gridsize;

    int row;
    int column;
    int numgrid;
};