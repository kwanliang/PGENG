#include "Game.h"
#include "SimpleAudioEngine.h"
#include "UIManager.h"
#include "SceneManager.h"
#include "GameInstance.h"
#include "MainMenu.h"

#include "platform/CCPlatformMacros.h"
#include <random>
#include <windows.h>

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

	// Random seed
	//srand(time(NULL));

	SelectedGrid = NULL;

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Size playingSize = Size(visibleSize.width, visibleSize.height - (visibleSize.height / 8));

	//this->addChild(UIManager::GetInstance()->GenerateText("GScore", std::to_string(GameInstance::GetInstance()->GetScore()), "fonts/Marker Felt.ttf", 32.f, Vec2(playingSize.width * 0.5f, playingSize.height * 0.8f)));

	m_GridMap.init(playingSize);

	auto drawnode = DrawNode::create();
	drawnode->drawLine(m_GridMap.GetMinPlayingField(), m_GridMap.GetMaxPlayingField(), Color4F(1.0, 0.0, 0.0, 1.0));
	addChild(drawnode);

	auto nodeItems = Node::create();
	nodeItems->setName("nodeItems");

	Size sprite_MudSize = Sprite::create("ZigzagGrass_Mud_Round.png")->getContentSize();

	Sprite* Background = Sprite::create("background.png");
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

	FreezePowerup = Sprite::create("freeze.png");
	FreezePowerup->setPosition(Vec2(70, 730));
	FreezePowerup->setScaleX(3);
	FreezePowerup->setScaleY(3);

	this->addChild(FreezePowerup);

	auto nodeTime = Node::create();
	nodeTime->setName("nodeTime");

	playerHealth = 10;


	timer.init(playerHealth);
	currHealth = 0.f;
	maxHealth = 0.f;

	wave.init();
	for (int i = 0; i < 6; i++) {
	
		this->addChild(fence.init(i), 1);
	}

	//nodeTime->addChild(wave.timer.getSprite(), 1);
	nodeTime->addChild(timer.getSprite(),1);

	this->addChild(nodeTime, 0);

	//auto frogHealth = Node::create();
	//frogHealth->setName("frogHealth");
	//frogHealthBar.healthBarInit();
	//frogHealth->addChild(frogHealthBar.getHealthSprite(), 1);
	//this->addChild(frogHealth, 0);
	tookDamage = false;
	EnableInput = true;
	CheckMatches = false;

	//Wave display Label
	waveDisplay = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
	waveDisplay->setPosition(Vec2(origin.x + visibleSize.width / 4,
		origin.y + visibleSize.height - waveDisplay->getContentSize().height));
	this->addChild(waveDisplay, 1);

	//Score display Label
	scoreDisplay = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
	scoreDisplay->setPosition(Vec2(origin.x + (visibleSize.width / 4) * 3,
		origin.y + visibleSize.height - scoreDisplay->getContentSize().height));
	this->addChild(scoreDisplay, 1);

	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();

	// set the background music and continuously play it.
	audio->playBackgroundMusic("Sound/BGM.wav", true);

	auto keyboard_listener = EventListenerKeyboard::create();
	keyboard_listener->onKeyPressed = CC_CALLBACK_2(Game::onKeyPressed, this);
	keyboard_listener->onKeyReleased = CC_CALLBACK_2(Game::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboard_listener, this);
	auto mouse_listener = EventListenerMouse::create();
	mouse_listener->onMouseDown = CC_CALLBACK_1(Game::onMousePressed, this);
	mouse_listener->onMouseUp = CC_CALLBACK_1(Game::onMouseReleased, this);
	mouse_listener->onMouseMove = CC_CALLBACK_1(Game::onMouseMove, this);
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
		if (EnableInput)
		{
			if (SelectedGrid == NULL)
			{
				SelectedGrid = m_GridMap.GetGridWithPos(Vec2(e->getCursorX(), e->getCursorY()));
			}
		}
		ClickFreeze(Vec2(e->getCursorX(), e->getCursorY()));
	}
}

