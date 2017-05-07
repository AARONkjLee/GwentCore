#pragma once

#include "cocos2d.h"
#include "MainScene.h"


class PlaySceneTest : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void GoBackToMainSceneCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(PlaySceneTest);
};
