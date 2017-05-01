#include "card.h"


Card::Card(){}//defaul initalization

Card::Card(int id){
	this->reload(id);
}

void Card::reload(int id){
	std::ifstream cardsPool;
	cardsPool.open("..//Resources/CardPoolDatabase.json");  
	// In Card.cpp, direction system is not consist with Cocos. "..//" means upper dir to ($ProjectDir), which is ($SolutionDir)
	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(cardsPool, root, false)){
		return;
	}  
	Json::Value cards = root;
	Json::Value card = cards[id];
	this->cardID = card["cardID"].asInt();
	this->countLimit = card["CountLimit"].asInt();
	this->strength = card["Strength"].asInt();
	this->exEffect = card["exEffect"].asBool();
	this->description = card["Description"].asCString();
	this->name = card["Name"].asCString();
	this->picDir = card["Pic"].asCString();
//  to-do
//	std::string strCardSet = card["CardSet"].asCString();
//	std::string strCardType = card["CardType"].asCString();


}

int Card::getCountLimit(){
	return this->countLimit;
}

std::string Card::getPicDir(){
	// To be called in Cocos, the initial dir is ($ProjectDir)/Resources
	return "GwentCardsResources/Monsters/" + picDir;
	/*switch(cardSet){
		case NullCSet: 			
			break;
		case Northern:
			return "GwentCardsResources/Northern Realms/" + picDir;
			break;
		case Nilfgaarian:
			return "GwentCardsResources/Nilfgaardian Empire/" + picDir;
			break;
		case Monster:
			return "GwentCardsResources/Monsters/" + picDir;
			break;
		case Scoiateal:
			return "GwentCardsResources/Scoia'tael/" + picDir;
			break;
		case Neutral:
			return "GwentCardsResources/Neutrals/" + picDir;
			break;
	}*/

}

std::string Card::getCardName(){
	return name;
}

std::string Card::getCardDiscription(){
	return description;
}

CardType Card::getCardType(){
	return this->cardType;
}

/*return the card set*/

CardSet Card::getSet(){
	return this->cardSet;
}

UnitType Card::getCardSet(){
	return this->unitType;
}

int Card::getStrength()
{
	return this->strength;
}

UnitLevel Card::getUnitLevel(){
	return this->unitLevel;
}

SpellType Card::getSpellType(){
	return this->spellType;
}

WeatherType Card::getWeatherType(){
	return this->weatherType;
}

bool Card::existEx(){
	return this->exEffect;
}

void Card::changeStrengthTo(int CStrength){
	this->strength = CStrength;
}
