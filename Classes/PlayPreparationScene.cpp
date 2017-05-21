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

	clickable = true;

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

	//Texts:

	auto background = Sprite::create(PLAY_PREPARATION_BG);
	background->setPosition(visibleSize / 2);
	this->addChild(background);

	auto title = Sprite::create(PLAY_PREPARATION_TITLE_PIC);
	title->setPosition(Vec2(WIN_CORDINATE_2_GL(6.75, 1.96, 20.37, 2.39)));
	this->addChild(title);

	auto scoiataelText = Sprite::create(PLAY_PREPARATION_ScoiataelText_PIC);
	scoiataelText->setPosition(Vec2(WIN_CORDINATE_2_GL(4.51, 12.75, 5.99, 3.85)));
	this->addChild(scoiataelText);

	auto northernKingdomsText = Sprite::create(PLAY_PREPARATION_NorthernKingdomsText_PIC);
	northernKingdomsText->setPosition(Vec2(WIN_CORDINATE_2_GL(10.8, 12.75, 5.99, 5.04)));
	this->addChild(northernKingdomsText);

	auto nilfgaardianEmpireText = Sprite::create(PLAY_PREPARATION_NilfgaardianEmpireText_PIC);
	nilfgaardianEmpireText->setPosition(Vec2(WIN_CORDINATE_2_GL(17.09, 12.75, 5.99, 4.36)));
	this->addChild(nilfgaardianEmpireText);

	auto monsterText = Sprite::create(PLAY_PREPARATION_MonsterText_PIC);
	monsterText->setPosition(Vec2(WIN_CORDINATE_2_GL(23.37, 12.75, 5.99, 4.53)));
	this->addChild(monsterText);

	// SetSprites:

	auto ScoiataelBack = Sprite::create(PLAY_PREPARATION_ScoiataelBack_PIC);
	ScoiataelBack->setScale(0.25*1080/visibleSize.height);
	ScoiataelBack->setPosition(Vec2(WIN_CORDINATE_2_GL(5.06, 4.84, 4.91, 7.37)));
	this->addChild(ScoiataelBack);

	auto NorthernRealmsBack = Sprite::create(PLAY_PREPARATION_NorthernRealmsBack_PIC);
	NorthernRealmsBack->setScale(0.25 * 1080 / visibleSize.height);
	NorthernRealmsBack->setPosition(Vec2(WIN_CORDINATE_2_GL(11.34, 4.84, 4.91, 7.37)));
	this->addChild(NorthernRealmsBack);

	auto NilfgaardianEmpireBack = Sprite::create(PLAY_PREPARATION_NilfgaardianEmpireBack_PIC);
	NilfgaardianEmpireBack->setScale(0.25 * 1080 / visibleSize.height);
	NilfgaardianEmpireBack->setPosition(Vec2(WIN_CORDINATE_2_GL(17.62,  4.84, 4.91, 7.37)));
	this->addChild(NilfgaardianEmpireBack);

	auto MonstersBack = Sprite::create(PLAY_PREPARATION_MonstersBack_PIC);
	MonstersBack->setScale(0.25 * 1080 / visibleSize.height);
	MonstersBack->setPosition(Vec2(WIN_CORDINATE_2_GL(23.9, 4.84, 4.91, 7.37)));
	this->addChild(MonstersBack);

	// Mouse listeners

	auto chooseSetMouseListener = EventListenerMouse::create();
	auto scaleSetSpriteMouseListener = EventListenerMouse::create();


	// Naming rule for scale action:
	// scale%Obj%way%Percent; 
	//		%Obj = object to run the action.
	//		%Way = By or To
	//		%Percent = scale number in 100%
	auto scaleBackTo110Relatively = ScaleTo::create(0.1, 1.1*0.25);
	auto scaleBackTo100Relatively = ScaleTo::create(0.1, 1.0*0.25);


