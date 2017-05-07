#pragma once

#include "cocos2d.h"

//³¡¾°ÇÐ»»½Ì³Ì
//http://www.cnblogs.com/HangZhe/p/5701019.html


const std::string MAIN_BG_DIR = "MainScene/Gwent_BackPic_1920x1080_logoless.jpg";
const std::string BUTTON_NROMAL_DIR = "MainScene/MainButtonNormal.png";
const std::string BUTTON_SELECTED_DIR = "MainScene/MainButtonSelected.png";
const std::string LOGO_DIR = "MainScene/Logo.png";


class MainScene : public cocos2d::Scene
{
public:

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
	void replaceSceneCallback(cocos2d::Scene* sceneChangingTo);

    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
};
