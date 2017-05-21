#include "cardCollections.h" 
#include <json\json.h>



CardCollection::CardCollection()
{
}

CardCollection::CardCollection(CardSet set){
	this->initWithSet(set);
}

void CardCollection::initWithSet(CardSet set){
	std::ifstream cardsCollectionPool;
	this->CollectionSet = set;
	switch (set) {
	case NullCSet:
		return;
	case Northern:
		cardsCollectionPool.open("..//Resources/cardCollection/Northern.json");
		// In Card.cpp, direction system is not consist with Cocos. "..//" means upper dir to ($ProjectDir), which is ($SolutionDir)
		break;
	case Nilfgaardian:
		cardsCollectionPool.open("..//Resources/cardCollection/Nilfgaardian.json");
		break;
	case Monster:
		cardsCollectionPool.open("..//Resources/cardCollection/Monster.json");
		break;
	case Scoiateal:
		cardsCollectionPool.open("..//Resources/cardCollection/Scoiateal.json");
		break;
	}	
	Json::Reader reader;
	Json::Value J_set;
	if (!reader.parse(cardsCollectionPool, J_set, false)) {
		return;
	}
	this->LeaderID = J_set["leader"].asInt();
	Json::Value J_deck;
	J_deck = J_set["deck"];
	for (int i = 0; i < J_deck.size(); i++) {
		this->deck.push_back(J_deck[i].asInt());
	}
	cardsCollectionPool.close();
}

void CardCollection::setLeader(LeaderCard leader){
	this->LeaderID = leader.getID();
}

void CardCollection::setLeadId(int leaderid) {
	this->LeaderID = leaderid;
}

bool CardCollection::addCard(Card card){
	int id = card.getID();
	int count = 0;
	if (card.getSet() == this->CollectionSet) {
		return false;
	}
	for (int i = 0; i < deck.size(); i++) {
		if (deck[i] == id) {
			count++;
			if (count == card.getCountLimit()) {
				return false;
			}
		}
	}
 	this -> deck.push_back(id);
	return false;
}

void CardCollection::dumpCollection(){
	std::ofstream cardsCollectionPool;
	switch (CollectionSet) {
	case NullCSet:
		return;
	case Northern:
//		cardsCollectionPool.open("..//Resources/cardCollection/Northern.json", std::ios::trunc);
		cardsCollectionPool.open("..//Resources/CardPoolDatabase.json", std::ios::trunc);
		// In Card.cpp, direction system is not consist with Cocos. "..//" means upper dir to ($ProjectDir), which is ($SolutionDir)
		break;
	case Nilfgaardian:
		cardsCollectionPool.open("..//Resources/cardCollection/Nilfgaardian.json", std::ios::trunc);
		break;
	case Monster:
		cardsCollectionPool.open("..//Resources/cardCollection/Monster.json", std::ios::trunc);
		break;
	case Scoiateal:
		cardsCollectionPool.open("..//Resources/cardCollection/Scoiateal.json", std::ios::trunc);
		break;
	case Neutral:
		cardsCollectionPool.open("..//Resources/cardCollection/Neutral.json", std::ios::trunc);
		break;
	}
	Json::StyledWriter writer;
	Json::Value J_set;
	Json::Value J_deck;
	J_set["leader"] = this->LeaderID;
	for (int i = 0; i < deck.size(); i++) {
		J_deck.append(deck[i]);
	}
	J_set["deck"] = J_deck;
	std::string S_set = writer.write(J_set);
	cardsCollectionPool << S_set;
	cardsCollectionPool.close();
}

CardSet CardCollection::getSet()
{
	return this->CollectionSet;
}

int CardCollection::getLeader()
{
	return this->LeaderID;
}


std::vector<int> CardCollection::getDeck()
{
	return this->deck;
}

