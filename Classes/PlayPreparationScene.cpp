#include "CardSprite.h"
#include "SimpleAudioEngine.h"
#include "PlayPreparationScene.h"

USING_NS_CC;

Scene* PlayPreparationScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PlayPreparationScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PlayPreparationScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
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
                                           CC_CALLBACK_1(PlayPreparationScene::GoBackToMainSceneCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Play Preparation Scene Test", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

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

	auto CardS1 = CardSprite::create(11);
	CardS1->setPosition(Vec2(visibleSize.width / 4 + origin.x, visibleSize.height / 2 + origin.y));
	//CardS1->setScale(0.5);

	auto CardS2 = CardSprite::create(1);
	CardS2->setPosition(Vec2(visibleSize.width * 3 / 4 + origin.x, visibleSize.height / 2 + origin.y));
	//CardS2->setScale(0.5);

	this->addChild(CardS1);
	this->addChild(CardS2);



    return true;
}


void PlayPreparationScene::GoBackToMainSceneCallback(Ref* pSender)
{
	auto Scene = MainScene::create();
	Director::getInstance()->replaceScene(TransitionFade::create(1, Scene));
}

std::vector<int> getUserDeck()
{
	// To-do change to read users deck
	int deckArr[] = {3,
		41,
		44,44,44,
		45,
		46,
		49,
		50,
		
		52,
		53,
		54,
		55,
		56,56,
		57,57,
		58,58,

		61,
		62,
		65,
		66,
		68,
		73,
		74,
		76,
		84,
		86,
		87,
		89,
		91,
		93,
		94
	};
	std::vector<int> deck(deckArr, deckArr+29);
	return ;
}
