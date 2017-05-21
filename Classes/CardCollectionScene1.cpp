#include "CardCollectionScene1.h"
#include <vector>

USING_NS_CC;

//card collection is global for all cardCollectionScenes.

Scene* CardCollectionScene1::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = CardCollectionScene1::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool CardCollectionScene1::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	bool clickable = true;
	
	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(CardCollectionScene1::GoBackToMainSceneCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	auto background = Sprite::create("CardCollectionScene/_BGP_1920x1080.png");
	background->setPosition(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2);
	this->addChild(background, 0);

	auto title = Label::createWithTTF("CHOOSE A LEADER", "fonts/Marker Felt.ttf", 48);
	title->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - title->getContentSize().height* 1.5));
	title->setColor(ccc3(192, 192, 192));
	this->addChild(title, 0);

	auto sub_title = Label::createWithTTF("Select the leader that will be used for the newly created deck.", "fonts/Marker Felt.ttf", 44);
	sub_title->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - title->getContentSize().height * 3));
	sub_title->setColor(ccc3(192, 192, 192));
	this->addChild(sub_title, 0);


	std::vector<LeaderCardSprite*> Leaders;
	std::vector<int> _id;

	switch (collectionInstance::getInstance()->collection.getSet())
	{
	case NullCSet:
		break;
	case Northern:
		for (int i = 0; i < 5; i++) {

			Leaders.push_back(LeaderCardSprite::create(i+5));
			_id.push_back(i + 5);
			Leaders[i]->setPosition(origin.x + 200 + (visibleSize.width - 200) / 5 * i,
				origin.y + visibleSize.height / 2);
			Leaders[i]->setScale(0.4);
			this->addChild(Leaders[i], 1);
		}
		break;
	case Nilfgaardian:
		for (int i = 0; i < 5; i++) {
			Leaders.push_back(LeaderCardSprite::create(i));
			_id.push_back(i);

			Leaders[i]->setPosition(origin.x+200 + (visibleSize.width-200) / 5 * i,
				origin.y + visibleSize.height / 2);
			Leaders[i]->setScale(0.4);
			this->addChild(Leaders[i], 1);
		}
		break;
	case Monster:
		for (int i = 0; i < 5; i++) {
			Leaders.push_back(LeaderCardSprite::create(i + 15));
			_id.push_back(i + 15);
			Leaders[i]->setPosition(origin.x + 200 + (visibleSize.width - 200) / 5 * i,
				origin.y + visibleSize.height / 2);
			Leaders[i]->setScale(0.4);
			this->addChild(Leaders[i], 1);
		}
		break;
	case Scoiateal:
		for (int i = 0; i < 5; i++) {
			Leaders.push_back(LeaderCardSprite::create(i + 10));
			_id.push_back(i + 10);
			Leaders[i]->setPosition(origin.x + 200 + (visibleSize.width - 200) / 5 * i,
				origin.y + visibleSize.height / 2);
			Leaders[i]->setScale(0.4);
			this->addChild(Leaders[i], 1);
		}
		break;

	default:
		break;
	}

	// Mouse listeners

	auto chooseSetMouseListener = EventListenerMouse::create();

	// Naming rule for scale action:
	// scale%Obj%way%Percent; 
	//		%Obj = object to run the action.
	//		%Way = By or To
	//		%Percent = scale number in 100%
	auto scaleBackBy110 = ScaleBy::create(0.1, 1.1);
	auto scaleBackBy100 = ScaleBy::create(0, 1, 1.0 / 1 / 1);

	chooseSetMouseListener->onMouseDown = [](Event* event) {};
	chooseSetMouseListener->onMouseMove = [=](Event* event) {};/*
															   auto target = static_cast<Sprite*>(event->getCurrentTarget());
															   if (target == nullptr)
															   {
															   return true;
															   }
															   if (target->getName() == "background") {
															   ScoiataelBack->runAction(scaleBackBy100);
															   NorthernRealmsBack->runAction(scaleBackBy100);
															   NilfgaardianEmpireBack->runAction(scaleBackBy100);
															   MonstersBack->runAction(scaleBackBy100);
															   }
															   else {
															   target->runAction(scaleBackBy110);
															   }
															   };*/
	chooseSetMouseListener->onMouseUp = [=, &clickable](Event* event) {

	    //if (!clickable) {
		//    return true;
	    //}
	    //clickable = false;
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		if (target == nullptr)
		{
			return true;
		}

		EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

		//Vec2 locationInNode = target->convertToNodeSpace(mouseEvent->getLocation());
		//Size s = target->getContentSize();
		//Rect rect = Rect(0, 0, s.width, s.height);

		   
		if (mouseEventOnTarget__(mouseEvent, Leaders[0])) {
			passLeaderBeforePassScene(_id[0]);
		}
		else if (mouseEventOnTarget__(mouseEvent, Leaders[1])) {
			passLeaderBeforePassScene(_id[1]);
		}
		else if (mouseEventOnTarget__(mouseEvent, Leaders[2])) {
			passLeaderBeforePassScene(_id[2]);
		}
		else if (mouseEventOnTarget__(mouseEvent, Leaders[3])) {
			passLeaderBeforePassScene(_id[3]);
		}
		else if (mouseEventOnTarget__(mouseEvent, Leaders[4])) {
			passLeaderBeforePassScene(_id[4]);
		}
		else {
			clickable = true;
			return true;
		}


		Director::getInstance()->replaceScene(TransitionShrinkGrow::create(1.0, CardCollectionScene2::createScene()));
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(chooseSetMouseListener, Leaders[0]);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(chooseSetMouseListener->clone(), Leaders[1]);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(chooseSetMouseListener->clone(), Leaders[2]);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(chooseSetMouseListener->clone(), Leaders[3]);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(chooseSetMouseListener->clone(), Leaders[4]);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(chooseSetMouseListener->clone(), background);

	return true;
}



void CardCollectionScene1::passLeaderBeforePassScene(int leaderId)
{
	collectionInstance::getInstance()->collection.setLeadId(leaderId);
}

std::vector<int> CardCollectionScene1::getUserDeck()
{
	std::vector<int> deck = {};
	return deck;
}

void CardCollectionScene1::GoBackToMainSceneCallback(Ref* pSender)
{
	auto Scene = MainScene::create();
	Director::getInstance()->replaceScene(TransitionFade::create(1, Scene));
}
