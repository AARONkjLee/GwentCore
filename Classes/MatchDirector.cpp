#include "MatchDirector.h" 

static MatchDirector* s_SharedMatchDirector = nullptr;

void MatchDirector::updateField()
{
	field = &BattleInfoManager::getInstance()->getBattlefield();
	cocos2d::log("%i", field->p0Deck[3]);
}

MatchDirector::MatchDirector()
{
}

MatchDirector::~MatchDirector()
{
	//delete s_SharedMatchDirector;
}

MatchDirector * MatchDirector::getInstance()
{
	if (!s_SharedMatchDirector)
	{
		s_SharedMatchDirector = new (std::nothrow) MatchDirector;
		s_SharedMatchDirector->init();
	}
	return s_SharedMatchDirector;
}

void MatchDirector::setGUILayer(cocos2d::Layer * gui)
{
	GUI = gui;
}

void MatchDirector::MainMatchLoop()
{
	BeforeGame();
	while (!GameOver()) {
		Turn(Player);
	}
	AfterGame();
}

void MatchDirector::init()
{
}

void MatchDirector::BeforeGame()
{
	StarterModel();
	SwitchHands();
}

bool MatchDirector::GameOver()
{
	updateField();
	if (field->p0Wins >= 2 ||
		field->p1Wins >= 2) {
		return true;
	}
	else {
		return false;
	}
}

void MatchDirector::Turn(int Player)
{
	if (Player == 0) {
		P0Turn();
	}
	else {
		P1Turn();
	}
}

void MatchDirector::AfterGame()
{
	//GUI->announceGameResult();
}

void MatchDirector::StarterModel()
{
	BattleInfoManager::getInstance()->initWithDecks(initDeck0, initDeck1);
	int Starter;
	if ((getCardSetOfPlayer(0) == Scoiateal) ^ (getCardSetOfPlayer(1) == Scoiateal)) {
		if (getCardSetOfPlayer(1) == Scoiateal) {
			//Starter = GUI->selectStarterByUser();
		}
		else {
			//Starter = ai.selectStarterByAI();
		}
	}
	else {
		Starter = rand() % 2;
	}
	BattleInfoManager::getInstance()->initWithFirstPlayer(Starter);
	//GUI->initWithStarter(Starter);
}

CardSet MatchDirector::getCardSetOfPlayer(int player)
{
	int leaderID;
	if (player = 0) {
		leaderID = BattleInfoManager::getInstance()->getBattlefield().p0LeaderID;
	}
	else {
		leaderID = BattleInfoManager::getInstance()->getBattlefield().p1LeaderID;
	}
	return BattleInfoManager::getCardSetFromLeaderID(leaderID);
}


void MatchDirector::SwitchHands()
{                         
	updateField();
	// Init Deck Shuffle Here Below
	std::random_shuffle(field->p0Deck.begin(), field->p0Deck.end());
	std::random_shuffle(field->p1Deck.begin(), field->p1Deck.end());

	for (int i = 0; i < 10; i++) {
		field->p0Hand.push_back(*field->p0Deck.end());
		field->p0Deck.pop_back();
		field->p1Hand.push_back(*field->p1Deck.end());
		field->p1Deck.pop_back();
	}	
	int cardIDToSwitch;
	//cardIDToSwitch = ai.selectSwitchHand();
	field->p1Deck.push_back(cardIDToSwitch);
	std::random_shuffle(field->p1Deck.begin(), field->p1Deck.end());
	field->p1Hand.push_back(*field->p1Deck.end());
	field->p1Deck.pop_back();
	//cardIDToSwitch = ai.selectSwitchHand();
	field->p1Deck.push_back(cardIDToSwitch);
	std::random_shuffle(field->p1Deck.begin(), field->p1Deck.end());
	field->p1Hand.push_back(*field->p1Deck.end());
	field->p1Deck.pop_back();

	//GUI->select1stHandToSwitch();
	//GUI->select2ndHandToSwitch();
}

void MatchDirector::P0Turn()
{
}

void MatchDirector::P1Turn()
{
}




