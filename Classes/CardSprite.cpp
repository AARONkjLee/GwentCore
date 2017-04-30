#include "CardSprite.h"

CardSprite::CardSprite()
{
}

CardSprite::CardSprite(int cid)
{
	cardPrototype.reload(cid);
	currentStrength = cardPrototype.getStrength();
}

CardSprite::CardSprite(int cid, CPosition posi)
{
	cardPrototype.reload(cid);
	currentStrength = cardPrototype.getStrength();
	position = posi;
}

void CardSprite::initDraw()
{
	if 
}

CardSprite::~CardSprite()
{
}
