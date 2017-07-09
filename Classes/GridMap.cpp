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

    for (int y = 0; y < row; ++y)
    {
        for (int x = 0; x < column; ++x)
        {
            Grid* tempGrid = new Grid();
            tempGrid->SetPosition(Vec2(x * gridsize.x + borderOffsetX, y * gridsize.y + borderOffsetY));
            tempGrid->SetIndex(Vec2(x, y));
            int tempRand = rand() % 5;
            tempGrid->SetType((GridType)tempRand);
            tempGrid->SetHaveMatch(false);

			auto lilypad = Sprite::create("lilypad.png");

			lilypad->setAnchorPoint(Vec2::ZERO);
			lilypad->setPosition(tempGrid->GetPosition());
			lilypad->setScale(0.8f);
			lilypad->setContentSize(Size(gridsize.x, gridsize.y));

            Butterfly* tempAnim = MakeAnimation(tempGrid->GetPosition(), (GridType)tempRand);

			tempGrid->SetSprite(lilypad);
			tempGrid->SetAnimation(tempAnim);

            gridmap.push_back(tempGrid);
        }
    }

    MaxPlayingField = gridmap[numgrid - 1]->GetPosition() + gridsize * 0.8f;
    MinPlayingField = gridmap[0]->GetPosition();

}

Butterfly* GridMap::MakeAnimation(Vec2 pos, GridType type)
{
    Butterfly* tempAnim = new Butterfly();

    switch (type)
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

    tempAnim->getSprite()->setAnchorPoint(Vec2::ZERO);
    tempAnim->SetPos(pos);
    tempAnim->SetScale(Vec2(0.4f, 0.4f));
    tempAnim->getSprite()->setContentSize(Size(gridsize.x, gridsize.y));

    return tempAnim;
}

void GridMap::CheckForMatches()
{
    for (auto it : gridmap)
    {
        if (!it->GetHaveMatch())
            CheckSurrondingMatch(it);
    }

    ResolveMatches();
}

void GridMap::CheckSurrondingMatch(Grid* grid)
{
    int counter = 0;
    for (int y = -1; y <= 1; ++y)
    {
        for (int x = -1; x <= 1; ++x)
        {
            if (abs(x) != abs(y))
            {
                Vec2 tempIndex = Vec2(grid->GetIndex().x + x, grid->GetIndex().y + y);
                //y * column + x
                if (tempIndex.x >= 0 && tempIndex.y >= 0 && tempIndex.x < column && tempIndex.y < row)
                {
                    Grid* GridChecker = GetGridWithIndex(tempIndex);
                    //if (grid != GridChecker)
                    {
                        if (tempIndex.y * column + tempIndex.x == 29)
                            GridChecker->GetType();
                        if (grid->GetType() == GridChecker->GetType())
                        {
                            grid->SetHaveMatch(true);
                            return;
                        }
                        //{
                        //    counter++;
                        //}

                        //if (counter >= 2)
                        //{
                        //grid->SetHaveMatch(true);
                        //return;
                        //}
                    }
                }
            }
        }
    }
}

void GridMap::ResolveMatches(void)
{
    for (auto it : gridmap)
    {
        if (it->GetHaveMatch())
        {
            int tempRand = rand() % 5;
            it->SetType((GridType)tempRand);
            //it->GetAnimation()->RemoveSprite();//((Butterfly::TYPE)tempRand);
            //it->SetAnimation(MakeAnimation(it->GetPosition(), (GridType)tempRand));

            it->SetHaveMatch(false);
        }
    }
}

Grid* GridMap::GetGridWithIndex(Vec2 index)
{
    for (auto it : gridmap)
    {
        if (it->GetIndex() == index)
            return it;
    }
    //return gridmap[index];

    return NULL;
}

Grid* GridMap::GetGridWithPos(Vec2 pos)
{
    for (auto it : gridmap)
    {
        Vec2 MaxAABB = it->GetPosition() + gridsize;
        Vec2 MinAABB = it->GetPosition();
        if (pos.x > MinAABB.x && pos.x < MaxAABB.x &&
            pos.y > MinAABB.y && pos.y < MaxAABB.y)
        {
            return it;
        }
    }
    
    return NULL;
}