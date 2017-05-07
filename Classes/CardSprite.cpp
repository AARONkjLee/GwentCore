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
		if (sprite->cardPrototype.getCardType() == Unit) {
			bool heroFlag = sprite->cardPrototype.getUnitLevel() == Hero;
			std::string strengthBackFilename = 
				(heroFlag) ? CARD_HERO_STRENGTH_BACK_DIR : 
				CARD_STRENGTH_BACK_DIR;
			auto strengthSprite = Sprite::create(strengthBackFilename);
			sprite->addChild(strengthSprite);
			strengthSprite->setPosition(
				((heroFlag) ? STRENGTH_HERO_BACK_COORDINATES.width :
					STRENGTH_BACK_COORDINATES.width)
				/ CARD_SIZE.width * (sprite->getContentSize().width),
				((heroFlag) ? STRENGTH_HERO_BACK_COORDINATES.height :
					STRENGTH_BACK_COORDINATES.height)
				/ CARD_SIZE.height * (sprite->getContentSize().height));

			auto strengthLabel = Label::create(
				sprite->getStrStrength(), // to change to sprite->cardPrototype.getStrengthStr()
				"fonts/Marker Felt.ttf", 72);
			sprite->addChild(strengthLabel);
			strengthLabel->setColor(
				(heroFlag) ? Color3B(255, 255, 255) : Color3B(0, 0, 0));
			strengthLabel->setPosition(
				( (heroFlag) ? STRENGTH_HERO_LABEL_COORDINATES.width : 
					STRENGTH_LABEL_COORDINATES.width )
				/ CARD_SIZE.width * (sprite->getContentSize().width),
				( (heroFlag) ? STRENGTH_HERO_LABEL_COORDINATES.height :
					STRENGTH_LABEL_COORDINATES.height )
				/ CARD_SIZE.height * (sprite->getContentSize().height));
		}
		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
}
