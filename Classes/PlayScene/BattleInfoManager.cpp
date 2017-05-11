#include "BattleInfoManager.h"

static BattleInfoManager* s_SharedBattleInfo = nullptr;

BattleInfoManager::BattleInfoManager()
{
}

BattleInfoManager::~BattleInfoManager()
{
}

BattleInfoManager * BattleInfoManager::getInstance()
{
	if (!s_SharedBattleInfo)
	{
		s_SharedBattleInfo = new (std::nothrow) BattleInfoManager;
		s_SharedBattleInfo->init();
	}

	return s_SharedBattleInfo;
}

bool BattleInfoManager::init()
{
	return true;
}

bool BattleInfoManager::initWithDecks(const std::vector<int>& deck0, const std::vector<int>& deck1)
{
	if (!deck0.size() || !deck1.size()) {
		return false;
	}
	//deck[0] is LeaderID and then cardIDs
	Battlefield.p0LeaderID = deck0[0];
	Battlefield.p0LeaderAviable = true;
	Battlefield.p1LeaderID = deck1[0];
	Battlefield.p1LeaderAviable = true;
	Battlefield.p0Deck = std::vector<int> (-1, deck0.size() - 1);
	Battlefield.p1Deck = std::vector<int> (-1, deck1.size() - 1);

	for (int i = 1; i < deck0.size(); i++) {
		Battlefield.p0Deck[i-1] = (deck0[i], 0);
	}
	for (int i = 1; i < deck1.size(); i++) {
		Battlefield.p1Deck[i - 1] = (deck1[i], 0);
	}

	return true;
}

bool BattleInfoManager::initWithFirstPlayer(const int & playerNo)
{
	if (playerNo != 0 || playerNo != 1) {
		return false;
	}
	Battlefield.whosTurn = playerNo;
	Battlefield.p0Pass = false;
	Battlefield.p1Pass = false;
	
	Battlefield.p0Wins = 0;
	Battlefield.p1Wins = 0;

	return true;
}

void BattleInfoManager::setBattlefield(const Field & f)
{
	Battlefield = f;
}

Field BattleInfoManager::getBattlefield()
{
	return Battlefield;
}

void BattleInfoManager::actToBattlefield(const Act & act)
{
	ActToField(act, this->Battlefield);
}

void BattleInfoManager::actCellToBattlefield(const ActCell & actCell)
{
	ActCellToField(actCell, this->Battlefield);
}

void ActToField(const Act & act, Field & field)
{
}

void ActCellToField(const ActCell & actCell, Field & field)
{
}
