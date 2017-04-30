#pragma once

#include "card.h"
#include "cocos2d.h"

enum CPosition {Hand1, Hand2, Grave1, Grave2, Deck1, Deck2, 
	Weather1, Weather2, Combat1, Combat2, Ranged1, Ranged2, 
	Seige1, Seige2, Void1, Void2};

class CardSprite : public cocos2d::Sprite{
private:
	Card cardPrototype;
	int currentStrength;
	CPosition position;
	Sprite* BodySprite;
	Sprite* StrengthSprite;

	/*
	If someday we want to implement DIY cards, we may need these

	Sprite* SetSprite;
	Sprite* UTypeSprite;
	Sprite* SpellSprite;
	*/

public:
	CardSprite();
	CardSprite(int cid);
	CardSprite(int cid, CPosition posi);
	void initDraw();
	~CardSprite();
};