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
	
	auto mainBGSprite = Sprite::create(MAIN_BG_DIR);
	mainBGSprite->setPosition(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height/2);
	mainLayer->addChild(mainBGSprite);

	auto closeItem = MenuItemImage::create(BUTTON_NROMAL_DIR,
		BUTTON_SELECTED_DIR,
		CC_CALLBACK_1(MainScene::menuCloseCallback, this));
	closeItem->setScale((float)68/81);
	closeItem->setPosition(Vec2(origin.x + visibleSize.width*0.324,
		origin.y + visibleSize.height*0.144));
	
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);	
	return true;
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
