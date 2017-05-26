#include "CoinSprite.h"

bool CoinSprite::init(){
	auto blackCoinFrame = SpriteFrame::create(BLACK_COIN_DIR, Rect(0, 0, 1920, 1080));
	auto redCoinFrame = SpriteFrame::create(RED_COIN_DIR, Rect(0, 0, 1920, 1080));
	auto blueCoinFrame = SpriteFrame::create(BLUE_COIN_DIR, Rect(0, 0, 1920, 1080));

	auto coinKeyListener = EventListenerKeyboard::create();
	coinKeyListener->onKeyPressed = CC_CALLBACK_2(CoinSprite::keyDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(coinKeyListener, this);
	return true;
}

void CoinSprite::keyDown(EventKeyboard::KeyCode key, Event * event)
{
	if (key == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		//this->setSpriteFrame(this->redCoinFrame);
		CCLOG("UP");
	}
	else if (key == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		CCLOG("DOWN");
		//this->setSpriteFrame(this->blueCoinFrame);
	}
	else {
		CCLOG("Other");
		this->getEventDispatcher()->pauseEventListenersForTarget(this);
		//this->setSpriteFrame(this->blackCoinFrame);
	}
}
