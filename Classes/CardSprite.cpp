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
			strengthSprite->setName("strengthSprite");

			sprite->addChild(strengthSprite);
			strengthSprite->setPosition(
				((heroFlag) ? STRENGTH_HERO_BACK_COORDINATES.width :
					STRENGTH_BACK_COORDINATES.width)
				/ CARD_SIZE.width * (sprite->getContentSize().width),
				((heroFlag) ? STRENGTH_HERO_BACK_COORDINATES.height :
					STRENGTH_BACK_COORDINATES.height)
				/ CARD_SIZE.height * (sprite->getContentSize().height));

			auto strengthLabel = Label::create(
				sprite->getStrStrength(), 
				"fonts/Marker Felt.ttf", 72);
			strengthLabel->setName("strengthLabel");
			sprite->addChild(strengthLabel);
			strengthLabel->setColor(
				(heroFlag) ? Color3B::WHITE : Color3B::BLACK);
			strengthLabel->enableShadow(
				(heroFlag) ? Color4B::BLACK : Color4B(Color3B::WHITE, 64),
				Size(4, -4), 10);
			
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

void CardSprite::setCurrentStrength(int strength)
{
	auto strengthLabel = this->getChildByName<Label*>("strengthLabel");
	currentStrength = strength;
	strengthLabel->setString(this->getStrStrength());
	if (currentStrength > cardPrototype.getStrength()) {
		strengthLabel->setColor(Color3B::GREEN);
		strengthLabel->enableShadow(Color4B::BLACK, Size(4, -4), 10);
	} else if (currentStrength < cardPrototype.getStrength()) {
		strengthLabel->setColor(Color3B::RED);
		strengthLabel->enableShadow(Color4B::BLACK, Size(4, -4), 10);
	} else {
		bool heroFlag = this->cardPrototype.getUnitLevel() == Hero;
		strengthLabel->setColor(
			(heroFlag) ? Color3B::WHITE : Color3B::BLACK);
		strengthLabel->enableShadow(
			(heroFlag) ? Color4B::BLACK : Color4B(Color3B::WHITE, 64),
			Size(4, -4), 10);
	}
	auto scale11 = ScaleTo::create(0.1, 2.0);
	auto scale10 = ScaleTo::create(0.15, 1.0);
	Vector<FiniteTimeAction*> actions;
	actions.pushBack(scale11);
	actions.pushBack(scale10);
	auto sequence1110 = Sequence::create(actions);
	strengthLabel->runAction(sequence1110);
}

Card CardSprite::getCardPrototype()
{
	return cardPrototype;
}

int CardSprite::getInitStrength()
{
	return cardPrototype.getStrength();
}
