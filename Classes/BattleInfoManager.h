#pragma once
#include "card.h"

enum ActType {NullMType, PASS, PLAY, LEADER, MOVE};
// {无效果， 放弃出牌， 打出卡牌， 使用领导牌， 卡牌被移动}
// Pass, Play, Leader and Change are active action from Player.
// Move is moving cards from place to place, which is passive action.
enum FieldLocation {NullLocation, HAND, DECK, GRAVE, REMOVED, COMBAT, RANGED, SEIGE, WEATHER};
enum CPosition {
	Hand1, Hand2, Grave1, Grave2, Deck1, Deck2,
	Weather1, Weather2, Combat1, Combat2, Ranged1, Ranged2,
	Siege1, Siege2, Void1, Void2
};


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
	std::vector<int> p0Siege;
	std::vector<int> p1Siege;

	std::vector<int> p0Weather;
	std::vector<int> p1Weather;
};

//struct CardWithPosition {
//	Card card;
//	CPosition position;
//};

struct ActCell {
	ActType actType;  
		// 见 ActType 的定义
	EffectType effectType;
		// 当前这个play是否连锁的effect
	int player;
		// 操作的玩家
	int attrID0;
		// 默认参数，即操作的主题卡牌
	int attrID1;
		// 比如医生选择的卡牌ID
	FieldLocation attrLoc0;
		// 位置参数，比如医生复活出来的agile所站的位置，或者
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
	static std::map<int, Card> CardMap;
	std::vector<Act> log;
public:

	BattleInfoManager();
	~BattleInfoManager();

	static BattleInfoManager* getInstance();
	void clear();  //手动析构

	bool init();
	bool initWithDecks(const std::vector<int> & deck0, const std::vector<int> & deck1);
	bool initWithFirstPlayer(const int & playerNo);
	
	void setBattlefield (const Field & f);
	Field & getBattlefield();
	void actToBattlefield(const Act & act);
	void actCellToBattlefield(const ActCell & actCell);
	
	bool isFrosting();
	bool isFogging();
	bool isRaining();
	bool isClearWeather();

	static Card & getCardWithID(int id);
	static int getPlayerFromCPosition(CPosition cPosi);
	static bool cPositionOnField(CPosition cPosi);
	static CardSet getCardSetFromLeaderID(int leaderID);
	void playCardFromHand(int player, int CID, CPosition targetZone); //todo
};