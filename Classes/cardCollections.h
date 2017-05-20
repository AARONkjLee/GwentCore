#ifndef __cardCollections_H__ 
#define __cardCollections_H__ 


#include "card.h"
#include "leaderCard.h"
#include <vector>

class CardCollection {
	private:
		int LeaderID ;
		CardSet CollectionSet;
		std::vector<int> deck;
	public:
		CardCollection();
		CardCollection(CardSet set);
		~CardCollection() {}
		void initWithSet(CardSet set);
		void setLeader(LeaderCard leader);
//it is a boollen type because that if it is a illegal 
//card for deck it will returen false ratherr than add 
//it into dec
		bool addCard(Card card);
		void dumpCollection();
		int getLeader();
		std::vector<int> getDeck();

};

 
#endif __cardCollections_H__ 
