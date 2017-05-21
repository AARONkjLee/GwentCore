#include "LeaderCardSprite.h" 

//  关于Action的教程
//  http://www.gamefromscratch.com/post/2014/10/11/Cocos2d-x-Tutorial-Series-Game-loops-Updates-and-Action-Handling.aspx
//  49种类的Action
//  http://blog.csdn.net/liuhong135541/article/details/24374227

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


void LeaderCardSprite::initLeader(int cid)
{
	leader.reload(cid);
}

LeaderCardSprite * LeaderCardSprite::create(int cid)
{
	LeaderCardSprite* sprite = new LeaderCardSprite();
	sprite->initLeader(cid);
	std::string filename;
	filename = sprite->leader.getPicDir();
	if (sprite && sprite->initWithFile(filename)) {
		sprite->autorelease();		
		return sprite;
	}

	CC_SAFE_DELETE(sprite);
	return nullptr;
}


LeaderCard LeaderCardSprite::getLeader()
{
	return leader;
}

