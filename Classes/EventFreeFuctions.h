#pragma once
#include "cocos2d.h"

template <typename eventTypeValue, typename typeValue>
bool clickOnTarget(eventTypeValue* & eventOrTouch, typeValue & target) {
	Vec2 locationInNode = target->convertToNodeSpace(eventOrTouch->getLocation());
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