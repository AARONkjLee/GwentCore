#pragma once
#include "card.h"
#include "BattleInfoManager.h"
#include <vector>

class AI {
private:
	int LeaderID;
	CardSet CollectionSet;
	std::vector<int> deck;
	int calculateHandValue(int player);
public:
	AI();
	~AI();
	int selectStarter();
	int selectSwitchHand();
	void selectDeck(CardSet set);
	int selectCardToPlay(CPosition pos);
};