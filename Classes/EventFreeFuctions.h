#pragma once
#include "cocos2d.h"

USING_NS_CC;

template <typename eventTypeValue, typename typeValue>
bool clickOnTarget(eventTypeValue* & event, typeValue & target) {
	Point locationInNode = target->convertToNodeSpace(Director::getInstance()->convertToGL((event->getLocation())));
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


template <typename typeValue>
bool clickOnTarget(cocos2d::Touch* & touch, typeValue & target) {
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);
	// �����Χ�жϼ��
	if (rect.containsPoint(locationInNode))
	{
		pointHasOpacityOnPNGTarget(locationInNode, target);
		//log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
		return true;
	}
	return false;
};


template <typename typeValue>
void pointHasOpacityOnPNGTarget(const cocos2d::Point & touchLocation, typeValue target) //���봥����touchLocation
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	//����touchLocation�����mysprite��boundingBox���½ǵ����꣬ ��Ϊһ���ê�㶼��sprite���ģ����Լ��˰��ContentSize
	auto ps = touchLocation - target->getPosition() + Point(target->getContentSize().width / 2, target->getContentSize().height / 2);
	
	//���غ�target��ͬ��ͼƬ������ʵ�ֵ�png�ģ�alphaͨ���ܺ���
	Image *myImage = new Image();
	//Sprite::getTexture();
	//Texture2D::getPath();
	myImage->initWithImageFile(target->getTexture()->getPath());
	unsigned char *data = myImage->getData();  //�������ͼƬ������
											   //���ݸոռ�����������ֵ��������������������һ�����ص�????????????Ȼ������ȡ�������ص��alphaֵ
											   //ע�⣺��ΪͼƬ���꣨0��0���������Ͻǣ�����Ҫ�ʹ������Yת��һ�£�Ҳ���ǡ�(myImage->getHeight() - (int)(ps.y) - 1)��
	int pa = 4 * ((myImage->getHeight() - (int)(ps.y) - 1) * myImage->getWidth() + (int)(ps.x)) + 3;
	unsigned int ap = data[pa];
	//�ж�alphaֵ��Ϊ��ʱ��Ҳ���Ǵ������˲�����sprite����ͼ��ĵط�����ʱ�ٴ�����Ҫ���߼����ݾͺ���
	if (ap != 0)
	{
		CCLOG("check");
	}
}