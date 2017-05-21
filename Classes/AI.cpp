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

int AI::valueDifference() {
	Field field = BattleInfoManager::getInstance()->getBattlefield();
	int p0Total = 0;
	int p1Total = 0;
	for (int i : field.p0Combat) {
		p0Total += CardEffectManager::getInstance()->getCardCurrentStrengthWithPositon(i, Combat1);
	}
	for (int i : field.p1Combat) {
		p1Total += CardEffectManager::getInstance()->getCardCurrentStrengthWithPositon(i, Combat2);
	}
	for (int i : field.p0Ranged) {
		p0Total += CardEffectManager::getInstance()->getCardCurrentStrengthWithPositon(i, Ranged1);
	}
	for (int i : field.p1Ranged) {
		p0Total += CardEffectManager::getInstance()->getCardCurrentStrengthWithPositon(i, Ranged2);
	}
	for (int i : field.p0Siege) {
		p0Total += CardEffectManager::getInstance()->getCardCurrentStrengthWithPositon(i, Siege1);
	}
	for (int i : field.p1Siege) {
		p0Total += CardEffectManager::getInstance()->getCardCurrentStrengthWithPositon(i, Siege2);
	}
	return p1Total - p0Total;
}

void changeTargetZone(Card card, CPosition &zone) {
	if (card.getUnitType() == CloseCombat) {
		zone = Combat2;
	}
	else if (card.getUnitType() == RangedCombat) {
			zone = Ranged2;
	} 
	else {
		zone = Siege2;
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
		50,
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
		87,
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
	if (std::count(currentHand.begin(), currentHand.end(), 44) > 0) {
		return 44;
	}
	/*if (BattleInfoManager::getInstance()->getBattlefield().p0LeaderID >= 10 && std::count(currentHand.begin(), currentHand.end(), 57) > 0) {
		return 57;
	}*/
	return -1;
}

int AI::selectCardToPlay(CPosition pos, CPosition &targetZone, int &nextID) {
	std::vector<int> currentArea;
	std::vector<Card> targetCards;
	if (pos == Hand2) {
		currentArea = BattleInfoManager::getInstance()->getBattlefield().p1Hand;
	}
	else {
		currentArea = BattleInfoManager::getInstance()->getBattlefield().p1Grave;
	}
	if (currentArea.size()==0) {
		return -1;
	}
	targetCards = searchEffect(currentArea, Spye);
	if (targetCards.size()) {
		changeTargetZone(targetCards[0], targetZone);
		return targetCards[0].getID();
	} //最优先：直接打出的间谍
	targetCards = searchEffect(BattleInfoManager::getInstance()->getBattlefield().p1Grave, Spye);
	if (targetCards.size()) {
		targetCards = searchEffect(currentArea, Medice);
		if (targetCards.size()) {
			changeTargetZone(targetCards[0], targetZone);
			return targetCards[0].getID();
		}
	} //次优先：能复活间谍的医生
	if (valueDifference() > 0 && BattleInfoManager::getInstance()->getBattlefield().p0Pass) {
		return -1;
	}
	if (valueDifference() < -15 && BattleInfoManager::getInstance()->getBattlefield().p0Wins < 1) {
		return -1;
	}
	std::vector<Card> finalVector;
	targetCards = searchEffect(currentArea, Mustere);
	finalVector.insert(finalVector.end(), targetCards.begin(), targetCards.end());
	targetCards = searchEffect(currentArea, NullEType);
	finalVector.insert(finalVector.end(), targetCards.begin(), targetCards.end());
	targetCards = searchEffect(currentArea, TightBonde);
	finalVector.insert(finalVector.end(), targetCards.begin(), targetCards.end());
	if (BattleInfoManager::getInstance()->getBattlefield().p1Grave.size()) {
		targetCards = searchEffect(currentArea, Medice);
		finalVector.insert(finalVector.end(), targetCards.begin(), targetCards.end());
	}
	if (pos == Hand2) {
		if (searchEffect(currentArea, SpellScorche).size() && scorchValue() > finalVector[0].getStrength()) {
			return 58;
		}
		changeTargetZone(finalVector[0], targetZone);
		return finalVector[0].getID();
	}
	changeTargetZone(finalVector[finalVector.size() - 1], targetZone);
	return finalVector[finalVector.size() - 1].getID();
}