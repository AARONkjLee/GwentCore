#pragma once

#include "card.h"
#include "cocos2d.h"
#include "CardEffectManager.h"
#include "EventFreeFuctions.h"

const std::string CARD_BACK_DIR = "GwentCardsResources/Back.jpg";
const std::string CARD_STRENGTH_BACK_DIR = "GwentCardsResources/StrengthBack.png";
const std::string CARD_HERO_STRENGTH_BACK_DIR = "GwentCardsResources/StrengthBackHero.png";

const cocos2d::Size CARD_SPRITE_SIZE((float)674, (float)1048);
const cocos2d::Size CS_STRENGTH_BACK_COORDINATES((float)90, (float)946);
const cocos2d::Size CS_STRENGTH_HERO_BACK_COORDINATES((float)92, (float)944);
const cocos2d::Size CS_STRENGTH_LABEL_COORDINATES((float)88, (float)939);
const cocos2d::Size CS_STRENGTH_HERO_LABEL_COORDINATES((float)92, (float)939);


class CardSprite : public cocos2d::Sprite{
private:
	Card cardPrototype;
	int currentStrength;
	std::string getStrStrength();
	CPosition position;

public:
	bool initCardPrototype(int cid);
	static CardSprite* create(int cid);
	bool init();
	bool initWithID(int cid);
	void setCurrentStrength(int strength);
	Card getCardPrototype();
	int getInitStrength();

	void initMouseEvent();
	void initTouchEvent();

	void mouseMoveFunc(cocos2d::EventMouse* event);
	void clickDownFunc(cocos2d::EventMouse* event);  //  判断是那个鼠标按键 用 event->getMouseButton() 判断
	void clickUpFunc(cocos2d::EventMouse* event);

	bool onTouchBeganFunc(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMovedFunc(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEndedFunc(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchCancelledFunc(cocos2d::Touch* touch, cocos2d::Event* event);

	CREATE_FUNC(CardSprite);
};