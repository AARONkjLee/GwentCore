#ifndef _CARDCOLLECTIONSCENE0__H__ 
#define _CARDCOLLECTIONSCENE0__H__ 

#include "cocos2d.h"

//To-do ¸ÄÃûÎª CardCollectionScene

class CardCollectionScene0 : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(CardCollectionScene0);
};

 
 
#endif _CARDCOLLECTIONSCENE0__H__ 
