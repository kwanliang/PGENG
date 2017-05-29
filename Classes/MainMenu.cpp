#include "MainMenu.h"
#include "SimpleAudioEngine.h"
#include "UIManager.h"
#include "SceneManager.h"
#include "Game.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer, 0, 999);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
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

    this->addChild(UIManager::GetInstance()->GenerateText("MMTitle", "Froggie Invasion", "fonts/Marker Felt.ttf", 32.f, Vec2(playingSize.width * 0.5f, playingSize.height * 0.8f)));

    auto B_StartGame = UIManager::GetInstance()->GenerateButton("Start Game", "button.png", "buttonpressed.png", 16.f, Vec2(playingSize.width * 0.5f, playingSize.height * 0.5f));
    B_StartGame->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
    {
        switch (type)
        {
        case cocos2d::ui::Widget::TouchEventType::BEGAN:
            break;
        case cocos2d::ui::Widget::TouchEventType::MOVED:
            break;
        case cocos2d::ui::Widget::TouchEventType::ENDED:
            SceneManager::GetInstance()->SwitchScene(HelloWorld::createScene());
            break;
        case cocos2d::ui::Widget::TouchEventType::CANCELED:
            break;
        default:
            break;
        }
    });
    this->addChild(B_StartGame);

    auto B_Options = UIManager::GetInstance()->GenerateButton("Options", "button.png", "buttonpressed.png", 16.f, Vec2(playingSize.width * 0.5f, playingSize.height * 0.4f));
    B_Options->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
    {
        switch (type)
        {
        case cocos2d::ui::Widget::TouchEventType::BEGAN:
            break;
        case cocos2d::ui::Widget::TouchEventType::MOVED:
            break;
        case cocos2d::ui::Widget::TouchEventType::ENDED:
            SceneManager::GetInstance()->SwitchScene(HelloWorld::createScene());
            break;
        case cocos2d::ui::Widget::TouchEventType::CANCELED:
            break;
        default:
            break;
        }
    });
    this->addChild(B_Options);

    auto B_Quit = UIManager::GetInstance()->GenerateButton("Quit Game", "button.png", "buttonpressed.png", 16.f, Vec2(playingSize.width * 0.5f, playingSize.height * 0.3f));
    B_Quit->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
    {
        switch (type)
        {
        case cocos2d::ui::Widget::TouchEventType::BEGAN:
            break;
        case cocos2d::ui::Widget::TouchEventType::MOVED:
            break;
        case cocos2d::ui::Widget::TouchEventType::ENDED:
            break;
        case cocos2d::ui::Widget::TouchEventType::CANCELED:
            break;
        default:
            break;
        }
    });
    this->addChild(B_Quit);

    auto keyboard_listener = EventListenerKeyboard::create();
    keyboard_listener->onKeyPressed = CC_CALLBACK_2(MainMenu::onKeyPressed, this);
    keyboard_listener->onKeyReleased = CC_CALLBACK_2(MainMenu::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboard_listener, this);
    auto mouse_listener = EventListenerMouse::create();
    mouse_listener->onMouseDown = CC_CALLBACK_1(MainMenu::onMousePressed, this);
    mouse_listener->onMouseUp = CC_CALLBACK_1(MainMenu::onMouseReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouse_listener, this);

    this->scheduleUpdate();

    return true;
}

void MainMenu::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
   
}

void MainMenu::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
}

void MainMenu::onMousePressed(Event* event)
{

}

void MainMenu::onMouseReleased(Event* event)
{

}

void MainMenu::update(float dt)
{
 
}

void MainMenu::menuCloseCallback(Ref* pSender)
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
