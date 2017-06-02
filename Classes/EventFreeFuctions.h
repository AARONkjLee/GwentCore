#pragma once
#include "cocos2d.h"

USING_NS_CC;

template <typename eventTypeValue, typename typeValue>
bool clickOnTarget(eventTypeValue* & event, typeValue & target) {
	Point locationInNode = target->convertToNodeSpace(Director::getInstance()->convertToGL((event->getLocation())));
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);
	// 点击范围判断检测
	if (rect.containsPoint(locationInNode))
	{
		//log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
		return true;
	}
	return false;
};


template <typename typeValue>
bool clickOnTarget(cocos2d::Touch* & touch, typeValue & target) {
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);
	// 点击范围判断检测
	if (rect.containsPoint(locationInNode))
	{
		pointHasOpacityOnPNGTarget(locationInNode, target);
		//log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
		return true;
	}
	return false;
};


template <typename typeValue>
void pointHasOpacityOnPNGTarget(const cocos2d::Point & touchLocation, typeValue target) //传入触摸点touchLocation
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	//计算touchLocation相对于mysprite的boundingBox左下角的坐标， 因为一般的锚点都在sprite中心，所以加了半个ContentSize
	auto ps = touchLocation - target->getPosition() + Point(target->getContentSize().width / 2, target->getContentSize().height / 2);
	
	//加载和target相同的图片，我是实现的png的，alpha通道很好用
	Image *myImage = new Image();
	//Sprite::getTexture();
	//Texture2D::getPath();
	myImage->initWithImageFile(target->getTexture()->getPath());
	unsigned char *data = myImage->getData();  //这里就是图片数据了
											   //根据刚刚计算的相对坐标值，计算出触摸点代表了哪一个像素点????????????然后再提取出该像素点的alpha值
											   //注意：因为图片坐标（0，0）是在左上角，所以要和触摸点的Y转换一下，也就是“(myImage->getHeight() - (int)(ps.y) - 1)”
	int pa = 4 * ((myImage->getHeight() - (int)(ps.y) - 1) * myImage->getWidth() + (int)(ps.x)) + 3;
	unsigned int ap = data[pa];
	//判断alpha值不为零时，也就是触摸在了不规则sprite的有图像的地方，这时再处理需要的逻辑内容就好了
	if (ap != 0)
	{
		CCLOG("check");
	}
}