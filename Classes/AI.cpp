#include "AI.h"

AI::AI() {
}

AI::~AI() {
}

bool AI::compareCardsByStrength(Card card1, Card card2) {
	return card1.getStrength() < card2.getStrength();
}

void AI::sortCardsByStrength(std::vector<Card> &cardVector) {
	std::sort(cardVector.begin(), cardVector.end(), compareCardsByStrength);
}

std::vector<Card> AI::searchEffect(std::vector<int> &range, EffectType effect) {
	Card currentCard;
	std::vector<Card> result;
	for (int currentCardID : range) {
		currentCard = BattleInfoManager::getCardWithID(currentCardID);
		if (std::count(currentCard.getEffects().begin(), currentCard.getEffects().end(), effect) > 0) {
			result.push_back(currentCard);
		}
	}
	sortCardsByStrength(result);
	return result;
}

int AI::scorchValue() {
	int maxStrength = 0;
	int currentStrength;
	int value = 0;
	for (int id : BattleInfoManager::getInstance()->getBattlefield().p0Combat) {
		currentStrength = CardEffectManager::getInstance()->getCardCurrentStrengthWithPositon(id, Combat1);
		update(currentStrength, maxStrength, value, 1);
	}
	for (int id : BattleInfoManager::getInstance()->getBattlefield().p0Ranged) {
		currentStrength = CardEffectManager::getInstance()->getCardCurrentStrengthWithPositon(id, Ranged1);
		update(currentStrength, maxStrength, value, 1);
	}
	for (int id : BattleInfoManager::getInstance()->getBattlefield().p0Siege) {
		currentStrength = CardEffectManager::getInstance()->getCardCurrentStrengthWithPositon(id, Siege1);
		update(currentStrength, maxStrength, value, 1);
	}
	for (int id : BattleInfoManager::getInstance()->getBattlefield().p1Combat) {
		currentStrength = CardEffectManager::getInstance()->getCardCurrentStrengthWithPositon(id, Combat2);
		update(currentStrength, maxStrength, value, -1);
	}
	for (int id : BattleInfoManager::getInstance()->getBattlefield().p1Ranged) {
		currentStrength = CardEffectManager::getInstance()->getCardCurrentStrengthWithPositon(id, Ranged2);
		update(currentStrength, maxStrength, value, -1);
	}
	for (int id : BattleInfoManager::getInstance()->getBattlefield().p1Siege) {
		currentStrength = CardEffectManager::getInstance()->getCardCurrentStrengthWithPositon(id, Siege2);
		update(currentStrength, maxStrength, value, -1);
	}
	return value;
}

void AI::update(int current, int &max, int &result, int coefficient) {
	if (current > max) {
		max = current;
		result = max * coefficient;
	}
	else {
		if (current == max) {
			result += max * coefficient;
		}
	}
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
	/*if (BattleInfoManager::getInstance()->getBattlefield().p0LeaderID >= 10 && std::count(currentHand.begin(), currentHand.end(), 57) > 0) {
		return 57;
	}*/
	return -1;
}

int AI::selectCardToPlay(CPosition pos) {
	std::vector<int> currentArea;
	std::vector<Card> targetCards;
	if (pos == Hand1) {
		currentArea = BattleInfoManager::getInstance()->getBattlefield().p1Hand;
	}
	else {
		currentArea = BattleInfoManager::getInstance()->getBattlefield().p1Grave;
	}
	targetCards = searchEffect(currentArea, Spye);
	if (targetCards.size()) {
		return targetCards[0].getID();
	} //最优先：直接打出的间谍
	targetCards = searchEffect(BattleInfoManager::getInstance()->getBattlefield().p1Grave, Spye);
	if (targetCards.size()) {
		targetCards = searchEffect(currentArea, Medice);
		if (targetCards.size()) {
			return targetCards[0].getID();
		}
	} //次优先：能复活间谍的医生
	return 0;
}