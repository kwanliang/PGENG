#include "Game.h"
#include "SimpleAudioEngine.h"
#include "UIManager.h"
#include "SceneManager.h"
#include "GameInstance.h"
#include "MainMenu.h"

USING_NS_CC;

Scene* Game::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = Game::create();

    // add layer as a child to scene
    scene->addChild(layer, 0, 999);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Game::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    SelectedGrid = NULL;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));

    //this->addChild(UIManager::GetInstance()->GenerateText("GScore", std::to_string(GameInstance::GetInstance()->GetScore()), "fonts/Marker Felt.ttf", 32.f, Vec2(playingSize.width * 0.5f, playingSize.height * 0.8f)));

    m_GridMap.init(playingSize);

    auto nodeItems = Node::create();
    nodeItems->setName("nodeItems");

    Size sprite_MudSize = Sprite::create("ZigzagGrass_Mud_Round.png")->getContentSize();

	Sprite* Background = Sprite::create("water.png");
	Background->setAnchorPoint(Vec2::ZERO);
	Background->setContentSize(visibleSize);
	this->addChild(Background);

    for (int i = 0; i < m_GridMap.GetNumGrid(); ++i)
    {
        //m_GridMap.GetGrid(i)->SetSprite(Sprite::create("ZigzagGrass_Mud_Round.png"));

        //m_GridMap.GetGrid(i)->GetSprite()->setAnchorPoint(Vec2::ZERO);
        //m_GridMap.GetGrid(i)->GetSprite()->setPosition(m_GridMap.GetGrid(i)->GetPosition());
        //m_GridMap.GetGrid(i)->GetSprite()->setContentSize(Size(m_GridMap.GetGridSize().x, m_GridMap.GetGridSize().y));
		nodeItems->addChild(m_GridMap.GetGrid(i)->GetSprite(), 0);
        nodeItems->addChild(m_GridMap.GetGrid(i)->GetAnimation()->getSprite(), 1);
    }

    this->addChild(nodeItems, 1);

	auto B_Back = UIManager::GetInstance()->GenerateButton("Back", "button.png", "buttonpressed.png", 16.f, Vec2(playingSize.width * 0.5f, playingSize.height));
	B_Back->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			break;
		case cocos2d::ui::Widget::TouchEventType::MOVED:
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			SceneManager::GetInstance()->SwitchScene(MainMenu::createScene());
			break;
		case cocos2d::ui::Widget::TouchEventType::CANCELED:
			break;
		default:
			break;
		}
	});
	this->addChild(B_Back);

	auto nodeTime = Node::create();
	nodeTime->setName("nodeTime");

	timer.init(10.f);


	nodeTime->addChild(timer.getSprite(), 1);
	this->addChild(nodeTime, 0);

	isHoldingBlock = false;

	//TESTING FROGS
	Frog* green = new Frog;
	green->init(Frog::TYPE::GREEN, Frog::LANE::LANE1);
	green->augmentSpeed(cocos2d::RandomHelper::random_int(1, 5));
	green->SetScale(Vec2(3, 3));
	frogList.push_back(green);
	this->addChild(green->getSprite(), 1);

	Frog* yellow = new Frog;
	yellow->init(Frog::TYPE::YELLOW, Frog::LANE::LANE2);
	yellow->augmentSpeed(cocos2d::RandomHelper::random_int(1, 5));
	yellow->SetScale(Vec2(3, 3));
	frogList.push_back(yellow);
	this->addChild(yellow->getSprite(), 1);

	Frog* blue = new Frog;
	blue->init(Frog::TYPE::BLUE, Frog::LANE::LANE3);
	blue->augmentSpeed(cocos2d::RandomHelper::random_int(1, 5));
	blue->SetScale(Vec2(3, 3));
	frogList.push_back(blue);
	this->addChild(blue->getSprite(), 1);

	Frog* red = new Frog;
	red->init(Frog::TYPE::RED, Frog::LANE::LANE4);
	red->augmentSpeed(cocos2d::RandomHelper::random_int(1, 5));
	red->SetScale(Vec2(3, 3));
	frogList.push_back(red);
	this->addChild(red->getSprite(), 1);

	Frog* red2 = new Frog;
	red2->init(Frog::TYPE::RED, Frog::LANE::LANE5);
	red2->augmentSpeed(cocos2d::RandomHelper::random_int(1, 5));
	red2->SetScale(Vec2(3, 3));
	frogList.push_back(red2);
	this->addChild(red2->getSprite(), 1);

	Frog* red3 = new Frog;
	red3->init(Frog::TYPE::RED, Frog::LANE::LANE6);
	red3->augmentSpeed(cocos2d::RandomHelper::random_int(1, 5));
	red3->SetScale(Vec2(3, 3));
	frogList.push_back(red3);
	this->addChild(red3->getSprite(), 1);

    auto keyboard_listener = EventListenerKeyboard::create();
    keyboard_listener->onKeyPressed = CC_CALLBACK_2(Game::onKeyPressed, this);
    keyboard_listener->onKeyReleased = CC_CALLBACK_2(Game::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboard_listener, this);
    auto mouse_listener = EventListenerMouse::create();
    mouse_listener->onMouseDown = CC_CALLBACK_1(Game::onMousePressed, this);
    mouse_listener->onMouseUp = CC_CALLBACK_1(Game::onMouseReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouse_listener, this);

    this->scheduleUpdate();

    return true;
}

void Game::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{

}

void Game::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
}

void Game::onMousePressed(Event* event)
{
    EventMouse* e = (EventMouse*)event;
    if (e->getMouseButton() == MOUSE_BUTTON_LEFT)
    {
        if (SelectedGrid == NULL)
        {
            SelectedGrid = m_GridMap.GetGridWithPos(Vec2(e->getCursorX(), e->getCursorY()));
        }
        else
        {
            Grid* temp = m_GridMap.GetGridWithPos(Vec2(e->getCursorX(), e->getCursorY()));
            if (temp != NULL)
            {
                Vec2 tempPos1 = temp->GetPosition();
                Vec2 tempPos2 = SelectedGrid->GetPosition();

                Vec2 tempSpritePos1 = temp->GetAnimation()->getSprite()->getPosition();
                Vec2 tempSpritePos2 = SelectedGrid->GetAnimation()->getSprite()->getPosition();

                temp->GetAnimation()->getSprite()->setPosition(tempPos2);
                SelectedGrid->GetAnimation()->getSprite()->setPosition(tempPos1);
                temp->SetPosition(tempPos2);
                SelectedGrid->SetPosition(tempPos1);

				m_GridMap.CheckForMatches();

                SelectedGrid = NULL;
            }
        }
    }
}

void Game::onMouseReleased(Event* event)
{

}

void Game::update(float dt)
{
	if (isHoldingBlock == true) {
		timer.update(dt);
	}

	for (int i = 0; i < frogList.size(); i++) {
		float a = frogList.at(i)->getPos().y;
		float b = frogList.at(i)->getPos().x;
		a -= frogList.at(i)->GetSpeed();
		frogList.at(i)->SetPos(Vec2(b, a));
	}
}

void Game::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
