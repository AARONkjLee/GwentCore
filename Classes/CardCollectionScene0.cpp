#include "CardCollectionScene0.h"

USING_NS_CC;

//card collection is global for all cardCollectionScenes.


Scene* CardCollectionScene0::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = CardCollectionScene0::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool CardCollectionScene0::init()
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
		CC_CALLBACK_1(CardCollectionScene0::GoBackToMainSceneCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	auto background = Sprite::create("CardCollectionScene/_BGP_1920x1080.png");
	background->setPosition(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2);
	this->addChild(background, 0);

	auto title = Label::createWithTTF("CHOOSE A FACTION", "fonts/Marker Felt.ttf", 48);
	title->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - title->getContentSize().height* 1.5));
	title->setColor(ccc3(192, 192, 192));
	this->addChild(title, 0);

	auto northernRealmText = Label::createWithTTF("NORTHERN REALMS", "fonts/Marker Felt.ttf", 24);
	northernRealmText->setPosition(Vec2(origin.x + visibleSize.width / 5 * 1,
		origin.y + visibleSize.height / 7* 5));
	northernRealmText->setColor(ccc3(192, 192, 192));
	this->addChild(northernRealmText, 0);

	auto northernRealmBack = Sprite::create("PlayScene/PlayPreparationScene/NorthernRealmsBack.jpg");
	northernRealmBack->setPosition(origin.x + visibleSize.width / 5 * 1,
		origin.y + visibleSize.height / 2);
	northernRealmBack->setScale(0.25 * 1080 / visibleSize.height);
	this->addChild(northernRealmBack, 0);

	auto monstersText = Label::createWithTTF("MONSTERS", "fonts/Marker Felt.ttf", 24);
	monstersText->setPosition(Vec2(origin.x + visibleSize.width / 5 * 2,
		origin.y + visibleSize.height / 7 * 5));
	monstersText->setColor(ccc3(192, 192, 192));
	this->addChild(monstersText, 0);

	auto monstersBack = Sprite::create("PlayScene/PlayPreparationScene/MonstersBack.jpg");
	monstersBack->setPosition(origin.x + visibleSize.width / 5 * 2,
		origin.y + visibleSize.height / 2);
	monstersBack->setScale(0.25 * 1080 / visibleSize.height);
	this->addChild(monstersBack, 0);

	auto scoiataelText = Label::createWithTTF("SCOIA`TAEL", "fonts/Marker Felt.ttf", 24);
	scoiataelText->setPosition(Vec2(origin.x + visibleSize.width / 5 * 3,
		origin.y + visibleSize.height / 7 * 5));
	scoiataelText->setColor(ccc3(192, 192, 192));
	this->addChild(scoiataelText, 0);

	auto scoiataelBack = Sprite::create("PlayScene/PlayPreparationScene/ScoiataelBack.jpg");
	scoiataelBack->setPosition(origin.x + visibleSize.width / 5 * 3,
		origin.y + visibleSize.height / 2);
	scoiataelBack->setScale(0.25 * 1080 / visibleSize.height);
	this->addChild(scoiataelBack, 0);

	auto nilfgaardText = Label::createWithTTF("NILFGAARD", "fonts/Marker Felt.ttf", 24);
	nilfgaardText->setPosition(Vec2(origin.x + visibleSize.width / 5 * 4,
		origin.y + visibleSize.height / 7 * 5));
	nilfgaardText->setColor(ccc3(192, 192, 192));
	this->addChild(nilfgaardText, 0);

	auto nilfgaardBack = Sprite::create("PlayScene/PlayPreparationScene/NilfgaardianEmpireBack.jpg");
	nilfgaardBack->setPosition(origin.x + visibleSize.width / 5 * 4,
		origin.y + visibleSize.height / 2);
	nilfgaardBack->setScale(0.25 * 1080 / visibleSize.height);
	this->addChild(nilfgaardBack, 0);

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
	chooseSetMouseListener->onMouseUp = [=,  &clickable](Event* event) {
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


		if (mouseEventOnTarget_(mouseEvent, scoiataelBack)) {
			passDeckBeforePassScene(Scoiateal);
		}
		else if (mouseEventOnTarget_(mouseEvent, northernRealmBack)) {
			passDeckBeforePassScene(Northern);
		}
		else if (mouseEventOnTarget_(mouseEvent, nilfgaardBack)) {
			passDeckBeforePassScene(Nilfgaardian);
		}
		else if (mouseEventOnTarget_(mouseEvent, monstersBack)) {
			passDeckBeforePassScene(Monster);
		}
		else {
			clickable = true;
			return true;
		}
		
		Director::getInstance()->replaceScene(TransitionShrinkGrow::create(1.0, CardCollectionScene1::createScene()));
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(chooseSetMouseListener, scoiataelBack);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(chooseSetMouseListener->clone(), northernRealmBack);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(chooseSetMouseListener->clone(), nilfgaardBack);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(chooseSetMouseListener->clone(), monstersBack);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(chooseSetMouseListener->clone(), background);

	return true;
}


void CardCollectionScene0::passDeckBeforePassScene(CardSet set)
{
	if (!(set == NullCSet)) {
		collectionInstance::getInstance()->collection.initWithSet(set);
	}
}

std::vector<int> CardCollectionScene0 ::getUserDeck()
{
	std::vector<int> deck = {};
	return deck;
}

void CardCollectionScene0::GoBackToMainSceneCallback(Ref* pSender)
{
	auto Scene = MainScene::create();
	Director::getInstance()->replaceScene(TransitionFade::create(1, Scene));
}

