#include "AI.h"

AI::AI() {
}

AI::~AI() {
}



void AI::selectDeck(CardSet set) {
	LeaderID = 2;
	CollectionSet = Nilfgaardian;
	deck = {
		41,
		44, 44, 44,
		45,
		46,
		49,
		50,
		56, 56,
		57, 57,
		58, 58,
		61,
		62,
		65,
		66,
		68,
		73,
		74,
		76,
		84,
		86,
		89,
		91,
		93,
		94
	};
}

int AI::selectStarter() {
	return 1;
}

int AI::selectSwitchHand() {
	std::vector<int> currentHand = BattleInfoManager::getInstance()->getBattlefield().p1Hand;
	if (std::count(currentHand.begin(), currentHand.end(), 44) > 1) {
		return 44;
	}
	if (BattleInfoManager::getInstance()->getBattlefield().p0LeaderID >= 10 && std::count(currentHand.begin(), currentHand.end(), 57) > 0) {
		return 57;
	}
	return -1;
}

int AI::selectCardToPlay(CPosition pos) {
	//std::vector<int> currentArea = BattleInfoManager::getInstance()->getBattlefield().(pos == hand1 ? p1Hand : p1Tomb);
	//for (int i)
	return 0;
}