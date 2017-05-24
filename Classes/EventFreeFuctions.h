#pragma once
#include "cocos2d.h"

template <typename eventTypeValue, typename typeValue>
bool clickOnTarget(eventTypeValue* & event, typeValue & target) {
	Vec2 locationInNode = target->convertToNodeSpace(Director::getInstance()->convertToGL((event->getLocation())));
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


template <typename typeValue>
bool clickOnTarget(cocos2d::Touch* & touch, typeValue & target) {
	Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
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