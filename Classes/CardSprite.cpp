#include "CardSprite.h"
#include <sstream>

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

std::string CardSprite::getStrStrength()
{
	std::stringstream strengthStream;
	strengthStream << currentStrength;
	return strengthStream.str();
}

bool CardSprite::initCardPrototype(int cid)
{
	if (!cardPrototype.reload(cid)) {
		cardPrototype.reload(0);
		log("CardSprite with id %i init failed.", cid);
		return false;
	}
	else {
		return true;
	}
	//currentStrength = cardPrototype.getStrength();
}

CardSprite * CardSprite::create(int cid)
{
	CardSprite* pRet = new(std::nothrow) CardSprite();
		if (pRet && pRet->initWithID(cid))
		{ 
			pRet->autorelease(); 
			return pRet; 
		} 
		else 
		{ 
			log("CardSprite create failed with ID %i", cid);
			delete pRet; 
			pRet = nullptr; 
			return nullptr; 
		} 
}

bool CardSprite::initWithID(int cid)
{
	if (!initCardPrototype(cid)) {
		return false;
	}

	std::string filename = cardPrototype.getPicDir();
	if (filename.empty()) {
		filename = CARD_BACK_DIR;
		log("CardSprite texture cannot be found with cid %i", cid);
	}
	if (!initWithFile(filename)) {
		log("CardSprite texture init failed with cid %i", cid);
		return false;
	}
	if (cardPrototype.getCardType() == Unit) {
		bool heroFlag = cardPrototype.getUnitLevel() == Hero;
		std::string strengthBackFilename = 
			(heroFlag) ? CARD_HERO_STRENGTH_BACK_DIR : 
			CARD_STRENGTH_BACK_DIR;
		auto strengthSprite = Sprite::create(strengthBackFilename);
		strengthSprite->setName("strengthSprite");

		addChild(strengthSprite);
		strengthSprite->setPosition(
			((heroFlag) ? CS_STRENGTH_HERO_BACK_COORDINATES.width :
				CS_STRENGTH_BACK_COORDINATES.width)
			/ CARD_SPRITE_SIZE.width * (getContentSize().width),
			((heroFlag) ? CS_STRENGTH_HERO_BACK_COORDINATES.height :
				CS_STRENGTH_BACK_COORDINATES.height)
			/ CARD_SPRITE_SIZE.height * (getContentSize().height));

		auto strengthLabel = Label::create(
			getStrStrength(), 
			"fonts/HalisGR-SBook.otf", 70);
		strengthLabel->setName("strengthLabel");
		addChild(strengthLabel);
		strengthLabel->setColor(
			(heroFlag) ? Color3B::WHITE : Color3B::BLACK);
		strengthLabel->enableShadow(
			(heroFlag) ? Color4B::BLACK : Color4B(Color3B::WHITE, 64),
			Size(4, -4), 10);
		
		strengthLabel->setPosition(
			( (heroFlag) ? CS_STRENGTH_HERO_LABEL_COORDINATES.width : 
				CS_STRENGTH_LABEL_COORDINATES.width )
			/ CARD_SPRITE_SIZE.width * (getContentSize().width),
			( (heroFlag) ? CS_STRENGTH_HERO_LABEL_COORDINATES.height :
				CS_STRENGTH_LABEL_COORDINATES.height )
			/ CARD_SPRITE_SIZE.height * (getContentSize().height));
	}

	initClickEvent();

	return true;
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

void CardSprite::initClickEvent()
{
	// To-Do 一种事件只创建一个listener,其他的通过位置判断
	auto mouseEvent = EventListenerMouse::create();	
	//try {
	//	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
	//	mouseEvent->getMouseButton();
	//	std::stringstream message;
	//	message << "Mouse event: Button: " << mouseEvent->getMouseButton() << "pressed at point (" <<
	//		mouseEvent->getLocation().x << "," << mouseEvent->getLocation().y << ")";
	//	MessageBox(message.str().c_str(), "Mouse Event Details");

	//}
	//catch (std::bad_cast& e) {
	//	// Not sure what kind of event you passed us cocos, but it was the wrong one
	//	return;
	//}

	mouseEvent->onMouseMove = CC_CALLBACK_1(CardSprite::mouseMoveFunc, this);
	mouseEvent->onMouseDown = CC_CALLBACK_1(CardSprite::clickDownFunc, this);
	mouseEvent->onMouseUp = CC_CALLBACK_1(CardSprite::clickUpFunc, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseEvent, this);
}

void CardSprite::mouseMoveFunc(EventMouse * event)
{
	if (mouseEventOnTarget(event, this)) {
		//log("CardSprite %s detected move!", this->getCardPrototype().getCardName().c_str());
	}
}

void CardSprite::clickDownFunc(EventMouse* event)
{
	if (mouseEventOnTarget(event, this)) {
		log("CardSprite %s detected click down!", this->getCardPrototype().getCardName().c_str());
	}
}

void CardSprite::clickUpFunc(EventMouse* event)
{
	if (mouseEventOnTarget(event, this)) {
		log("CardSprite %s detected click up!", this->getCardPrototype().getCardName().c_str());
	}
}
