#ifndef _CARDCOLLECTIONSCENE1__H__ 
#define _CARDCOLLECTIONSCENE1__H__ 

#include "cocos2d.h"
#include "MainScene.h" 
#include "CardCollectionScene2.h"
#include "SimpleAudioEngine.h"
#include "CardSprite.h"
#include "cardCollections.h"
#include "LeaderCardSprite.h"
#include "collectionInstance.h"

//To-do ¸ÄÃûÎª CardCollectionScene

class CardCollectionScene1 : public cocos2d::Layer
{
private:
	bool clickable;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	// a selector callback
	void GoBackToMainSceneCallback(cocos2d::Ref* pSender);

	std::vector<int> getUserDeck();
	void passLeaderBeforePassScene(int leaderId);

	void CardCollectionScene1::replaceToPlaySceneCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(CardCollectionScene1);
};

template <typename typeValue>
bool mouseEventOnTarget__(cocos2d::EventMouse* mouseEvent, typeValue target) {
	Vec2 locationInNode = target->convertToNodeSpace(mouseEvent->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);

	// µã»÷·¶Î§ÅÐ¶Ï¼ì²â
	if (rect.containsPoint(locationInNode))
	{
		//log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
		return true;
	}
	return false;
};




#endif _CARDCOLLECTIONSCENE1__H__ 
