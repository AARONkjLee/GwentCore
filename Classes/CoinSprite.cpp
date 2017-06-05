#include "CoinSprite.h"

USING_NS_CC;

bool CoinSprite::init(){
	coin = BlackC;

	auto blackCoin = Sprite::create(BLACK_COIN_DIR);
	blackCoin->setPosition(0, 0);
	blackCoin->setName("blackCoinSprite");
	this->addChild(blackCoin);

	auto redCoin = Sprite::create(RED_COIN_DIR);
	redCoin->setPosition(0, 0);
	redCoin->setOpacity(0);
	redCoin->setName("redCoinSprite");
	this->addChild(redCoin);

	auto blueCoin = Sprite::create(BLUE_COIN_DIR);
	blueCoin->setPosition(0, 0);
	blueCoin->setOpacity(0);
	blueCoin->setName("blueCoinSprite");
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
	if (coin == coinState) {
		return;
	}

	std::string oldChildSpriteName;
	switch (coin)
	{
	case BlackC:
		oldChildSpriteName = "blackCoinSprite";
		break;
	case RedC:
		oldChildSpriteName = "redCoinSprite";
		break;
	case BlueC:
		oldChildSpriteName = "blueCoinSprite";
		break;
	default:
		break;
	}
	Sprite* oldCoinSprite = (Sprite*)this->getChildByName(oldChildSpriteName);

	std::string newChildSpriteName;
	switch (coinState)
	{
	case BlackC:
		newChildSpriteName = "blackCoinSprite";
		coin = BlackC;
		break;
	case RedC:
		newChildSpriteName = "redCoinSprite";
		coin = RedC;
		break;
	case BlueC:
		newChildSpriteName = "blueCoinSprite";
		coin = BlueC;
		break;
	default:
		break;
	}
	Sprite* mewCoinSprite = (Sprite*)this->getChildByName(newChildSpriteName);

	oldCoinSprite->runAction(FadeOut::create(0.5));
	mewCoinSprite->runAction(FadeIn::create(0.5));
}