void Game::onMouseReleased(Event* event)
{

    EventMouse* e = (EventMouse*)event;
    if (e->getMouseButton() == MOUSE_BUTTON_LEFT)
    {
        if (SelectedGrid)
        {
            SelectedGrid = NULL;

			CheckMatches = true;

            m_GridMap.CheckForMatches();     
            
			for (int i = 0; i < 6; ++i)
            {
                if (m_GridMap.GetLaneMatches()[i] > 0)
                {
                    Projectile* projectile = FetchProjectile();
					projectile->Init(i, m_GridMap.GetLaneMatches()[i]);
					addChild(projectile->GetParticle());

					char buffer[100];
					sprintf_s(buffer, "%d\n", m_GridMap.GetLaneMatches()[i]);
					OutputDebugStringA(buffer);
                }
            }
			
			m_GridMap.ResetLaneMatches();
        }
    }
}

void Game::onMouseMove(Event* event)
{
    EventMouse* e = (EventMouse*)event;
    Vec2 CursorPos = Vec2(e->getCursorX(), e->getCursorY());
    if (SelectedGrid)
    {
        Grid* temp = m_GridMap.GetGridWithPos(CursorPos);
        if (temp != NULL)
        {           
            m_GridMap.SwitchGrid(SelectedGrid, temp);
        }
        else
        {
            if (CursorPos.x < m_GridMap.GetMinPlayingField().x || CursorPos.x > m_GridMap.GetMaxPlayingField().x ||
                CursorPos.y < m_GridMap.GetMinPlayingField().y || CursorPos.y > m_GridMap.GetMaxPlayingField().y)
            {
                SelectedGrid = NULL;

				CheckMatches = true;

                m_GridMap.CheckForMatches();
				
				for (int i = 0; i < 6; ++i)
				{
					if (m_GridMap.GetLaneMatches()[i] > 0)
					{
						Projectile* projectile = FetchProjectile();
						projectile->Init(i, m_GridMap.GetLaneMatches()[i]);
						addChild(projectile->GetParticle());

						char buffer[100];
						sprintf_s(buffer, "%d\n", m_GridMap.GetLaneMatches()[i]);
						OutputDebugStringA(buffer);
					}
				}
				
				m_GridMap.ResetLaneMatches();
            }
        }
    }


}

Frog* Game::FetchFrog() {

	for (auto it : frogList)
	{

		Frog* temp = it;
		if (!temp->isActive)
		{
			temp->isActive = true;
			return temp;
		}
	}

	for (int i = 0; i < 10; ++i)
	{
		frogList.push_back(new Frog());
	}
	Frog* froggie = frogList.back();
	froggie->isActive = true;
	return froggie;
}

Projectile* Game::FetchProjectile() {
	for (auto it : projectileList)
	{
		Projectile* temp = it;
		if (!temp->GetIsActive())
		{
			temp->SetIsActive(true);
			return temp;
		}
	}

	for (int i = 0; i < 10; ++i)
	{
		projectileList.push_back(new Projectile());
	}
	Projectile* projectile = projectileList.back();
	projectile->SetIsActive(true);
	return projectile;
}

void Game::ClickFreeze(Vec2 pos)
{
	if (FreezePowerup->getBoundingBox().containsPoint(pos))
	{
		if (GameInstance::GetInstance()->GetFreeze() != 0)
		{
			FreezeAllFrog();
		}
	}
}

void Game::FreezeAllFrog()
{
	GameInstance::GetInstance()->DecrementFreeze();
	for (int i = 0; i < frogList.size(); i++) {
		if (frogList.at(i)->isActive)
		{
			frogList.at(i)->isFrozen = true;
		}
	}
}

