#pragma once

#include "cocos2d.h"




const std::string MAIN_BG_DIR = "MainScene/Gwent_BackPic_1920x1080_logoless.jpg";
const std::string MAIN_BUTTON_NROMAL_DIR = "MainScene/MainButtonNormal.png";
const std::string MAIN_BUTTON_SELECTED_DIR = "MainScene/MainButtonSelectedEdged.png";
const std::string MAIN_LOGO_DIR = "MainScene/Logo.png";

const std::string HALISGR_BOLD_FONTS = "fonts/HalisGR-Bold.otf";
const std::string HALISGR_FONTS = "fonts/HalisGR-SBook.otf";

//#define REPLACE_SCENE (funcName)\
//void replaceTo##funcName (Ref* pSender) {\
//	auto tScene = funcName::createScene();\
//	Director::getInstance()->replaceScene(TransitionFade::create(1, tScene)); }
//


class MainScene : public cocos2d::Scene
{
private:
	bool clickable;
public:

    virtual bool init();
    
    // a selector callback


	void replaceToPlaySceneCallback(Ref * pSender);
	void replaceToCollectionSceneCallback(Ref * pSender);
	void replaceToSettingSceneCallback(Ref * pSender);
	void menuCloseCallback(cocos2d::Ref* pSender);
	void createTestSpriteCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);



};
