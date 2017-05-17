#pragma once

#include <json/json.h>
#include <fstream>
#include <string>


enum CardSet {NullCSet, Northern, Nilfgaarian, Monster, Scoiateal, Neutral};
enum Ability {
	Pick_Rain, //Pick a Torrential Rain card from your deck and play it instantly.
		// �����ԣ�û��ʱ�ܷ�շ��������쵼��ͬ��������
	Read_Hand_Card, //Look at 3 random cards from your opponent's hand.
		// �����ԣ����ÿɿ����ǿ������
	Cancel_Ability, //Cancel your opponent's Leader Ability.
		// ����ʱ������Ч��
	Rraw_From_Opponent, //Draw a card from your opponent's discard pile.
		// ̫��imba�������ԣ�����Ĺ��û���ɷ�շ���
	Restore_Unit, //Abilities that restore a unit to the battlefield restore a randomly-chosen unit. Affects both players.
		// �����ԣ����и���Ч�����������������Ч����
	Pick_Fog, //Pick an Impenetrable Fog card from your deck and play it instantly.
	Clear_Weathear, //Clear any weather effects (resulting from Biting Frost, Torrential Rain or Impenetrable Fog cards) in play.
		// �����ԣ��ɷ�շ���
	Seige_Horn, //Doubles the strength of all your Siege units (unless a Commander's Horn is also present on that row).
		// �����ԣ����кŽ�ʱ�ɷ�շ���
	Seige_Scorch, //Destroy your enemy's strongest Siege unit(s) if the combined strength of all his or her Siege units is 10 or more.
		// �����ԣ��ɷ�շ���
	Range_Scorch, //Destroy your enemy's strongest Ranged Combat unit(s) if the combined strength of all his or her Ranged Combat units is 10 or more.
	Pick_Frost, //Pick a Biting Frost card from your deck and play it instantly.
	Draw_11th, //Draw an extra card at the beginning of the battle
		// �����ԣ�����ǰ���ƺ�
	Range_Horn, //Doubles the strength of all your Ranged Combat units (unless a Commander's Horn is also present on that row).
	Close_Scorch, //Destroy your enemy's Close Combat unit(s) if the combined strength of all his or her Close Combat units is 10 or more.
	Move_Aglie, //Move agile unites to whichever valid row maximizes their strength (don't move units already in optimal row).
		// �����ԣ��շ���
	Pick_Weather, //Pick any weather card from your deck and play it instantly.
	Close_Horn, //Double the strength of all your Close Combat units (unless a Commander's Horn is also present on that row).
	Destroy2_Draw1, //Discard 2 cards and draw 1 card of your choice from your deck.
		// ���ԣ�����û��ʱ��
	Restore_Unit_ToHand, //Restore a card from your discard pile to your hand.
		// �����ԣ��Լ�Ĺ��û���ɷ�շ���
	Double_Spies //Doubles strength of all spies.
		// �����ԣ�����Ч��������Ч�����ɷ�ͺŽǵ��ӣ�����˳��
};

class LeaderCard {
private:
	int cardID;
	std::string picDir;  // For leaderCards, their picDir include the full direction rather than only filename.
						 // Cards have only filename.
	std::string name;
	std::string description;
	CardSet cardSet;
	Ability ability;

public:
	LeaderCard();
	LeaderCard(int id);
	~LeaderCard() {}

/*load the card using the id*/
	void reload(int id);


/*return the direction of the picture*/
	std::string getPicDir();
/*return the card name*/
	std::string getName();
/*return the card type*/
	std::string getDescription();
/*return the card set*/
	CardSet getSet();
/*return the Ability*/
	Ability getAbility();
};

