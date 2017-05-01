#include "CardSprite.h"
#include <sstream>

USING_NS_CC;
/*
CardSprite::CardSprite()
{
}

CardSprite::CardSprite(const int & cid)
{
	cardPrototype.reload(cid);
	currentStrength = cardPrototype.getStrength();
}

CardSprite::CardSprite(const int & cid, const CPosition & posi)
{
	cardPrototype.reload(cid);
	currentStrength = cardPrototype.getStrength();
	position = posi;
}

void CardSprite::initDraw()
{
	auto BodySprite = Sprite::create(cardPrototype.getPicDir());
	this->addChild(BodySprite);
	if (cardPrototype.getCardType() == Unit) {
		auto StrengthSprite = Sprite::create("StrengthBack.png");
		this->addChild(StrengthSprite);
	}
}

CardSprite::~CardSprite()
{
}
*/

std::string CardSprite::getStrStrength()
{
	std::stringstream strengthStream;
	strengthStream << currentStrength;
	return strengthStream.str();
}

void CardSprite::initCardPrototype(int cid)
{
	cardPrototype.reload(cid);
	currentStrength = cardPrototype.getStrength();
}

CardSprite * CardSprite::create(int cid)
{
	CardSprite* sprite  = new CardSprite();
	sprite->initCardPrototype(cid);
	std::string filename = sprite->cardPrototype.getPicDir();
	if (filename.empty()) {
		filename = CARD_BACK_DIR;
	}
	if (sprite && sprite->initWithFile(filename)){
		sprite->autorelease();

		//to-do judge the CType and ULevel
		auto strengthSprite = Sprite::create(CARD_STRENGTH_BACK_DIR);
		strengthSprite->setPosition(STRENGTH_BACK_COORDINATES);
		sprite->addChild(strengthSprite);

		

		auto strengthLabel = Label::create(
			sprite->getStrStrength(), // to change to sprite->cardPrototype.getStrengthStr()
			"fonts/Marker Felt.ttf", 72);
		strengthLabel->setColor(Color3B(0,0,0));
		strengthLabel->setPosition(STRENGTH_LABEL_COORDINATES);
		sprite->addChild(strengthLabel);

		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
}
