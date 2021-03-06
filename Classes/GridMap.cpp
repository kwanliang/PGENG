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
	ResetLaneMatches();

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
			tempGrid->SetLane(x);
			tempGrid->SetIsIterated(false);
			tempGrid->SetHasMatch(false);

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
		tempAnim->init(Butterfly::TYPE::GREEN);
		break;
	case BLUE:
		tempAnim->init(Butterfly::TYPE::BLUE);
		break;
	case YELLOW:
		tempAnim->init(Butterfly::TYPE::YELLOW);
		break;
	case RED:
		tempAnim->init(Butterfly::TYPE::RED);
		break;
	case RAINBOW:
		tempAnim->init(Butterfly::TYPE::RAINBOW);
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

bool GridMap::CheckForMatches()
{
	for (auto it : gridmap)
	{
		if (!it->GetHasMatch() && !it->GetIsIterated())
		{
			it->SetIsIterated(true);
			std::list<Grid*> counter;

			counter.push_back(it);

			CheckSurrondingMatch(it, counter);

			if (counter.size() >= 3)
			{
				for (auto it : counter)
					it->SetHasMatch(true);
			}

			counter.clear();
		}
	}

	return ResolveMatches();
}

void GridMap::CheckSurrondingMatch(Grid* grid, std::list<Grid*>& counter)
{
	for (int y = -1; y <= 1; ++y)
	{
		for (int x = -1; x <= 1; ++x)
		{
			if (abs(x) != abs(y))
			{
				Vec2 tempIndex = Vec2(grid->GetIndex().x + x, grid->GetIndex().y + y);

				if (tempIndex.x >= 0 && tempIndex.y >= 0 && tempIndex.x < column && tempIndex.y < row)
				{
					Grid* GridChecker = GetGridWithIndex(tempIndex);
					if (!GridChecker->GetHasMatch() && !GridChecker->GetIsIterated())
					{
						if (grid->GetType() == GridChecker->GetType())
						{
							GridChecker->SetIsIterated(true);
							counter.push_back(GridChecker);
							CheckSurrondingMatch(GridChecker, counter);
						}
					}
				}
			}
		}
	}
}

bool GridMap::ResolveMatches(void)
{
	bool hasMatches = false;
	for (auto it : gridmap)
	{
		if (it->GetHasMatch())
		{
			hasMatches = true;
			LaneMatches[it->GetLane()]++;
			int tempRand = it->GetType();
			while (tempRand == it->GetType())
			{
				tempRand = rand() % 5;
			}
			it->SetType((GridType)tempRand);
			it->GetAnimation()->changeSprite((Butterfly::TYPE)tempRand);
		}
		ResetGrid(it);
	}

	return hasMatches;
}

void GridMap::SwitchGrid(Grid* grid1, Grid* grid2)
{
	// Set Temporarys
	Vec2 tempPos1 = grid1->GetPosition();
	Vec2 tempPos2 = grid2->GetPosition();
	Vec2 tempIndex1 = grid1->GetIndex();
	Vec2 tempIndex2 = grid2->GetIndex();
	//GridType tempType1 = grid1->GetType();
	//GridType tempType2 = grid2->GetType();
	int tempLane1 = grid1->GetLane();
	int tempLane2 = grid2->GetLane();

	// Switch Type
	//grid1->SetType(tempType1);
	//grid2->SetType(tempType2);
	//swapmap.emplace_back(grid1, grid2);

	// Switch Position
	grid1->GetAnimation()->getSprite()->setPosition(tempPos2);
	grid2->GetAnimation()->getSprite()->setPosition(tempPos1);
	grid1->SetPosition(tempPos2);
	grid2->SetPosition(tempPos1);

	// Switch Index
	grid1->SetIndex(tempIndex2);
	grid2->SetIndex(tempIndex1);



	// Switch Lane
	grid1->SetLane(tempLane2);
	grid2->SetLane(tempLane1);
}

bool GridMap::SwapAnimation(Grid* grid1, Grid* grid2, float dt)
{
	if (grid1->GetAnimation()->getSprite()->getPosition() != grid2->GetAnimation()->getSprite()->getPosition())
	{
		Vec2 temp1 = grid1->GetAnimation()->getSprite()->getPosition() * dt;
		Vec2 temp2 = grid2->GetAnimation()->getSprite()->getPosition() * dt;
		grid1->GetAnimation()->getSprite()->setPosition(grid1->GetAnimation()->getSprite()->getPosition() + temp2);
		grid2->GetAnimation()->getSprite()->setPosition(grid2->GetAnimation()->getSprite()->getPosition() + temp1);
		return true;
	}

	Vec2 tempPos1 = grid1->GetPosition();
	Vec2 tempPos2 = grid2->GetPosition();

	grid1->GetAnimation()->getSprite()->setPosition(tempPos2);
	grid2->GetAnimation()->getSprite()->setPosition(tempPos1);

	return false;
}

void GridMap::ResetGrid(Grid* grid)
{
	grid->SetIsIterated(false);
	grid->SetHasMatch(false);
}

void GridMap::ResetLaneMatches(void)
{
	for (int i = 0; i < 6; ++i)
	{
		LaneMatches[i] = 0;
	}
}

Grid* GridMap::GetGridWithIndex(Vec2 index)
{
	for (auto it : gridmap)
	{
		if (it->GetIndex() == index)
			return it;
	}

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

void GridMap::update(float dt)
{
	//for (std::list<std::pair<Grid*, Grid*>>::iterator it = swapmap.begin(); it != swapmap.end();)
	//{
	//    if (SwapAnimation(it->first, it->second, dt))
	//        NULL;
	//    else
	//        ++it;
	//}
}