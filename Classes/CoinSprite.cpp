#include "CoinSprite.h"

USING_NS_CC;

bool CoinSprite::init(){
	coin = BlackC;

	auto blackCoin = Sprite::create(BLACK_COIN_DIR);
	blackCoin->setPosition(0, 0);
	blackCoin->setTag(0);
	this->addChild(blackCoin);

	auto redCoin = Sprite::create(RED_COIN_DIR);
	redCoin->setPosition(0, 0);
	redCoin->setVisible(false);
	redCoin->setTag(1);
	this->addChild(redCoin);

	auto blueCoin = Sprite::create(BLUE_COIN_DIR);
	blueCoin->setPosition(0, 0);
	blueCoin->setVisible(false);
	blueCoin->setTag(2);
	this->addChild(blueCoin);

	auto coinKeyListener = EventListenerKeyboard::create();
	coinKeyListener->onKeyPressed = CC_CALLBACK_2(CoinSprite::keyDown, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(coinKeyListener, this);
	return true;
}


void CoinSprite::setDebugMode(bool debug)
{
	debugMode = debug;
}


void CoinSprite::keyDown(EventKeyboard::KeyCode key, Event * event)
{
	if (debugMode) {
		if (key == EventKeyboard::KeyCode::KEY_UP_ARROW) {
			CCLOG("UP");
			changeToCoinState(RedC);
		}
		else if (key == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
			CCLOG("DOWN");
			changeToCoinState(BlueC);
		}
		else {
			CCLOG("Other");
			changeToCoinState(BlackC);
		}
	}
	if (key == EventKeyboard::KeyCode::KEY_SPACE) {
		CCLOG("SPACE on coinSprite");
	}
}


void CoinSprite::changeToCoinState(CoinState coinState)
{
	Sprite* blackCoin = (Sprite*)this->getChildByTag(0);
	Sprite* redCoin = (Sprite*)this->getChildByTag(1);
	Sprite* blueCoin = (Sprite*)this->getChildByTag(2);
	// I know these tags are magic number but I am lazy to change.
	// If you want to change it see init()
	
	if (coin == coinState) {
		return;
	}
	switch (coin)
	{
	case BlackC:
		blackCoin->setVisible(false);
		break;
	case RedC:
		redCoin->setVisible(false);
		break;
	case BlueC:
		blueCoin->setVisible(false);
		break;
	default:
		break;
	}

	switch (coinState)
	{
	case BlackC:
		blackCoin->setVisible(true);
		coin = BlackC;
		break;
	case RedC:
		redCoin->setVisible(true);
		coin = RedC;
		break;
	case BlueC:
		blueCoin->setVisible(true);
		coin = BlueC;
		break;
	default:
		break;
	}
}
