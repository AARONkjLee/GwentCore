#pragma once

#include "BattleInfoManager.h"
#include "SinglePlayScene.h"
#include <algorithm>


class MatchDirector {
private:
	// All GUI methods called in this class should be created in SinglePlayScene
	cocos2d::Layer* GUI;
	int Player;
	Field* field;
	void updateField();
	

	//to-do define the AI class 
	//AI ai;
public:
	// This two vectors are used for passing deck from PlayPreparationScene ot SinglePlayScene
	std::vector<int> initDeck0;
	std::vector<int> initDeck1;

	MatchDirector();
	~MatchDirector();

	static MatchDirector* getInstance();
	void setGUILayer(cocos2d::Layer* gui);
	void MainMatchLoop();

	void init();
	void BeforeGame();
	bool GameOver();
	void Turn(int Player);
	void AfterGame();
	void StarterModel();
	CardSet getCardSetOfPlayer(int player);
	void SwitchHands();
	void P0Turn();
	void P1Turn();
};