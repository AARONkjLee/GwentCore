#pragma once

#include "card.h"
#include "cocos2d.h"

const std::string CARD_BACK_DIR = "GwentCardsResources/Back.jpg";
const std::string CARD_STRENGTH_BACK_DIR = "StrengthBack.png";
const std::string CARD_HERO_STRENGTH_BACK_DIR = "StrengthBackHero.png";
const cocos2d::Size CARD_SIZE((float)674, (float)1048);
const cocos2d::Size STRENGTH_BACK_COORDINATES((float)90, (float)946);
const cocos2d::Size STRENGTH_HERO_BACK_COORDINATES((float)92, (float)944);
const cocos2d::Size STRENGTH_LABEL_COORDINATES((float)88, (float)943);
const cocos2d::Size STRENGTH_HERO_LABEL_COORDINATES((float)92, (float)943);

enum CPosition {Hand1, Hand2, Grave1, Grave2, Deck1, Deck2, 
	Weather1, Weather2, Combat1, Combat2, Ranged1, Ranged2, 
	Seige1, Seige2, Void1, Void2};

class CardSprite : public cocos2d::Sprite{
private:
	Card cardPrototype;
	int currentStrength;
	std::string getStrStrength();
	CPosition position;

	// Use this->getChildByName<Sprite*>("strengthSprite")
	// and this->getChildByName<Label*>("strengthLabel")
	// to access its strength aprt

	/*
	Do NOT do like below!  To inherit from Sprite, see:
	http://blog.csdn.net/while0/article/details/25615685

	Sprite* BodySprite;
	Sprite* StrengthSprite;

	If someday we want to implement DIY cards, we may need these

	Sprite* SetSprite;
	Sprite* UTypeSprite;
	Sprite* SpellSprite;
	*/

public:
	void initCardPrototype(int cid);
	static CardSprite* create(int cid);
	void setCurrentStrength(int strength);
	Card getCardPrototype();
	int getInitStrength();

	/*
	Do NOT do like below!  To inherit from Sprite, see:
	http://blog.csdn.net/while0/article/details/25615685

	CardSprite();
	CardSprite(const int & cid);
	CardSprite(const int & cid, const CPosition & posi);
	void initDraw();
	~CardSprite();
	*/

	//CREATE_FUNC(CardSprite);  useless for define the create function manually
};