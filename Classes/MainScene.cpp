//#include "CardSpriteTest.h"
#include "SimpleAudioEngine.h"
#include "MainScene.h"

// For Scene Test
#include "PlaySceneTest.h"
#include "CollectionSceneTest.h"
#include "SettingSceneTest.h"
#include "CardCollectionScene.h"

USING_NS_CC;

// To-do 加入一个可点击flag 默认true 当已经点了一个按钮的时候 这个flag为false
// 所有按钮函数 先判断可点击flag为true再运行
// 防止快速点击多个按钮导致的冲突

//场景切换教程
//http://www.cnblogs.com/HangZhe/p/5701019.html
//http://blog.csdn.net/lttree/article/details/38185641

//菜单教程
//http://www.tuicool.com/articles/immUVn

bool MainScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	int labelFontSize = 50*visibleSize.width/1920;

	//auto collectionScene = CollectionSceneTest::createScene();
	//auto settingScene = SettingSceneTest::createScene();


	auto mainLayer = Layer::create();
	this->addChild(mainLayer);
	

	auto logoSprite = Sprite::create(LOGO_DIR);
	logoSprite->setPosition(Vec2(origin.x + visibleSize.width*0.324,
		origin.y + visibleSize.height*0.711));
	logoSprite->setScale((float)655/900);
	mainLayer->addChild(logoSprite, 1);


	auto mainBGSprite = Sprite::create(MAIN_BG_DIR);
	mainBGSprite->setPosition(origin.x + visibleSize.width/2,
		origin.y + visibleSize.height/2);
	mainLayer->addChild(mainBGSprite);

	auto playButton = MenuItemImage::create(BUTTON_NROMAL_DIR,
		BUTTON_SELECTED_DIR,
		CC_CALLBACK_1(MainScene::replaceToPlaySceneCallback, this));
	playButton->setScale((float)68 / 81);
	playButton->setPosition(Vec2(origin.x + visibleSize.width*0.324,
		origin.y + visibleSize.height*0.384));

	auto playLable = Label::create("PLAY", HALISGR_BOLD_FONTS, labelFontSize);
	playLable->enableShadow(Color4B::BLACK, Size(4, -4), 10);  // Last int for blur radius, which is to do by cocos2ds
	playLable->setPosition(Vec2(playButton->getContentSize().width/2, playButton->getContentSize().height / 2));
	playButton->addChild(playLable);
	

	auto collectionButton = MenuItemImage::create(BUTTON_NROMAL_DIR,
		BUTTON_SELECTED_DIR,
		CC_CALLBACK_1(MainScene::replaceToCollectionSceneCallback, this));
	collectionButton->setScale((float)68 / 81);
	collectionButton->setPosition(Vec2(origin.x + visibleSize.width*0.324,
		origin.y + visibleSize.height*0.304));

	auto collectionLable = Label::create("COLLECTION", HALISGR_BOLD_FONTS, 0.96*labelFontSize);
	collectionLable->enableShadow(Color4B::BLACK, Size(4, -4), 10);  // Last int for blur radius, which is to do by cocos2ds
	collectionLable->setPosition(Vec2(collectionButton->getContentSize().width / 2, collectionButton->getContentSize().height / 2));
	collectionButton->addChild(collectionLable);


	auto settingButton = MenuItemImage::create(BUTTON_NROMAL_DIR,
		BUTTON_SELECTED_DIR,
		CC_CALLBACK_1(MainScene::replaceToSettingSceneCallback, this));
	settingButton->setScale((float)68 / 81);
	settingButton->setPosition(Vec2(origin.x + visibleSize.width*0.324,
		origin.y + visibleSize.height*0.224));

	auto settingLable = Label::create("SETTING", HALISGR_BOLD_FONTS, labelFontSize);
	settingLable->enableShadow(Color4B::BLACK, Size(4, -4), 10);  // Last int for blur radius, which is to do by cocos2ds
	settingLable->setPosition(Vec2(settingButton->getContentSize().width / 2, settingButton->getContentSize().height / 2));
	settingButton->addChild(settingLable);

	
	auto closeButton = MenuItemImage::create(BUTTON_NROMAL_DIR,
		BUTTON_SELECTED_DIR,
		CC_CALLBACK_1(MainScene::menuCloseCallback, this));
	closeButton->setScale((float)68 / 81);
	closeButton->setPosition(Vec2(origin.x + visibleSize.width*0.324,
		origin.y + visibleSize.height*0.144));

	auto closeLable = Label::create("EXIT", HALISGR_BOLD_FONTS, labelFontSize);
	closeLable->enableShadow(Color4B::BLACK, Size(4, -4), 10);  // Last int for blur radius, which is to do by cocos2ds
	closeLable->setPosition(Vec2(closeButton->getContentSize().width / 2, closeButton->getContentSize().height / 2));
	closeButton->addChild(closeLable);


	auto menu = Menu::create(playButton, collectionButton, settingButton, closeButton, NULL);
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

void MainScene::createTestSpriteCallback(cocos2d::Ref * pSender)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto testLayer = Layer::create();
	this->addChild(testLayer,1);
	auto testSprite = Sprite::create("HelloWorld.png");
	testSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	testLayer->addChild(testSprite);
	
}

float transitionTime = 1.0;

void MainScene::replaceToPlaySceneCallback(Ref* pSender)
{
	auto Scene = PlaySceneTest::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(transitionTime, Scene));
}

void MainScene::replaceToCollectionSceneCallback(Ref* pSender)
{
	//auto Scene = CardCollection::createScene();
	auto Scene = CardCollectionScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(transitionTime, Scene));
}

void MainScene::replaceToSettingSceneCallback(Ref* pSender)
{
	auto Scene = SettingSceneTest::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(transitionTime, Scene));
}

