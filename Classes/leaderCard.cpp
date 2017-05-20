#include "leaderCard.h"

Json::Value leaderCards;

LeaderCard::LeaderCard(){}//defaul initalization

LeaderCard::LeaderCard(int id){
	this->reload(id);
}

void LeaderCard::reload(int id) {
	if (!leaderCards) {
		std::ifstream cardsPool;
		cardsPool.open("..//Resources/LeaderCardPoolDatabase.json");
		// In Card.cpp, direction system is not consist with Cocos. "..//" means upper dir to ($ProjectDir), which is ($SolutionDir)
		Json::Reader reader;		
		if (!reader.parse(cardsPool, leaderCards, false)) {
			return;
		}
		cardsPool.close();
	}
	Json::Value card = leaderCards[id];
	this->cardID = card["cardID"].asInt();
	this->description = card["Description"].asCString();
	this->name = card["Name"].asCString();
	this->picDir = card["Pic"].asCString();
	/*To do: Translate string to enum*/
	// card type
	std::string strAbility = card["Ability"].asCString();
	if (strAbility == " Pick_Rain") {
		this->ability = Pick_Rain;
	}
	else if (strAbility == "Read_Hand_Card") {
		this->ability = Read_Hand_Card;
	}
	else if (strAbility == "Cancel_Ability") {
		this->ability = Cancel_Ability;
	}
	else if (strAbility == "Rraw_From_Opponent") {
		this->ability = Rraw_From_Opponent;
	}
	else if (strAbility == "Restore_Unit") {
		this->ability = Restore_Unit;
	}
	else if (strAbility == "Pick_Fog") {
		this->ability = Pick_Fog;
	}
	else if (strAbility == "Clear_Weathear") {
		this->ability = Clear_Weathear;
	}
	else if (strAbility == "Seige_Horn") {
		this->ability = Seige_Horn;
	}
	else if (strAbility == "Seige_Scorch") {
		this->ability = Seige_Scorch;
	}
	else if (strAbility == "Range_Scorch") {
		this->ability = Range_Scorch;
	}
	else if (strAbility == "Pick_Frost") {
		this->ability = Pick_Frost;
	}
	else if (strAbility == "Draw_11th") {
		this->ability = Draw_11th;
	}
	else if (strAbility == "Range_Horn") {
		this->ability = Range_Horn;
	}
	else if (strAbility == "Close_Scorch") {
		this->ability = Close_Scorch;
	}
	else if (strAbility == "Move_Aglie") {
		this->ability = Move_Aglie;
	}
	else if (strAbility == "Pick_Weather") {
		this->ability = Pick_Weather;
	}
	else if (strAbility == "Close_Horn") {
		this->ability = Close_Horn;
	}
	else if (strAbility == "Destroy2_Draw1") {
		this->ability = Destroy2_Draw1;
	}
	else if (strAbility == "Restore_Unit_ToHand") {
		this->ability = Restore_Unit_ToHand;
	}
	else if (strAbility == "Double_Spies") {
		this->ability = Double_Spies;
	}


}



std::string LeaderCard::getPicDir(){
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
	}

}

std::string LeaderCard::getName(){
	return this->name;
}

std::string LeaderCard::getDescription(){
	return this->description;
}


/*return the card set*/

CardSet LeaderCard::getSet(){
	return this->cardSet;
}

Ability LeaderCard::getAbility()
{
	return this->ability;
}

int LeaderCard::getID()
{
	return cardID;
}
