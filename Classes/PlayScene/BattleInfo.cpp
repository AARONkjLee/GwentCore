#include "BattleInfo.h"

static BattleInfo* s_SharedBattleInfo = nullptr;

BattleInfo::BattleInfo()
{
}

BattleInfo::~BattleInfo()
{
}

BattleInfo * BattleInfo::getInstance()
{
	if (!s_SharedBattleInfo)
	{
		s_SharedBattleInfo = new (std::nothrow) BattleInfo;
		s_SharedBattleInfo->init();
	}

	return s_SharedBattleInfo;
}

bool BattleInfo::init()
{
	return true;
}

bool BattleInfo::initWithDecks(const std::vector<int>& deck0, const std::vector<int>& deck1)
{
	if (!deck0.size() || !deck1.size()) {
		return false;
	}
	//deck[0] is LeaderID and then cardIDs
	field.p0LeaderID = deck0[0];
	field.p0LeaderAviable = true;
	field.p1LeaderID = deck1[0];
	field.p1LeaderAviable = true;
	field.p0Deck = std::vector<int> (-1, deck0.size() - 1);
	field.p1Deck = std::vector<int> (-1, deck1.size() - 1);

	for (int i = 1; i < deck0.size(); i++) {
		field.p0Deck[i-1] = (deck0[i], 0);
	}
	for (int i = 1; i < deck1.size(); i++) {
		field.p1Deck[i - 1] = (deck1[i], 0);
	}

	return true;
}

bool BattleInfo::initWithFirstPlayer(const int & playerNo)
{
	if (playerNo != 0 || playerNo != 1) {
		return false;
	}
	field.whosTurn = playerNo;
	field.p0Pass = false;
	field.p1Pass = false;
	
	field.p0Wins = 0;
	field.p1Wins = 0;

	return true;
}

