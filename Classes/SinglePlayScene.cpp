#include "CardSprite.h"
#include "SimpleAudioEngine.h"
#include "SinglePlayScene.h"
#include "PlayPreparationScene.h"

USING_NS_CC;

auto visibleSize = Director::getInstance()->getVisibleSize();

void SinglePlayScene::initWithStarter(int Starter)
{
	leader0 = LeaderCardSprite::create(BattleInfoManager::getInstance()->getBattlefield().p0LeaderID);
	leader0->setScale(0.08);
	leader0->setPosition(Vec2(WIN_CORDINATE_2_GL(3.06, 0.22, 2.11, 1.36)));
	leader1 = LeaderCardSprite::create(BattleInfoManager::getInstance()->getBattlefield().p1LeaderID);
	leader1->setScale(0.08);
	leader1->setPosition(Vec2(WIN_CORDINATE_2_GL(3.06,16.62, 2.11, 1.36)));
	this->addChild(leader0);
	this->addChild(leader1);


}

Scene* SinglePlayScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SinglePlayScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SinglePlayScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(SinglePlayScene::GoBackToMainSceneCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

	auto background = Sprite::create(PLAY_SCENE_BG_DIR);
	background->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	this->addChild(background);

	MatchDirector::getInstance()->setGUILayer(this);
	MatchDirector::getInstance()->MainMatchLoop();

    return true;
}


void SinglePlayScene::GoBackToMainSceneCallback(Ref* pSender)
{
	if (clickable) {
		clickable = false;
		auto Scene = MainScene::create();
		Director::getInstance()->replaceScene(TransitionFade::create(1, Scene));
	}
}
