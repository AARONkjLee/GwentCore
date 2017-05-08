#include "CardCollection.h"
#include "SimpleAudioEngine.h"
#include "CardSprite.h"

USING_NS_CC; 

Scene* CardCollection::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = CardCollection::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool CardCollection::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(CardCollection::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	auto leftLabel1 = MenuItemImage::create(
		"left_label1.png",
		"left_label2.png"
	);
	leftLabel1->setPosition(Vec2(origin.x + leftLabel1->getContentSize().width/3,
		origin.y + visibleSize.height / 10 * 7));
	leftLabel1->setScale(1.2);
	this->addChild(leftLabel1, 1);

	auto leftLabel2 = MenuItemImage::create(
		"left_label1.png",
		"left_label2.png"
	);
	leftLabel2->setPosition(Vec2(origin.x + leftLabel2->getContentSize().width / 3,
		origin.y + visibleSize.height / 10 * 6));
	leftLabel2->setScale(1.2);
	this->addChild(leftLabel2, 1);

	auto leftLabel3 = MenuItemImage::create(
		"left_label1.png",
		"left_label2.png"
	);
	leftLabel3->setPosition(Vec2(origin.x + leftLabel3->getContentSize().width / 3,
		origin.y + visibleSize.height / 2 ));
	leftLabel3->setScale(1.2);
	this->addChild(leftLabel3, 1);

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label
	auto background = Sprite::create("BGP_1920x1080.jpg");
	background->setPosition(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2);
	this->addChild(background, 0);

	auto label = Label::createWithTTF("Card Collection", "fonts/Marker Felt.ttf", 30);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	label->setColor(ccc3(192, 192, 192));

	// add the label as a child to this layer
	this->addChild(label, 1);



	/*
	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("CardSpriteTest.png");

	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
	*/

	auto CardS1 = CardSprite::create(2);
	CardS1->setPosition(Vec2(visibleSize.width / 5 + origin.x, visibleSize.height / 4+ origin.y));
	CardS1->setScale(0.5);
	this->addChild(CardS1);



	return true;
}

void CardCollection::menuCloseCallback(Ref* pSender)
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