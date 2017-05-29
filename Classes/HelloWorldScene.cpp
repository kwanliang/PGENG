#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer, 0, 999);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
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

	auto nodeItems = Node::create();
	nodeItems->setName("nodeItems");

	Size sprite_MudSize = Sprite::create("ZigzagGrass_Mud_Round.png")->getContentSize();

	int numIter = std::ceil(playingSize.width / sprite_MudSize.width);
	float tempX = 0.f;
	float tempY = playingSize.height * 0.5f;

	for (int i = 0; i < numIter; ++i)
	{
		auto sprite_Mud = Sprite::create("ZigzagGrass_Mud_Round.png");

		sprite_Mud->setAnchorPoint(Vec2::ZERO);
		sprite_Mud->setPosition(tempX, tempY);
		tempX += sprite_MudSize.width;

		nodeItems->addChild(sprite_Mud, 0);
	}

	this->addChild(nodeItems, 1);

	auto nodeChar = Node::create();
	nodeChar->setName("nodeChar");

	hero.init("Blue_Front1.png", "Sprite_Char", 0, sprite_MudSize.height + playingSize.height * 0.5f);

	nodeChar->addChild(hero.getSprite(), 1);

	this->addChild(nodeChar, 1);

	auto nodeTime = Node::create();
	nodeTime->setName("nodeTime");

	timer.init(10.f);
	

	nodeTime->addChild(timer.getSprite(), 1);
	this->addChild(nodeTime, 0);

	isHoldingBlock = false;

	//TESTING FROGS
	Frog* green = new Frog;
	green->init(Frog::TYPE::GREEN, 1);
	green->SetPos(Vec2(100, 500));
	green->SetScale(Vec2(3, 3));
	frogList.push_back(green);
	this->addChild(green->getSprite(), 1);

	Frog* yellow = new Frog;
	yellow->init(Frog::TYPE::YELLOW, 1);
	yellow->SetPos(Vec2(200, 500));
	yellow->SetScale(Vec2(3, 3));
	frogList.push_back(yellow);
	this->addChild(yellow->getSprite(), 1);

	Frog* blue = new Frog;
	blue->init(Frog::TYPE::BLUE, 1);
	blue->SetPos(Vec2(300, 500));
	blue->SetScale(Vec2(3, 3));
	frogList.push_back(blue);
	this->addChild(blue->getSprite(), 1);

	Frog* red = new Frog;
	red->init(Frog::TYPE::RED, 1);
	red->SetPos(Vec2(400, 500));
	red->SetScale(Vec2(3, 3));
	frogList.push_back(red);
	this->addChild(red->getSprite(), 1);

	//TESTING BUTTERFLY
	Butterfly* greenB = new Butterfly;
	greenB->init(Butterfly::TYPE::GREEN, Vec2(1, 1));
	greenB->SetPos(Vec2(100, 300));
	greenB->SetScale(Vec2(0.5f, 0.5f));
	butterflyList.push_back(greenB);
	this->addChild(greenB->getSprite(), 1);

	Butterfly* yellowB = new Butterfly;
	yellowB->init(Butterfly::TYPE::YELLOW, Vec2(1, 1));
	yellowB->SetPos(Vec2(200, 300));
	yellowB->SetScale(Vec2(0.5f, 0.5f));
	butterflyList.push_back(yellowB);
	this->addChild(yellowB->getSprite(), 1);

	Butterfly* blueB = new Butterfly;
	blueB->init(Butterfly::TYPE::BLUE, Vec2(1, 1));
	blueB->SetPos(Vec2(300, 300));
	blueB->SetScale(Vec2(0.5f, 0.5f));
	butterflyList.push_back(blueB);
	this->addChild(blueB->getSprite(), 1);

	Butterfly* redB = new Butterfly;
	redB->init(Butterfly::TYPE::RED, Vec2(1, 1));
	redB->SetPos(Vec2(400, 300));
	redB->SetScale(Vec2(0.5f, 0.5f));
	butterflyList.push_back(redB);
	this->addChild(redB->getSprite(), 1);

	Butterfly* rainbow = new Butterfly;
	rainbow->init(Butterfly::TYPE::RAINBOW, Vec2(1, 1));
	rainbow->SetPos(Vec2(500, 300));
	rainbow->SetScale(Vec2(0.5f, 0.5f));
	butterflyList.push_back(rainbow);
	this->addChild(rainbow->getSprite(), 1);

	//auto moveEvent = MoveBy::create(5, Vec2(200.0f, 0.0f));
	////sprite_Char->runAction(moveEvent->clone());

	//auto delay = DelayTime::create(5.0f);
	//auto delaySequence = Sequence::create(delay, delay->clone(), nullptr);
	//auto sequence = Sequence::create(moveEvent, moveEvent->reverse(), delaySequence, nullptr);
	//sprite_Char->runAction(sequence);
	//sprite_Char->runAction(sequence->reverse());

	auto keyboard_listener = EventListenerKeyboard::create();
	keyboard_listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	keyboard_listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboard_listener, this);
	auto mouse_listener = EventListenerMouse::create();
	//mouse_listener->onMouseDown = CC_CALLBACK_1(HelloWorld::onMousePressed, this);
	mouse_listener->onMouseUp = CC_CALLBACK_1(HelloWorld::onMouseReleased, this);
	mouse_listener->onMouseMove = CC_CALLBACK_1(HelloWorld::onMouseMoved, this);
	//mouse_listener->onMouseDown = CC_CALLBACK_1(HelloWorld::onMouseHold, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouse_listener, this);

	//this->schedule(schedule_selector(HelloWorld::onKeyHold));
	//this->schedule(schedule_selector(HelloWorld::onMouseHold));

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	//// add a "close" icon to exit the progress. it's an autorelease object
	//auto closeItem = MenuItemImage::create(
	//                                       "CloseNormal.png",
	//                                       "CloseSelected.png",
	//                                       CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	//
	//closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
	//                            origin.y + closeItem->getContentSize().height/2));

	//// create menu, it's an autorelease object
	//auto menu = Menu::create(closeItem, NULL);
	//menu->setPosition(Vec2::ZERO);
	//this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	//auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
	//
	//// position the label on the center of the screen
	//label->setPosition(Vec2(origin.x + visibleSize.width/2,
	//                        origin.y + visibleSize.height - label->getContentSize().height));

	//// add the label as a child to this layer
	//this->addChild(label, 1);

	//// add "HelloWorld" splash screen"
	//auto sprite = Sprite::create("HelloWorld.png");

	//// position the sprite on the center of the screen
	//sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	//// add the sprite as a child to this layer
	//this->addChild(sprite, 0);

	mLoc.set(.5f, .5f);
	mLocInc.set(.005f, .01f);

	shaderCharEffect = new GLProgram();
	shaderCharEffect->initWithFilenames("Basic.vsh", "CharEffect.fsh");
	shaderCharEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	shaderCharEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	shaderCharEffect->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORDS);
	shaderCharEffect->link();
	shaderCharEffect->updateUniforms();

	proPostProcess = GLProgram::createWithFilenames("Basic.vsh", "GreyScale.fsh");
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD1, GLProgram::VERTEX_ATTRIB_TEX_COORD1);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD2, GLProgram::VERTEX_ATTRIB_TEX_COORD2);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD3, GLProgram::VERTEX_ATTRIB_TEX_COORD3);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_NORMAL, GLProgram::VERTEX_ATTRIB_NORMAL);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_BLEND_WEIGHT, GLProgram::VERTEX_ATTRIB_BLEND_WEIGHT);
	proPostProcess->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_BLEND_INDEX, GLProgram::VERTEX_ATTRIB_BLEND_INDEX);
	proPostProcess->link();
	proPostProcess->updateUniforms();

	rendtex = RenderTexture::create(visibleSize.width, visibleSize.height);
	rendtex->retain();

	rendtexSprite = Sprite::createWithTexture(rendtex->getSprite()->getTexture());
	rendtexSprite->setTextureRect(Rect(0, 0, rendtexSprite->getTexture()->getContentSize().width, rendtexSprite->getTexture()->getContentSize().height));
	rendtexSprite->setAnchorPoint(Point::ZERO);
	rendtexSprite->setPosition(Point::ZERO);
	rendtexSprite->setFlippedY(true);
	rendtexSprite->setGLProgram(proPostProcess);
	this->addChild(rendtexSprite, 2);

	this->scheduleUpdate();

	return true;
}

