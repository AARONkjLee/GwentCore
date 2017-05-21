/* This file is to define all template card effect
// These effects are all for "EffectType"

// A effect function should have a input of Field
// and a input of a Act

 enum EffectType {
	NullEType, 
	Agile, 
	Spye, 
	TightBonde, 
	Decoye, 
	Medice, 
	SpellHorne, 
	UnitHorne, 
	SpellScorche, 
	UnitScorche, 
	Mustere, 
	MoraleBooste, 
	BitingFroste, 
	Foge, 
	Raine, 
	ClearWeathere 
};

//enum setEffect {
//	NullSetEffect,
//	NorthernE,
//	NilfgaarianE,
//	MonsterE,
//	ScoiatealE,
//	NeutralE
//};*/

#pragma once
#include "MatchDirector.h"

class CardEffectManager {
private:
	Field* field;
	void updateField();

public:
	CardEffectManager();
	~CardEffectManager();
	static CardEffectManager* getInstance();

	int getCardCurrentStrengthWithPositon(int cid, CPosition cPosi);
	static void checkPrompt(int Player, int promptCid, std::vector<CPosition> &leaglPlayTargetZones, std::vector<int> &leaglPlayTargetCIDs);
};