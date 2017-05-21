#pragma once

#include "cocos2d.h"
#include "MainScene.h"
#include "PlayPreparationScene.h"
#include "CardSprite.h"
#include "MatchDirector.h"
#include "LeaderCardSprite.h"


const std::string PLAY_SCENE_BG_DIR = "PlayScene/PlaySceneBG.jpg";

USING_NS_CC;

class SinglePlayScene : public cocos2d::Layer
{
private:
	bool clickable;/*
	Size visibleSize;
	Vec2 origin;*/
	//std::vector<CardSprite*> hand0s;
	//std::vector<CardSprite*> hand1s;
	//std::vector<CardSprite*> combat0s;
	//std::vector<CardSprite*> combat1s;
	//std::vector<CardSprite*> ranged0s;
	//std::vector<CardSprite*> ranged1s;
	//std::vector<CardSprite*> siege0s;
	//std::vector<CardSprite*> siege1s;
	Sprite* coin;
	LeaderCardSprite* leader0, *leader1;

public:
	void initWithStarter(int Starter);



    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void GoBackToMainSceneCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(SinglePlayScene);
};
