#ifndef _CARDCOLLECTIONSCENE1__H__ 
#define _CARDCOLLECTIONSCENE1__H__ 

#include "cocos2d.h"
#include "MainScene.h" 
#include "CardCollectionScene2.h"
#include "SimpleAudioEngine.h"
#include "CardSprite.h"
#include "cardCollections.h"
#include "leaderCardSprite.h"

//To-do ����Ϊ CardCollectionScene

class CardCollectionScene1 : public cocos2d::Layer
{
private:
	bool clickable;
	CardCollection collection;
public:
	static cocos2d::Scene* createScene(CardCollection collection_);
	virtual bool init();

	// a selector callback
	void GoBackToMainSceneCallback(cocos2d::Ref* pSender);

	std::vector<int> getUserDeck();
	void passLeaderBeforePassScene(LeaderCard leader);

	void CardCollectionScene1::replaceToPlaySceneCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(CardCollectionScene1);
};

template <typename typeValue>
bool mouseEventOnTarget__(cocos2d::EventMouse* mouseEvent, typeValue target) {
	Vec2 locationInNode = target->convertToNodeSpace(mouseEvent->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);

	// �����Χ�жϼ��
	if (rect.containsPoint(locationInNode))
	{
		//log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
		return true;
	}
	return false;
};




#endif _CARDCOLLECTIONSCENE1__H__ 
