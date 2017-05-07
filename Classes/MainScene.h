#pragma once

#include "cocos2d.h"

//�����л��̳�
//http://www.cnblogs.com/HangZhe/p/5701019.html


const std::string MAIN_BG_DIR = "MainScene/Gwent_BackPic_1920x1080_logoless.jpg";


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
