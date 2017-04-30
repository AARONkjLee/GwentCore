#include "card.h"


Card::Card()
{

}

Card::Card(int id){

}

void Card::reload(int id)
{

}

int Card::getCountLimit(){
	return this->countLimit;
}

std::string Card::getPicDir(){
	switch(cardSet){
		case NullCSet: 			
			break;
		case Northern:
			return "Northern Realms" + picDir;
			break;
		case Nilfgaarian:
			return "Nilfgaardian Empire" + picDir;
			break;
		case Monster:
			return "Monsters" + picDir;
			break;
		case Scoiateal:
			return "Scoia'tael" + picDir;
			break;
		case Neutral:
			return "Neutrals" + picDir;
			break;
	}

}

std::string Card::getCardName(){
	return name;
}

std::string Card::getCardDiscription(){
	return discription;
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
