#include "GridMap.h"

GridMap::GridMap()
{

}

GridMap::~GridMap()
{
    gridmap.clear();
}

void GridMap::init(Vec2 windowsize)
{
    row = 5;
    column = 6;
    numgrid = row * column;

    gridsize = Vec2(windowsize.x / column, (windowsize.y * 0.5f) / row);

    for (int x = 0; x < column; ++x)
    {
        for (int y = 0; y < row; ++y)
        {
            Grid* tempGrid = new Grid();
            tempGrid->SetPosition(Vec2(x * gridsize.x, y * gridsize.y));
            int tempRand = rand() % 7 - 1;
            tempGrid->SetType((GridType)tempRand);
            gridmap.push_back(tempGrid);
        }
    }
}