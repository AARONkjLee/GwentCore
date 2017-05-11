#include "card.h"


Card::Card(){}//defaul initalization

Card::Card(int id){
	this->reload(id);
}

void Card::reload(int id) {
	std::ifstream cardsPool;
	cardsPool.open("..//Resources/CardPoolDatabase.json");
	// In Card.cpp, direction system is not consist with Cocos. "..//" means upper dir to ($ProjectDir), which is ($SolutionDir)
	Json::Reader reader;
	Json::Value cards;
	if (!reader.parse(cardsPool, cards, false)) {
		return;
	}
	cardsPool.close();
	Json::Value card = cards[id];
	Json::Value jsonEffects = card["EffectType"];
	this->cardID = card["cardID"].asInt();
	this->countLimit = card["CountLimit"].asInt();
	this->strength = card["Strength"].asInt();
	this->exEffect = card["exEffect"].asBool();
	this->description = card["Description"].asCString();
	this->name = card["Name"].asCString();
	this->picDir = card["Pic"].asCString();
	this->strengthStr = card["Strength"].asString();
	/*To do: Translate string to enum*/
	// card type
	std::string strCardType = card["CardType"].asCString();
	if (strCardType == " NullCType") {
		this->cardType = NullCType;
	}
	else if (strCardType == "Unit") {
		this->cardType = Unit;
	}
	else if (strCardType == "Spell") {
		this->cardType = Spell;
	}
	std::string strCardSet = card["CardSet"].asCString();
	if (strCardSet == "NullCSet") {
		this->cardSet = NullCSet;
	}
	else if (strCardSet == "Northern") {
		this->cardSet = Northern;
	}
	else if (strCardSet == "Nilfgaarian") {
		this->cardSet = Nilfgaarian;
	}
	else if (strCardSet == "Monster") {
		this->cardSet = Monster;
	}
	else if (strCardSet == "Scoiateal") {
		this->cardSet = Scoiateal;
	}
	else if (strCardSet == "Neutral") {
		this->cardSet = Neutral;
	}
	
	std::string strUnitType = card["UnitType"].asCString();
	if (strUnitType == "NullUType") {
		this->unitType = NullUType;
	}
	else if (strUnitType == "CloseCombat") {
		this->unitType = CloseCombat;
	}
	else if (strUnitType == "RangedCombat") {
		this->unitType = RangedCombat;
	}
	else if (strUnitType == "Siege") {
		this->unitType = Siege;
	}
	else if (strUnitType == "CloseRangedCombat") {
		this->unitType = CloseRangedCombat;
	}
	std::string strUnitLevel = card["UnitLevel"].asCString();
	if (strUnitLevel == " NullULevel") {
		this->unitLevel = NullULevel;
	}
	else if (strUnitLevel == "Ordinary") {
		this->unitLevel = Ordinary;
	}
	else if (strUnitLevel == "Hero") {
		this->unitLevel = Hero;
	}
	std::string strSpellType = card["SpellType"].asCString();
	if (strSpellType == "NullSType") {
		this->spellType = NullSType;
	}
	else if (strSpellType == "Weather") {
		this->spellType = Weather;
	}
	else if (strSpellType == "Horn") {
		this->spellType = Horn;
	}
	else if (strSpellType == "Decoy") {
		this->spellType = Decoy;
	}
	else if (strSpellType == "Scorch") {
		this->spellType = Scorch;
	}
	std::string strWeatherType = card["WeatherType"].asCString();
	if (strWeatherType == "NullWType") {
		this->weatherType = NullWType;
	}
	else if (strWeatherType == "Bitingfroest") {
		this->weatherType = Bitingfroest;
	}
	else if (strWeatherType == "Fog") {
		this->weatherType = Fog;
	}
	else if (strWeatherType == "Rain") {
		this->weatherType = Rain;
	}
	else if (strWeatherType == "ClearWeather") {
		this->weatherType = ClearWeather;
	}
	for (int i = 0; i < jsonEffects.size(); i++) {
		EffectType effectType;
		std::string strEffectType = jsonEffects[i].asCString();
		if (strEffectType == "NullEType") {
			effectType = NullEType;
		}
		else if (strEffectType == "Agile") {
			effectType = Agile;
		}
		else if (strEffectType == "Spye") {
			effectType = Spye;
		}
		else if (strEffectType == "TightBonde") {
			effectType = TightBonde;
		}
		else if (strEffectType == "Decoye") {
			effectType = Decoye;
		}
		else if (strEffectType == "Medice") {
			effectType = Medice;
		}
		else if (strEffectType == "SpellHorne") {
			effectType = SpellHorne;
		}
		else if (strEffectType == "UnitHorne") {
			effectType = UnitHorne;
		}
		else if (strEffectType == "SpellScorche") {
			effectType = SpellScorche;
		}
		else if (strEffectType == "UnitScorche") {
			effectType = UnitScorche;
		}
		else if (strEffectType == "Mustere") {
			effectType = Mustere;
		}
		else if (strEffectType == "MoraleBooste") {
			effectType = MoraleBooste;
		}
		else if (strEffectType == "BitingFroste") {
			effectType = BitingFroste;
		}
		else if (strEffectType == "Foge") {
			effectType = Foge;
		}
		else if (strEffectType == "Raine") {
			effectType = Raine;
		}
		else if (strEffectType == "ClearWeathere") {
			effectType = ClearWeathere;
		}
		this->effects.push_back(effectType);
	}



}

int Card::getCountLimit(){
	return this->countLimit;
}

std::string Card::getPicDir(){
	// To be called in Cocos, the initial dir is ($ProjectDir)/Resources
	//return "GwentCardsResources/Monsters/" + picDir;
	switch(cardSet){
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
			if (this->cardType == Spell) {
				return "GwentCardsResources/Neutrals/" + picDir;
			}
			else if (this->cardType == Unit) {
				return "GwentCardsResources/Neutral Units/" + picDir;
			}
			break;
	}

}

std::string Card::getCardName(){
	return this->name;
}

std::string Card::getCardDiscription(){
	return this->description;
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

std::string Card::getStrengthStr()
{
	return this->strengthStr;
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
