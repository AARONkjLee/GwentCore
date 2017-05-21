#include "CardCollectionScene2.h"
#include "SimpleAudioEngine.h"
#include "CardSprite.h"

USING_NS_CC; 


Scene* CardCollectionScene2::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = CardCollectionScene2::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool CardCollectionScene2::init()
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
		CC_CALLBACK_1(CardCollectionScene2::GoBackToMainSceneCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	auto leftLabel1 = MenuItemImage::create(
		"CardCollectionScene/label.png",
		"CardCollectionScene/label.png"
	);
	leftLabel1->setPosition(Vec2(origin.x + visibleSize.width / 10,
		origin.y + visibleSize.height / 10 * 8));
	leftLabel1->setScale(0.7);
	this->addChild(leftLabel1, 1);

	auto leftLabel2 = MenuItemImage::create(
		"CardCollectionScene/label.png",
		"CardCollectionScene/label.png"
	);
	leftLabel2->setPosition(Vec2(origin.x + visibleSize.width / 10,
		origin.y + visibleSize.height / 10 * 7));
	leftLabel2->setScale(0.7);
	this->addChild(leftLabel2, 1);


	auto buttonb1 = MenuItemImage::create(
		"CardCollectionScene/buttonb.png",
		"CardCollectionScene/buttonb.png"
	);
	buttonb1->setPosition(Vec2(origin.x + visibleSize.width / 7 * 3,
		origin.y + visibleSize.height / 11 * 2.7 ));
	buttonb1->setScale(0.7);
	this->addChild(buttonb1, 1);

	auto buttonb2 = MenuItemImage::create(
		"CardCollectionScene/buttonb.png",
		"CardCollectionScene/buttonb.png"
	);
	buttonb2->setPosition(Vec2(origin.x + visibleSize.width / 7 * 4,
		origin.y + visibleSize.height / 11 * 2.7));
	buttonb2->setScale(0.7);
	this->addChild(buttonb2, 1);

	auto buttonb3 = MenuItemImage::create(
		"CardCollectionScene/buttonb.png",
		"CardCollectionScene/buttonb.png"
	);
	buttonb2->setPosition(Vec2(origin.x + visibleSize.width / 7 * 5,
		origin.y + visibleSize.height / 11 * 2.7));
	buttonb2->setScale(0.7);
	this->addChild(buttonb3, 1);

	auto rightb = MenuItemImage::create(
		"CardCollectionScene/right.png",
		"CardCollectionScene/right.png"
	);
	rightb->setPosition(Vec2(origin.x + visibleSize.width * 0.644,
		origin.y + visibleSize.height / 11 * 2.7));
	this->addChild(rightb, 1);

	auto leftb = MenuItemImage::create(
		"CardCollectionScene/left.png",
		"CardCollectionScene/left.png"
	);
	leftb->setPosition(Vec2(origin.x + visibleSize.width/ 2,
		origin.y + visibleSize.height / 11 * 2.7));
	this->addChild(leftb, 1);


	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label
	auto background = Sprite::create("CardCollectionScene/_BGP_1920x1080.png");
	background->setPosition(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2);
	this->addChild(background, 0);

	auto back1 = Sprite::create("CardCollectionScene/background_for_card_exhibition.png");
	back1->setPosition(origin.x + visibleSize.width / 7 * 4,
		origin.y + visibleSize.height / 2);
	back1->setScale(1.5);
	this->addChild(back1, 0);

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
	CardCollection mCardset = collectionInstance::getInstance()->collection;
	CardSet hhhset = mCardset.getSet();
	int mLeader_id = mCardset.getLeader();
	auto ns="";

	switch (hhhset)
	{
	case NullCSet:
		break;
	case Northern:
		ns="PlayScene/PlayPreparationScene/NorthernRealmsBack.jpg";
		break;
	case Nilfgaardian:
		ns="PlayScene/PlayPreparationScene/NilfgaardianEmpireBack.jpg";
		break;
	case Monster:
		ns="PlayScene/PlayPreparationScene/MonstersBack.jpg";
		break;
	case Scoiateal:
		ns="PlayScene/PlayPreparationScene/ScoiataelBack.jpg";
		break;
	case Neutral:
		ns = "PlayScene/PlayPreparationScene/NorthernRealmsBack.jpg";
		break;
	default:
		break;
	}

	auto mset = Sprite::create(ns);
	mset->setPosition(origin.x + 90,
		origin.y + visibleSize.height / 4);
	mset->setScale(0.2);
	this->addChild(mset, 1);

	auto leader_label = LeaderCardSprite::create(mLeader_id);
	leader_label->setPosition(origin.x + 200 ,
		origin.y + visibleSize.height / 4);
	leader_label->setScale(0.2);
	this->addChild(leader_label, 1);



	switch (hhhset)
	{
	case NullCSet:
		break;
	case Northern:

		break;
	case Nilfgaardian:
		// mCardset.getDeck().size()
		for (int i = 0; i < 35 ; i++) {
			int pos = mCardset.getDeck().at(i);
			auto CardS1 = CardSprite::create(pos);
			if (CardS1) {
				int y = i / 7;
				int x = i - y * 7;
				
				CardS1->setPosition(Vec2(340+ visibleSize.width / 12 * (0.6 + x) + origin.x, origin.y+80+ y*130));
				CardS1->setScale(0.18);
				this->addChild(CardS1);
			}
		}
		break;
	case Monster:
		for (int i = 1; i <= 40; i++) {
			auto CardS1 = CardSprite::create(i);
			CardS1->setPosition(Vec2(origin.x + 20, origin.y + 20));
			CardS1->setScale(0.05);
			this->addChild(CardS1);
		}
		break;
	case Scoiateal:
		break;
	case Neutral:
		break;
	default:
		break;
	}

	return true;
}

void CardCollectionScene2::menuCloseCallback(Ref* pSender)
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


void CardCollectionScene2::GoBackToMainSceneCallback(Ref* pSender)
{
	auto Scene = MainScene::create();
	Director::getInstance()->replaceScene(TransitionFade::create(1, Scene));
}
