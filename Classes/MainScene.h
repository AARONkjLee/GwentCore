#pragma once

#include "cocos2d.h"

//³¡¾°ÇÐ»»½Ì³Ì
//http://www.cnblogs.com/HangZhe/p/5701019.html

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
