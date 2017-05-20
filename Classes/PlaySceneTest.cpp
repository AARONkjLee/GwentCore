#include "CardSprite.h"
#include "SimpleAudioEngine.h"
#include "PlaySceneTest.h"

//  关于Listener和Event的教程
//  http://www.gamefromscratch.com/post/2014/10/03/Cocos2d-x-Tutorial-Series-Handling-Touch-and-Mouse-Input.aspx
//  http://www.jellythink.com/archives/769

//  关于Lambda函数的教程
//  http://www.jellythink.com/archives/668

USING_NS_CC;

Scene* PlaySceneTest::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PlaySceneTest::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PlaySceneTest::init()
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
                                           CC_CALLBACK_1(PlaySceneTest::GoBackToMainSceneCallback, this));
    
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
    
    auto label = Label::createWithTTF("Play Scene Test", "fonts/Marker Felt.ttf", 24);
    
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

	auto mouselistener = EventListenerMouse::create();
	// 以下三个是lambda函数 见本cpp文件开头的教程
	mouselistener->onMouseDown = [] (cocos2d::Event* event){};
	mouselistener->onMouseMove = [](cocos2d::Event* event) {};
	mouselistener->onMouseUp = [=](cocos2d::Event* event) {
		// 获取事件所绑定的 target 
		auto target = static_cast<CardSprite*>(event->getCurrentTarget());
		if (target == nullptr)
		{
			return true;
		}

		EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
		//mouseEvent->getMouseButton();
		//std::stringstream message;
		//message << "Mouse event: Button: " << mouseEvent->getMouseButton() << "pressed at point (" <<
		//	mouseEvent->getLocation().x << "," << mouseEvent->getLocation().y << ")";
		//MessageBox(message.str().c_str(), "Mouse Event Details");


		// 获取当前点击点所在相对按钮的位置坐标
		// getLocation得到的是openGL坐标系，也就是世界坐标系
		Vec2 locationInNode = target->convertToNodeSpace(mouseEvent->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		// 点击范围判断检测
		if (rect.containsPoint(locationInNode))
		{
			//log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
			if (mouseEvent->getMouseButton() == 0) {
				target->setCurrentStrength(target->getInitStrength() + 2);
			} else if (mouseEvent->getMouseButton() == 1) {
				target->setCurrentStrength(target->getInitStrength() - 2);
			} else {
				target->setCurrentStrength(target->getInitStrength());

			}
			return true;
		}
		return false;

	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouselistener, CardS1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouselistener->clone(), CardS2);

    return true;
}


void PlaySceneTest::GoBackToMainSceneCallback(Ref* pSender)
{
	auto Scene = MainScene::create();
	Director::getInstance()->replaceScene(TransitionFade::create(1, Scene));
}
