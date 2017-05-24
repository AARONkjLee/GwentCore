#include "CardSpriteWithLayer.h"


void CardSpriteWithLayer::initTouchEvent()
{
	auto shader = Layer::create();
	shader->setOpacity(GLubyte(0));
	this->addChild(shader);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(CardSprite::onTouchBeganFunc, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(CardSprite::onTouchMovedFunc, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(CardSprite::onTouchEndedFunc, this);
	touchListener->onTouchCancelled = CC_CALLBACK_2(CardSprite::onTouchCancelledFunc, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this->getChildByName("shader"));
}
