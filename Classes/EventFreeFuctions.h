#pragma once
#include "cocos2d.h"

template <typename typeValue>
bool mouseEventOnTarget(cocos2d::EventMouse* & mouseEvent, typeValue & target) {
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