//#include "CardSpriteTest.h"
#include "SimpleAudioEngine.h"
#include "MainScene.h"

USING_NS_CC;

bool MainScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto mainLayer = Layer::create();

	this->addChild(mainLayer);
	
	/*auto closeItem = MenuItemImage::create("MainButtonNormal.png",
		"MainButtonSelected.png",
		CC_CALLLBACK_1(menuCloseCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));*/

	return false;
}

void MainScene::menuCloseCallback(Ref* pSender)
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

void MainScene::replaceSceneCallback(cocos2d::Scene * sceneChangingTo)
{
}
