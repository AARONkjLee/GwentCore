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
	int initStrength = thisCard.getStrength();  //ԭ��
	if (BattleInfoManager::cPositionOnField(cPosi) &&
		thisCard.getUnitLevel() == Hero) { //Ӣ�۷���ԭ��
		return initStrength;
	}
	else {
		//������Ӱ��
		if ((thisCard.getUnitType() == CloseCombat && 
			BattleInfoManager::getInstance()->isFrosting()) || // ��ս��˪��
			(thisCard.getUnitType() == RangedCombat &&
			BattleInfoManager::getInstance()->isFogging()) || // Զս����
			(thisCard.getUnitType() == Siege &&
			BattleInfoManager::getInstance()->isRaining()) // ���Ǳ���
			) {
			if (initStrength!=0) initStrength = 1; // �����������1
		}

		int result = initStrength; // ����resultΪ����������
		int controller = BattleInfoManager::getPlayerFromCPosition(cPosi); // ������
		std::vector<int> searchPositionVec; // ���ѷ�Χ��Vec
		switch (thisCard.getUnitType())  // ���ݿ�������
		{
		case CloseCombat: // ��ս��Ӧ�����ߵ�������Χ
			searchPositionVec = (controller ? field->p1Combat : field->p0Combat); 
			break;
		case RangedCombat: // Զս��Ӧ�����ߵ�������Χ
			searchPositionVec = (controller ? field->p1Ranged : field->p0Ranged);
			break;
		case Siege: // ���Ƕ�Ӧ�����ߵ�������Χ
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
