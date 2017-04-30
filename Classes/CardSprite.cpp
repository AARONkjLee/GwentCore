#include "CardSprite.h"

CardSprite::CardSprite(int cid)
{
	Card cardPrototype(cid);
	currentStrength = cardPrototype.getStrength();
}
