#include "BattleInfoManager.h"

static BattleInfoManager* s_SharedBattleInfo = nullptr;

BattleInfoManager::BattleInfoManager()
{
}

BattleInfoManager::~BattleInfoManager()
{
	//delete s_SharedBattleInfo;
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

void BattleInfoManager::clear()
{
	/*for (std::map<int, Card*>::iterator ptcp = CardMap.begin(); ptcp != CardMap.end(); ++ptcp) {
		delete ptcp*;
	}*/
}

bool BattleInfoManager::init()
{
	return true;
}

bool BattleInfoManager::initWithDecks(const std::vector<int>& deck0, const std::vector<int>& deck1)
{
	if (deck0.empty() || deck1.empty()) {
		return false;
	}
	//deck[0] is LeaderID and then cardIDs
	Battlefield.p0LeaderID = deck0[0];
	Battlefield.p0LeaderAviable = true;
	Battlefield.p1LeaderID = deck1[0];
	Battlefield.p1LeaderAviable = true;
	Battlefield.p0Deck = deck0;
	Battlefield.p0Deck.erase(Battlefield.p0Deck.begin());
	Battlefield.p1Deck = deck1;
	Battlefield.p1Deck.erase(Battlefield.p1Deck.begin());

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

Field & BattleInfoManager::getBattlefield()
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


const int FROST_CID = 52;
bool BattleInfoManager::isFrosting()
{
	for (int cid : Battlefield.p0Weather) {
		if (cid == FROST_CID) {
			return true;
		}
	}
	for (int cid : Battlefield.p1Weather) {
		if (cid == FROST_CID) {
			return true;
		}
	}
	return false;
}


const int FOG_CID = 54;
bool BattleInfoManager::isFogging()
{
	for (int cid : Battlefield.p0Weather) {
		if (cid == FOG_CID) {
			return true;
		}
	}
	for (int cid : Battlefield.p1Weather) {
		if (cid == FOG_CID) {
			return true;
		}
	}
	return false;
}


const int RAIN_CID = 55;
bool BattleInfoManager::isRaining()
{
	for (int cid : Battlefield.p0Weather) {
		if (cid == RAIN_CID) {
			return true;
		}
	}
	for (int cid : Battlefield.p1Weather) {
		if (cid == RAIN_CID) {
			return true;
		}
	}
	return false;
}

bool BattleInfoManager::isClearWeather()
{
	return !(isFrosting() || isFogging() || isRaining());
}

Card & BattleInfoManager::getCardWithID(int id)
{
	if (CardMap.find(id) != CardMap.end()) {
		return CardMap[id];
	}
	else {
		Card c(id);
		CardMap[id] = c;
		return CardMap[id];
	}
}

int BattleInfoManager::getPlayerFromCPosition(CPosition cPosi)
{
	switch (cPosi)
	{
	case Hand1:
	case Grave1:
	case Deck1:
	case Weather1:
	case Combat1:
	case Ranged1:
	case Seige1:
	case Void1:
		return 0;
		break;
	case Hand2:
	case Grave2:
	case Deck2:
	case Weather2:
	case Combat2:
	case Ranged2:
	case Seige2:
	case Void2:
		return 1;
		break;
	default:
		break;
	}
	return 0;
}

bool BattleInfoManager::cPositionOnField(CPosition cPosi)
{
	switch (cPosi)
	{
	case Combat1:
	case Ranged1:
	case Seige1:
	case Combat2:
	case Ranged2:
	case Seige2:
		return true;
		break;
	default:
		return false;
		break;
	}
	return false;
}

void ActToField(const Act & act, Field & field)
{
}

void ActCellToField(const ActCell & actCell, Field & field)
{
}