//	chooseSetMouseListener->onMouseDown = [](Event* event) {};
	CardSet activatedSetSprite = NullCSet;
	scaleSetSpriteMouseListener->onMouseMove = [=, &activatedSetSprite](Event* event) {}; /*
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		if (target == nullptr)
		{
			return true;
		}

		EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
		CardSet currentActivatedSetSprite;

		if (mouseEventOnTarget(mouseEvent, ScoiataelBack)) {
			currentActivatedSetSprite = Scoiateal;
		}
		else if (mouseEventOnTarget(mouseEvent, NorthernRealmsBack)) {
			currentActivatedSetSprite = Northern;
		}
		else if (mouseEventOnTarget(mouseEvent, NilfgaardianEmpireBack)) {
			currentActivatedSetSprite = Nilfgaardian;
		}
		else if (mouseEventOnTarget(mouseEvent, MonstersBack)) {
			currentActivatedSetSprite = Monster;
		}
		else if (mouseEventOnTarget(mouseEvent, background)) {
			currentActivatedSetSprite = NullCSet;
		}

		if (currentActivatedSetSprite != activatedSetSprite) {
			switch (currentActivatedSetSprite)
			{
			case NullCSet:
				ScoiataelBack->runAction(scaleBackTo100Relatively);
				NorthernRealmsBack->runAction(scaleBackTo100Relatively);
				NilfgaardianEmpireBack->runAction(scaleBackTo100Relatively);
				MonstersBack->runAction(scaleBackTo100Relatively);
				break;
			case Northern:
				ScoiataelBack->runAction(scaleBackTo100Relatively);
				NorthernRealmsBack->runAction(scaleBackTo110Relatively);
				NilfgaardianEmpireBack->runAction(scaleBackTo100Relatively);
				MonstersBack->runAction(scaleBackTo100Relatively);
				break;
			case Nilfgaardian:
				ScoiataelBack->runAction(scaleBackTo100Relatively);
				NorthernRealmsBack->runAction(scaleBackTo100Relatively);
				NilfgaardianEmpireBack->runAction(scaleBackTo110Relatively);
				MonstersBack->runAction(scaleBackTo100Relatively);
				break;
			case Monster:
				ScoiataelBack->runAction(scaleBackTo100Relatively);
				NorthernRealmsBack->runAction(scaleBackTo100Relatively);
				NilfgaardianEmpireBack->runAction(scaleBackTo100Relatively);
				MonstersBack->runAction(scaleBackTo110Relatively);
				break;
			case Scoiateal:
				ScoiataelBack->runAction(scaleBackTo110Relatively);
				NorthernRealmsBack->runAction(scaleBackTo100Relatively);
				NilfgaardianEmpireBack->runAction(scaleBackTo100Relatively);
				MonstersBack->runAction(scaleBackTo100Relatively);
				break;
			case Neutral:
				break;
			default:
				break;
			}
			activatedSetSprite = currentActivatedSetSprite;
		}

		return true;
	};*/
	chooseSetMouseListener->onMouseUp = [=](Event* event) {
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

		// To 若晴 这些 passDeckBeforePassScene 方法你应该是不用调用的
		if (mouseEventOnTarget(mouseEvent, ScoiataelBack)) {
			passDeckBeforePassScene(Scoiateal);
		}
		else if (mouseEventOnTarget(mouseEvent, NorthernRealmsBack)) {
			passDeckBeforePassScene(Northern);
		}
		else if (mouseEventOnTarget(mouseEvent, NilfgaardianEmpireBack)) {
			passDeckBeforePassScene(Nilfgaardian);
		}
		else if (mouseEventOnTarget(mouseEvent, MonstersBack)) {
			passDeckBeforePassScene(Monster);
		}
		else {
			clickable = true;
			return true;
		}

		// To 若晴 这句话你可以写为进入你自己的下一个场景 转换之前你要想办法把选好的Set传入下一个场景
		// 你可以试试复写下一个scene的create函数，令其带一个参数，根据传入的参数创建选好阵营的scene
		Director::getInstance()->replaceScene(TransitionFadeTR::create(1, SinglePlayScene::createScene()));
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(chooseSetMouseListener, ScoiataelBack);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(chooseSetMouseListener->clone(), NorthernRealmsBack);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(chooseSetMouseListener->clone(), NilfgaardianEmpireBack);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(chooseSetMouseListener->clone(), MonstersBack);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(chooseSetMouseListener->clone(), background);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(scaleSetSpriteMouseListener, ScoiataelBack);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(scaleSetSpriteMouseListener->clone(), NorthernRealmsBack);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(scaleSetSpriteMouseListener->clone(), NilfgaardianEmpireBack);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(scaleSetSpriteMouseListener->clone(), MonstersBack);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(scaleSetSpriteMouseListener->clone(), background);

    return true;
}


void PlayPreparationScene::GoBackToMainSceneCallback(Ref* pSender)
{
	if (clickable) {
		clickable = false;
		auto Scene = MainScene::create();
		Director::getInstance()->replaceScene(TransitionFade::create(1, Scene));
	}
}

void PlayPreparationScene::passDeckBeforePassScene(CardSet set)
{
	CardCollection ccoll(set);
	std::vector<int> deckT = ccoll.getDeck();
	deckT.insert(deckT.begin(), ccoll.getLeader());
	MatchDirector::getInstance()->initDeck0 = deckT;
	MatchDirector::getInstance()->initDeck1 = deckT;
	/*switch (set)
	{
	case NullCSet:
		cocos2d::log("NS");
		break;
	case Northern:
		cocos2d::log("Northern");
		break;
	case Nilfgaardian:
		
		cocos2d::log("Nilfgaardian");
		break;
	case Monster:
		cocos2d::log("Monster");
		break;
	case Scoiateal:
		cocos2d::log("Scoiateal");
		break;
	case Neutral:
		cocos2d::log("Neutral");
		break;
	default:
		break;
	};*/
	//To 若晴：这个函数用于准备我都下一个SinglePlayScene 也许你不需要调用
}

std::vector<int> PlayPreparationScene::getUserDeck()
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
	std::vector<int> deck(deckArr, deckArr+33);
	return deck;
}


void PlayPreparationScene::replaceToPlaySceneCallback(Ref* pSender)
{
	if (clickable) {
		clickable = false;
		auto Scene = SinglePlayScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0, Scene));
	}
}