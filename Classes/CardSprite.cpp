#include "CardSprite.h"

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