//void HelloWorld::onKeyHold(float interval)
//{
//	if (std::find(heldKeys.begin(), heldKeys.end(), EventKeyboard::KeyCode::KEY_RIGHT_ARROW) 
//		!= heldKeys.end())
//	{
//		hero.MoveChar(1.f, 0.f);
//	}
//	if (std::find(heldKeys.begin(), heldKeys.end(), EventKeyboard::KeyCode::KEY_LEFT_ARROW)
//		!= heldKeys.end())
//	{
//		hero.MoveChar(-1.f, 0.f);
//	}
//	if (std::find(heldKeys.begin(), heldKeys.end(), EventKeyboard::KeyCode::KEY_UP_ARROW)
//		!= heldKeys.end())
//	{
//		hero.MoveChar(0.f, 1.f);
//	}
//	if (std::find(heldKeys.begin(), heldKeys.end(), EventKeyboard::KeyCode::KEY_DOWN_ARROW)
//		!= heldKeys.end())
//	{
//		hero.MoveChar(0.f, -1.f);
//	}
//}

void HelloWorld::onMouseHold(float interval)
{
	if (std::find(heldMouse.begin(), heldMouse.end(), MOUSE_BUTTON_LEFT)
		!= heldMouse.end())
	{
		/*auto curSprite = this->getChildByName("nodeChar")->getChildByName("sprite_Char");
		auto moveEvent = MoveBy::create(0.0f, Vec2(10.0f, 0.f));*/
		//curSprite->runAction(moveEvent);
	}
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	//if (std::find(heldKeys.begin(), heldKeys.end(), keyCode) == heldKeys.end())
	//{
	//	heldKeys.push_back(keyCode);
	//}

	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		hero.MoveChar(1.f, 0.f);
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		hero.MoveChar(-1.f, 0.f);
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		hero.MoveChar(0.f, 1.f);
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		hero.MoveChar(0.f, -1.f);
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		CCDirector::getInstance()->replaceScene(TransitionFade::create(1.5, HelloWorld::createScene(), Color3B(0, 255, 255)));
	}
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	hero.Stop();
	//heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(), keyCode), heldKeys.end());
}