void Game::update(float dt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (tookDamage == true){
		currHealth = dt;
		maxHealth += dt;
		timer.update(currHealth);
	}
	if (maxHealth >= 1.f){
		tookDamage = false;
		maxHealth = 0;
	}

	Text.str("");
	Text << "Wave " << wave.getWave();
	waveDisplay->setString(Text.str().c_str());

	Text.str("");
	Text << "Score: " << GameInstance::GetInstance()->GetScore();
	scoreDisplay->setString(Text.str().c_str());

    m_GridMap.update(dt);

	Frog::TYPE frogType = static_cast<Frog::TYPE>(cocos2d::RandomHelper::random_int(0, 3));
	Frog::LANE lane = static_cast<Frog::LANE>(cocos2d::RandomHelper::random_int(0, 5));

	if (CheckMatches)
	{
		EnableInput = false;

		CheckMatches = m_GridMap.CheckForMatches();
		
		//for (int i = 0; i < 6; ++i)
		//{
		//	if (m_GridMap.GetLaneMatches()[i] > 0)
		//	{
		//		Projectile* projectile = FetchProjectile();
		//		projectile->Init(i, m_GridMap.GetLaneMatches()[i]);
		//		addChild(projectile->GetParticle());
		//	}
		//}
		
		m_GridMap.ResetLaneMatches();
	}
	else if (!CheckMatches)
	{
		EnableInput = true;
	}

	//if (this->getChildrenCount()<= frogLimit){
	//	
	//	Frog* frog = FetchFrog();
	//	frog->init(frogType, lane);
	//	
	//	addChild(frog->getSprite(), 1);
	//}

	if (wave.spawnFrog(dt))
	{
		if (wave.currFrog < wave.getFrogLimit())
		{
			Frog* frog = FetchFrog();
			frog->init(frogType, lane);
			frog->healthBarInit();
			addChild(frog->getSprite(), 1);
			addChild(frog->getFSprite(), 2);
			addChild(frog->getHealthSprite(), 1);
			wave.currFrog++;
		}
	}

	int frogCount = 0;

	for (int i = 0; i < frogList.size(); i++) {
		if (frogList.at(i)->isActive)
		{
			frogCount++;
			float a = frogList.at(i)->getPos().y;
			float b = frogList.at(i)->getPos().x;
			if (!frogList.at(i)->isFrozen)
			{
				a -= frogList.at(i)->GetSpeed();
			}
			frogList.at(i)->SetPos(Vec2(b, a));
			frogList.at(i)->getFSprite()->setPosition(Vec2(b, a));
			frogList.at(i)->getHealthSprite()->setPosition(Vec2(frogList.at(i)->getPos().x, frogList.at(i)->getPos().y + 30));
			for (auto it : frogList) {
				if (it->isActive)
				{
					if (it->getPos().y < visibleSize.height*0.5) {
						it->isActive = false;
						this->removeChild(it->getSprite());
						this->removeChild(it->getHealthSprite());
						playerHealth -= 1;
						tookDamage = true;
					}
					it->update(dt);
					if (it->GetisDead()) {
						this->removeChild(it->getSprite());
						this->removeChild(it->getHealthSprite());
					}
				}
			}
		}
	}

	wave.update(dt, frogCount);
	if (playerHealth <= 0) {
		SceneManager::GetInstance()->SwitchScene(MainMenu::createScene());
	}

    for (auto it : projectileList)
    {
        if (it->GetIsActive())
        {
			it->IncrementPositionY(5.f);

			for (auto frogit : frogList)
			{
				if (frogit->isActive)
				{
					if (frogit->GetLane() == it->GetLane())
					{
						if (frogit->getSprite()->getBoundingBox().containsPoint(it->GetPosition()))
						{
							frogit->takeDamage(it->GetDamage());
							it->SetIsActive(false);
							this->removeChild(it->GetParticle());
						}

					}
				}
			}

            if (it->GetPosition().y > visibleSize.height)
            {
                it->SetIsActive(false);
                this->removeChild(it->GetParticle());
            }
        }
    }

	for (auto it : projectileList)
	{
		if (it->GetIsActive())
		{
			if (it->GetPosition().y > visibleSize.height)
			{
				it->SetIsActive(false);
				this->removeChild(it->GetParticle());
			}
			else
			{
				it->IncrementPositionY(10.f);
			}
		}
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