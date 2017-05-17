#pragma once
#include "card.h"

enum ActType {NullMType, PASS, PLAY, LEADER, MOVE};
// {无效果， 放弃出牌， 打出卡牌， 使用领导牌， 卡牌被移动}
// Pass, Play, Leader and Change are active action from Player.
// Move is moving cards from place to place, which is passive action.
enum FieldLocation {NullLocation, HAND, DECK, GRAVE, REMOVED, COMBAT, RANGED, SEIGE, WEATHER};



struct Field {
	int whosTurn; // 0 or 1
	bool p0Pass;
	bool p1Pass;
	
	int p0Wins;
	int p1Wins;

	int p0LeaderID;
	int p1LeaderID;
	bool p0LeaderAviable;
	bool p1LeaderAviable;
	
	std::vector<int> p0Hand;
	std::vector<int> p1Hand;
	std::vector<int> p0Deck;
	std::vector<int> p1Deck;
	std::vector<int> p0Grave;
	std::vector<int> p1Grave;

	// Won't be used in curret stage 2017.5.11
	std::vector<int> p0Out;
	std::vector<int> p1Out;

	std::vector<int> p0Combat;
	std::vector<int> p1Combat;
	std::vector<int> p0Ranged;
	std::vector<int> p1Ranged;
	std::vector<int> p0Seige;
	std::vector<int> p1Seige;

	std::vector<int> p0Weather;
	std::vector<int> p1Weather;
};


struct ActCell {
	ActType actType;
	EffectType effectType;
	int player;
	int attrID0;
	int attrID1;
	FieldLocation attrLoc0;
	FieldLocation attrLoc1;
};


struct Act {
	ActCell promotor;
	bool hasChain;
	std::vector<ActCell> chainActCells;
};

void ActToField(const Act & act, Field & field);
void ActCellToField(const ActCell & actCell, Field & field);


class BattleInfoManager {
private:
	Field Battlefield;
	std::vector<Act> log;
public:

	BattleInfoManager();
	~BattleInfoManager();

	static BattleInfoManager* getInstance();

	bool init();
	bool initWithDecks(const std::vector<int> & deck0, const std::vector<int> & deck1);
	bool initWithFirstPlayer(const int & playerNo);
	
	void setBattlefield (const Field & f);
	Field & getBattlefield();
	void actToBattlefield(const Act & act);
	void actCellToBattlefield(const ActCell & actCell);
};