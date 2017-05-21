#ifndef _CARDCOLLECTIONSCENE0__H__ 
#define _CARDCOLLECTIONSCENE0__H__ 

#include "cocos2d.h"
#include "MainScene.h" 
#include"CardCollectionScene1.h"
#include "SimpleAudioEngine.h"
#include "CardSprite.h"
#include "cardCollections.h"
#include "collectionInstance.h"

//To-do ¸ÄÃûÎª CardCollectionScene



class CardCollectionScene0 : public cocos2d::Layer
{
private:
	bool clickable;
	
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void GoBackToMainSceneCallback(cocos2d::Ref* pSender);

	std::vector<int> getUserDeck();
	void passDeckBeforePassScene(CardSet set);

	void CardCollectionScene0::replaceToPlaySceneCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(CardCollectionScene0);
};

template <typename typeValue>
bool mouseEventOnTarget_(cocos2d::EventMouse* mouseEvent, typeValue target) {
	Vec2 locationInNode = target->convertToNodeSpace(mouseEvent->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);

	// µã»÷·¶Î§ÅÐ¶Ï¼ì²â
	if (rect.containsPoint(locationInNode))
	{
		log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
		return true;
	}
	return false;
};


 
 
#endif _CARDCOLLECTIONSCENE0__H__ 
