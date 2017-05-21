#ifndef __LeaderCardSprite_H__ 
#define __LeaderCardSprite_H__ 

#include "leaderCard.h"
#include "cocos2d.h"
#include <string>

//const std::string CARD_BACK_DIR = "GwentCardsResources/Back.jpg";
//const std::string CARD_STRENGTH_BACK_DIR = "GwentCardsResources/StrengthBack.png";
//const std::string CARD_HERO_STRENGTH_BACK_DIR = "GwentCardsResources/StrengthBackHero.png";



class LeaderCardSprite : public cocos2d::Sprite {
private:
	LeaderCard leader;

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
	void initLeader(int cid);
	static LeaderCardSprite* create(int cid);
	LeaderCard getLeader();

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
 
#endif __LeaderCardSprite_H__ 
