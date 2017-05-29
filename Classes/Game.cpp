#include "Game.h"
#include "SimpleAudioEngine.h"
#include "UIManager.h"
#include "SceneManager.h"
#include "GameInstance.h"

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

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));

    this->addChild(UIManager::GetInstance()->GenerateText("GScore", std::to_string(GameInstance::GetInstance()->GetScore()), "fonts/Marker Felt.ttf", 32.f, Vec2(playingSize.width * 0.5f, playingSize.height * 0.8f)));

    m_GridMap.init(playingSize);

    auto nodeItems = Node::create();
    nodeItems->setName("nodeItems");

    Size sprite_MudSize = Sprite::create("ZigzagGrass_Mud_Round.png")->getContentSize();

    for (int i = 0; i < m_GridMap.GetNumGrid(); ++i)
    {
        auto sprite_Mud = Sprite::create("ZigzagGrass_Mud_Round.png");

        sprite_Mud->setAnchorPoint(Vec2::ZERO);
        sprite_Mud->setPosition(m_GridMap.GetGrid(i)->GetPosition());
        sprite_Mud->setContentSize(Size(m_GridMap.GetGridSize().x, m_GridMap.GetGridSize().y));
        nodeItems->addChild(sprite_Mud, 0);
    }

    this->addChild(nodeItems, 1);

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

}

void Game::onMouseReleased(Event* event)
{

}



void Game::update(float dt)
{

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
