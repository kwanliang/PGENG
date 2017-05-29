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

    gridsize = Vec2(windowsize.x / column, (windowsize.y * 0.5f) / row) * 0.8f;

	float borderOffsetX = windowsize.x * 0.1f;
	float borderOffsetY = windowsize.y * 0.1f;

    for (int x = 0; x < column; ++x)
    {
        for (int y = 0; y < row; ++y)
        {
            Grid* tempGrid = new Grid();
            tempGrid->SetPosition(Vec2(x * gridsize.x + borderOffsetX, y * gridsize.y + borderOffsetY));
            int tempRand = rand() % 5;
            tempGrid->SetType((GridType)tempRand);

			Butterfly* tempAnim = new Butterfly();

			auto lilypad = Sprite::create("lilypad.png");

            switch (tempGrid->GetType())
            {
            case GREEN:
				tempAnim->init(Butterfly::TYPE::GREEN, Vec2(1, 1));
                break;
            case BLUE:
				tempAnim->init(Butterfly::TYPE::BLUE, Vec2(1, 1));
                break;
            case YELLOW:
				tempAnim->init(Butterfly::TYPE::YELLOW, Vec2(1, 1));
                break;
            case RED:
				tempAnim->init(Butterfly::TYPE::RED, Vec2(1, 1));
                break;
            case RAINBOW:
				tempAnim->init(Butterfly::TYPE::RAINBOW, Vec2(1, 1));
                break;
            default:
                break;
            }

			lilypad->setAnchorPoint(Vec2::ZERO);
			lilypad->setPosition(tempGrid->GetPosition());
			lilypad->setScale(0.8f);
			lilypad->setContentSize(Size(gridsize.x, gridsize.y));

			tempAnim->getSprite()->setAnchorPoint(Vec2::ZERO);
			tempAnim->SetPos(tempGrid->GetPosition());
			tempAnim->SetScale(Vec2(0.4f, 0.4f));
			tempAnim->getSprite()->setContentSize(Size(gridsize.x, gridsize.y));

			tempGrid->SetSprite(lilypad);
			tempGrid->SetAnimation(tempAnim);

            gridmap.push_back(tempGrid);
        }
    }
}

void GridMap::CheckForMatches()
{

}

void GridMap::CheckSurrondingMatch(int index, int& counter)
{
	
}

Grid* GridMap::GetGridWithPos(Vec2 pos)
{
    for (int i = 0; i < numgrid; ++i)
    {
        Vec2 MaxAABB = gridmap[i]->GetPosition() + gridsize;
        Vec2 MinAABB = gridmap[i]->GetPosition();
        if (pos.x > MinAABB.x && pos.x < MaxAABB.x &&
            pos.y > MinAABB.y && pos.y < MaxAABB.y)
        {
            return gridmap[i];
        }
    }
    
    return NULL;
}