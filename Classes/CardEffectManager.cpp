#include "CardEffectManager.h"

static CardEffectManager* s_SharedCardEffectManager = nullptr;

void CardEffectManager::updateField()
{
	field = &BattleInfoManager::getInstance()->getBattlefield();
}

CardEffectManager::CardEffectManager()
{
}

CardEffectManager::~CardEffectManager()
{
}

CardEffectManager * CardEffectManager::getInstance()
{
	if (!s_SharedCardEffectManager)
	{
		s_SharedCardEffectManager = new (std::nothrow) CardEffectManager;
		//s_SharedCardEffectManager->init();
	}
	return s_SharedCardEffectManager;
}

int CardEffectManager::getCardCurrentStrengthWithPositon(int cid, CPosition cPosi)
{
	updateField();
	BattleInfoManager::getInstance();
	Card thisCard = BattleInfoManager::getCardWithID(cid);
	int initStrength = thisCard.getStrength();  //原攻
	if (BattleInfoManager::cPositionOnField(cPosi) &&
		thisCard.getUnitLevel() == Hero) { //英雄返回原攻
		return initStrength;
	}
	else {
		//被天气影响
		if ((thisCard.getUnitType() == CloseCombat && 
			BattleInfoManager::getInstance()->isFrosting()) || // 近战被霜冻
			(thisCard.getUnitType() == RangedCombat &&
			BattleInfoManager::getInstance()->isFogging()) || // 远战被雾
			(thisCard.getUnitType() == Siege &&
			BattleInfoManager::getInstance()->isRaining()) // 攻城被雨
			) {
			if (initStrength!=0) initStrength = 1; // 基础攻击变成1
		}

		int result = initStrength; // 定义result为基础攻击力
		int controller = BattleInfoManager::getPlayerFromCPosition(cPosi); // 控制者
		std::vector<int> searchPositionVec; // 搜搜范围的Vec
		switch (thisCard.getUnitType())  // 根据卡牌类型
		{
		case CloseCombat: // 近战对应控制者的搜索范围
			searchPositionVec = (controller ? field->p1Combat : field->p0Combat); 
			break;
		case RangedCombat: // 远战对应控制者的搜索范围
			searchPositionVec = (controller ? field->p1Ranged : field->p0Ranged);
			break;
		case Siege: // 攻城对应控制者的搜索范围
			searchPositionVec = (controller ? field->p1Siege : field->p0Siege);
			break;
		default:
			break;
		}

		for (int i : searchPositionVec) {
			std::vector<EffectType> currentEffects = BattleInfoManager::getCardWithID(i).getEffects();
			result += std::count(currentEffects.begin(), currentEffects.end(), MoraleBooste);
			result += initStrength*std::count(currentEffects.begin(), currentEffects.end(), TightBonde);
		}
		bool doubleFlag = false;
		for (int i : searchPositionVec) {
			std::vector<EffectType> currentEffects = BattleInfoManager::getCardWithID(i).getEffects();
			if ((bool)std::count(currentEffects.begin(), currentEffects.end(), SpellHorne)) {
				doubleFlag = true;
				break;
			}
			if (i != cid && (bool)std::count(currentEffects.begin(), currentEffects.end(), UnitHorne)) {
				doubleFlag = true;
				break;
			}
		}

		result += result*(int)doubleFlag;
		return result;
	}
}
