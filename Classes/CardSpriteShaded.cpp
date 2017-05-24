#include "CardSpriteShaded.h"

int globalTouchLayerOrder = -1;
bool touchSwallowFlag = true;

void CardSpriteShaded::initTouchEvent()
{
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(CardSprite::onTouchBeganFunc, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(CardSprite::onTouchMovedFunc, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(CardSprite::onTouchEndedFunc, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(CardSprite::onTouchCancelledFunc, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool CardSpriteShaded::onTouchBeganFunc(cocos2d::Touch * touch, cocos2d::Event * event)
{
	if (!touchSwallowFlag) {
		touchSwallowFlag = true;
		return true;
	}
	log("touch began on %i %s CardSpriteShaded", getCardPrototype().getID(), getCardPrototype().getCardName().c_str());
	touchSwallowFlag = false;
	return false;
}

void CardSpriteShaded::onTouchMovedFunc(cocos2d::Touch * touch, cocos2d::Event * event)
{
	log("touch moved on %i %s CardSpriteShaded", getCardPrototype().getID(), getCardPrototype().getCardName().c_str());
}

void CardSpriteShaded::onTouchEndedFunc(cocos2d::Touch * touch, cocos2d::Event * event)
{
	log("touch ended on %i %s CardSpriteShaded", getCardPrototype().getID(), getCardPrototype().getCardName().c_str());
}

void CardSpriteShaded::onTouchCancelledFunc(cocos2d::Touch * touch, cocos2d::Event * event)
{
	log("touch cancelled on %i %s CardSpriteShaded", getCardPrototype().getID(), getCardPrototype().getCardName().c_str());
}
