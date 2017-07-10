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
    Butterfly* MakeAnimation(Vec2 pos, GridType type);

    void CheckForMatches(void);
    void CheckSurrondingMatch(Grid* grid);
    void ResolveMatches(void);
    void ResetLaneMatches(void);
    Grid* GetGridWithIndex(Vec2 index);
    Grid* GetGridWithPos(Vec2 pos);

    inline Grid* GetGrid(int index) { return gridmap[index]; }
    inline int* GetLaneMatches(void) { return LaneMatches; }
    inline Vec2 GetGridSize(void) { return gridsize; }
    inline Vec2 GetMinPlayingField(void) { return MinPlayingField; }
    inline Vec2 GetMaxPlayingField(void) { return MaxPlayingField; }
    inline int GetNumGrid(void) { return numgrid; }


private:
    std::vector<Grid*> gridmap;
    int LaneMatches[6];
    Vec2 gridsize;

    Vec2 MaxPlayingField;
    Vec2 MinPlayingField;

    int row;
    int column;
    int numgrid;
};