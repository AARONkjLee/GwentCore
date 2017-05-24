#pragma once
#include "CardSprite.h"

class CardSpriteShaded : public CardSprite {
private:
	int touchLayerOrder = 0;
public:
	void initTouchEvent();
	bool onTouchBeganFunc(cocos2d::Touch * touch, cocos2d::Event * event);
	void onTouchMovedFunc(cocos2d::Touch * touch, cocos2d::Event * event);
	void onTouchEndedFunc(cocos2d::Touch * touch, cocos2d::Event * event);
	void onTouchCancelledFunc(cocos2d::Touch * touch, cocos2d::Event * event);
};