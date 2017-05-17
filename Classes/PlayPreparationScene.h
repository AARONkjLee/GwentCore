#pragma once

#include "cocos2d.h"
#include "MainScene.h"
#include "BattleInfoManager.h"

std::vector<int> getUserDeck();

struct GUIActCell {
	ActCell actCell;
	std::string info;
};

struct GUICell {

};


class PlayPreparationScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void GoBackToMainSceneCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(PlayPreparationScene);
};
