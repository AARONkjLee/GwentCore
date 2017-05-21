#include "MatchDirector.h" 

static MatchDirector* s_SharedMatchDirector = nullptr;

void MatchDirector::updateField()
{
	field = &BattleInfoManager::getInstance()->getBattlefield();
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
	if ((getCardSet(0) == Scoiateal) ^ (getCardSet(1) == Scoiateal)) {
		if (getCardSet(1) == Scoiateal) {
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

CardSet MatchDirector::getCardSet(int player)
{
	int leaderID;
	if (player = 0) {
		leaderID = BattleInfoManager::getInstance()->getBattlefield().p0LeaderID;
	}
	else {
		leaderID = BattleInfoManager::getInstance()->getBattlefield().p1LeaderID;
	}
	switch (leaderID)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
		return Nilfgaardian;
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		return Northern;
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
		return Scoiateal;
		break;
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
		return Monster;
		break;
	default:
		return NullCSet;
		break;
	}
}


void MatchDirector::SwitchHands()
{                         
	auto bf = & BattleInfoManager::getInstance()->getBattlefield();
	
	// Init Deck Shuffle Here Below
	std::random_shuffle(bf->p0Deck.begin(), bf->p0Deck.end());
	std::random_shuffle(bf->p1Deck.begin(), bf->p1Deck.end());

	for (int i = 0; i < 10; i++) {
		bf->p0Hand.push_back(*bf->p0Deck.end());
		bf->p0Deck.pop_back();
		bf->p1Hand.push_back(*bf->p1Deck.end());
		bf->p1Deck.pop_back();
	}	
	int cardIDToSwitch;
	//cardIDToSwitch = ai.selectSwitchHand();
	bf->p1Deck.push_back(cardIDToSwitch);
	std::random_shuffle(bf->p1Deck.begin(), bf->p1Deck.end());
	bf->p1Hand.push_back(*bf->p1Deck.end());
	bf->p1Deck.pop_back();
	//cardIDToSwitch = ai.selectSwitchHand();
	bf->p1Deck.push_back(cardIDToSwitch);
	std::random_shuffle(bf->p1Deck.begin(), bf->p1Deck.end());
	bf->p1Hand.push_back(*bf->p1Deck.end());
	bf->p1Deck.pop_back();
}

void MatchDirector::P0Turn()
{
}

void MatchDirector::P1Turn()
{
}




