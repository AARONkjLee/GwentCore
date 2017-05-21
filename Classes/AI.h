#pragma once
#include "card.h"
#include "BattleInfoManager.h"
#include "CardEffectManager.h"
#include <vector>
#include <algorithm>

class AI {
private:
	int LeaderID;
	CardSet CollectionSet;
	std::vector<int> deck;
	static bool compareCardsByStrength(Card card1, Card card2);
	void sortCardsByStrength(std::vector<Card> &cardVector);
	std::vector<Card> searchEffect(std::vector<int> &range, EffectType effect);
	int scorchValue();
	void update(int current, int &max, int &result, int coefficient);
	int valueDifference();
	void changeTargetZone(Card card, CPosition &zone);
public:
	AI();
	~AI();
	static AI* getInstance();
	int selectStarter();
	int selectSwitchHand();
	std::vector<int> getDeck();
	void selectDeck(CardSet set);
	int selectCardToPlay(CPosition pos, CPosition &targetZone, int &nextID);
};