void HelloWorld::onMousePressed(Event* event)
{
	//EventMouse* e = (EventMouse*)event;
	//if (std::find(heldButtons.begin(), heldButtons.end(), e->getMouseButton()) == heldButtons.end())
	//{
	//	heldButtons.push_back(e->getMouseButton());
	//}
	EventMouse* e = (EventMouse*)event;
	if (std::find(heldMouse.begin(), heldMouse.end(), MOUSE_BUTTON_LEFT) == heldMouse.end()){
		if (e->getMouseButton() == MOUSE_BUTTON_LEFT)
		{
			hero.MoveCharByCoord(e->getCursorX(), e->getCursorY());
			//positionToMove = e->getLocation();
			//positionToMove = positionToMove.getNormalized();
			//auto curSprite = this->getChildByName("nodeChar")->getChildByName("sprite_Char");
			//auto moveEvent = MoveBy::create(0.0f, Vec2(positionToMove.x, positionToMove.y));
			//curSprite->runAction(moveEvent);
			heldMouse.push_back(MOUSE_BUTTON_LEFT);
		}
	}
}

//void HelloWorld::onMouseHold(Event* event){
//	if (std::find(heldMouse.begin(), heldMouse.end(), MOUSE_BUTTON_LEFT) != heldMouse.end()){
//		//pressed
//	}
//}

void HelloWorld::onMouseReleased(Event* event)
{
	heldMouse.erase(std::remove(heldMouse.begin(), heldMouse.end(), MOUSE_BUTTON_LEFT), heldMouse.end());
	isHoldingBlock = false;
	timer.reset(10.f);

	//EventMouse* e = (EventMouse*)event;
	//if (e->getMouseButton() == MOUSE_BUTTON_LEFT)
	//{
	//	positionToMove.x = e->getCursorX();
	//	positionToMove.y = e->getCursorY();
	//	positionToMove = positionToMove.getNormalized();
	//	auto curSprite = this->getChildByName("nodeChar")->getChildByName("sprite_Char");
	//	auto moveEvent = MoveBy::create(0.0f, Vec2(positionToMove.x, positionToMove.y));
	//	curSprite->runAction(moveEvent);
	//}
	//heldButtons.erase(std::remove(heldButtons.begin(), heldButtons.end(), e->getMouseButton()), heldButtons.end());
}
using namespace std;
void HelloWorld::onMouseMoved(Event* event){
	EventMouse* e = (EventMouse*)event;
	
	if (e->getMouseButton() == MOUSE_BUTTON_LEFT){
		auto mouse_listener = EventListenerMouse::create();
		hero.MoveCharByCoord(e->getCursorX(), e->getCursorY());
		_eventDispatcher->addEventListenerWithFixedPriority(mouse_listener, 1);
		isHoldingBlock = true;
	}

	//std::stringstream message;
	//message << e->getCursorX();
	//label = Label::createWithSystemFont(message.str(), "Arial", 100);
	//label->setPosition(200,50);
	//this->addChild(label);

	this->scheduleUpdate();
}
void HelloWorld::update(float delta)
{
	//auto cam = Camera::getDefaultCamera();
	//cam->setPosition(hero.getSprite()->getPosition());
	
	GLProgramState* state = GLProgramState::getOrCreateWithGLProgram(shaderCharEffect);
	hero.getSprite()->setGLProgram(shaderCharEffect);
	hero.getSprite()->setGLProgramState(state);


	state->setUniformVec2("loc", mLoc);

	rendtex->beginWithClear(.0f, .0f, .0f, .0f);
	this->visit();
	rendtex->end();
	rendtexSprite->setTexture(rendtex->getSprite()->getTexture());
	rendtexSprite->setGLProgram(proPostProcess);

	hero.update(delta);
	if (isHoldingBlock == true){
		timer.update(delta);
	}
	
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	frogList.clear();
	butterflyList.clear();
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}
