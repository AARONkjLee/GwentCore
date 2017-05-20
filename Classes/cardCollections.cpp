#include "cardCollections.h" 
#include <json\json.h>

CardCollection::CardCollection(CardSet set){
	this->initWithSet(set);
}

void CardCollection::initWithSet(CardSet set){
	std::ifstream cardsPool;
	switch (set) {
	case NullCSet:
		break;
	case Northern:
		cardsPool.open("..//Resources/cardCollection/Northern.json");
		// In Card.cpp, direction system is not consist with Cocos. "..//" means upper dir to ($ProjectDir), which is ($SolutionDir)
		break;
	case Nilfgaarian:
		cardsPool.open("..//Resources/cardCollection/Nilfgaarian.json");
		break;
	case Monster:
		cardsPool.open("..//Resources/cardCollection/Monster.json");
		break;
	case Scoiateal:
		cardsPool.open("..//Resources/cardCollection/Scoiateal.json");
		break;
	case Neutral:
		cardsPool.open("..//Resources/cardCollection/Neutral.json");
		break;
	}	
	Json::Reader reader;
	Json::Value J_set;
	if (!reader.parse(cardsPool, J_set, false)) {
		return;
	}
	this->LeaderID = J_set["leader"].asInt();
	Json::Value J_deck;
	J_deck = J_set["deck"];
	for (int i = 0; i < J_deck.size(); i++) {
		this->deck.push_back(J_deck[i].asInt());
	}
	cardsPool.close();
}

void CardCollection::setLeader(LeaderCard leader)
{
}
