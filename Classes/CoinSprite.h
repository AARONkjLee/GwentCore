#pragma once
#include "cocos2d.h"

const std::string BLACK_COIN_DIR = "PlayScene/CoinBlack.png";
const std::string RED_COIN_DIR = "PlayScene/CoinRed.png";
const std::string BLUE_COIN_DIR = "PlayScene/CoinBlue.png";

USING_NS_CC;

class CoinSprite : public cocos2d::Sprite{
private:
	SpriteFrame* blackCoinFrame, *redCoinFrame, *blueCoinFrame;
public:
	bool init();
	CREATE_FUNC(CoinSprite);
	void keyDown(EventKeyboard::KeyCode key, Event* event);
};