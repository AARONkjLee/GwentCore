#pragma once

#include "BattleInfoManager.h"
#include "SinglePlayScene.h"
#include "CardEffectManager.h"
#include "AI.h"
#include <algorithm>


class MatchDirector {
private:
	// All GUI methods called in this class should be created in SinglePlayScene
	cocos2d::Layer* GUI;
	//int fieldwhosturn;
	Field* field;
	void updateField();
	

	//to-do define the AI class 
	AI ai;
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
	void InitMatch();
	void P0Turn();
	void P1Turn();
	void IndicatingWinning();
	void roundResult(int winner);
	void matchResult();

};