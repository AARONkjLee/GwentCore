#include "CardCollectionScene1.h"

USING_NS_CC;

//card collection is global for all cardCollectionScenes.

Scene* CardCollectionScene1::createScene(CardCollection collection_)
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = CardCollectionScene1::create();

	layer->collection = collection_;

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

	CardSet set;
	switch (set)
	{
	case NullCSet:
		break;
	case Northern:
		for (int i = 5; i < 10; i++) {
			auto lea = LeaderCardSprite::creat(i);
			lea ->setPosition(origin.x + visibleSize.width / 5 * 3,
				origin.y + visibleSize.height / 2);
			this->addChild(lea, 1);
		}
		break;
	case Nilfgaardian:
		break;
	case Monster:
		break;
	case Scoiateal:
		break;
	case Neutral:
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
	chooseSetMouseListener->onMouseUp = [&](Event* event) {
		if (!clickable) {
			return true;
		}
		clickable = false;
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		if (target == nullptr)
		{
			return true;
		}

		EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);

		//Vec2 locationInNode = target->convertToNodeSpace(mouseEvent->getLocation());
		//Size s = target->getContentSize();
		//Rect rect = Rect(0, 0, s.width, s.height);


		if (mouseEventOnTarget__(mouseEvent, scoiataelBack)) {
			passLeaderBeforePassScene(Scoiateal);
		}
		else if (mouseEventOnTarget__(mouseEvent, northernRealmBack)) {
			passLeaderBeforePassScene(Northern);
		}
		else if (mouseEventOnTarget__(mouseEvent, nilfgaardBack)) {
			passLeaderBeforePassScene(Nilfgaardian);
		}
		else if (mouseEventOnTarget__(mouseEvent, monstersBack)) {
			passLeaderBeforePassScene(Monster);
		}
		else {
			clickable = true;
			return true;
		}

		// To 若晴 这句话你可以写为进入你自己的下一个场景 转换之前你要想办法把选好的Set传入下一个场景
		// 你可以试试复写下一个scene的create函数，令其带一个参数，根据传入的参数创建选好阵营的scene
		Director::getInstance()->replaceScene(TransitionShrinkGrow::create(1.0, CardCollectionScene2::createScene()));
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(chooseSetMouseListener, scoiataelBack);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(chooseSetMouseListener->clone(), northernRealmBack);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(chooseSetMouseListener->clone(), nilfgaardBack);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(chooseSetMouseListener->clone(), monstersBack);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(chooseSetMouseListener->clone(), background);

	return true;
}


void CardCollectionScene1::GoBackToMainSceneCallback(Ref* pSender)
{
	if (clickable) {
		clickable = false;
		auto Scene = MainScene::create();
		Director::getInstance()->replaceScene(TransitionFade::create(1, Scene));
	}
}

void CardCollectionScene1::passLeaderBeforePassScene(LeaderCard leader)
{
	collection.setLeader(leader);
}

std::vector<int> CardCollectionScene1::getUserDeck()
{
	std::vector<int> deck = {};
	return deck;
}


