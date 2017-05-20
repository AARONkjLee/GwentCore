#ifndef __cardCollections_H__ 
#define __cardCollections_H__ 


#include "card.h"
#include "leaderCard.h"
#include <vector>

class CardCollection {
	private:
		int LeaderID ;
		std::vector<int> deck;
	public:
		CardCollection(CardSet set);
		~CardCollection() {}
		void initWithSet(CardSet set);
		void setLeader(LeaderCard leader);
		void setDeck(CardSet set);




};

 
#endif __cardCollections_H__ 
