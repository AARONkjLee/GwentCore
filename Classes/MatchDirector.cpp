#include "MatchDirector.h" 

static MatchDirector* s_SharedMatchDirector = nullptr;

void MatchDirector::updateField()
{
	field = &BattleInfoManager::getInstance()->getBattlefield();
	//cocos2d::log("%i", field->p0Deck[3]);
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

void MatchDirector::setGUILayer(SinglePlayScene * gui)
{
	GUI = gui;
}

void MatchDirector::MainMatchLoop()
{
	BeforeGame();
	while (!GameOver()) {
		Turn(field->whosTurn);
		break;
	}
	AfterGame();
}

void MatchDirector::init()
{
	updateField();
	AI::getInstance()->selectDeck(Nilfgaardian);
}

void MatchDirector::BeforeGame()
{
	StarterModel();
	SwitchHands();
	InitMatch();
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
			//下版本再做
			//Starter = GUI->selectStarterByUser();
			Starter = 1;
		}
		else {
			Starter = AI::getInstance()->selectStarter();
			}
	}
	else {
		Starter = rand() % 2;
	}
	field->whosTurn = Starter;
	BattleInfoManager::getInstance()->initWithFirstPlayer(Starter);
	GUI->initWithStarter(Starter);
	
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
		field->p0Hand.push_back(field->p0Deck.back());
		field->p0Deck.pop_back();
		field->p1Hand.push_back(field->p1Deck.back());
		field->p1Deck.pop_back();
	}
	int cardIDToSwitch;
	cardIDToSwitch = AI::getInstance()->selectSwitchHand();
	if (cardIDToSwitch != -1) {
		field->p1Deck.push_back(cardIDToSwitch);
		std::random_shuffle(field->p1Deck.begin(), field->p1Deck.end());
		field->p1Hand.push_back(field->p1Deck.back());
		field->p1Deck.pop_back();
		cardIDToSwitch = AI::getInstance()->selectSwitchHand();
		if (cardIDToSwitch != -1) {
			field->p1Deck.push_back(cardIDToSwitch);
			std::random_shuffle(field->p1Deck.begin(), field->p1Deck.end());
			field->p1Hand.push_back(field->p1Deck.back());
			field->p1Deck.pop_back();
		}
	}
	// 下版本再做
	//GUI->select1stHandToSwitch();
	//GUI->select2ndHandToSwitch();
}

void MatchDirector::InitMatch()  //下版本再做
{
	//所有游戏开局初始效果
	updateField();
	std::vector<int> initMatchEffectsCIDList;
//	initMatchEffectsCIDList = CardEffectManager.initMatchEffectsCIDList();
	if (std::count(initMatchEffectsCIDList.begin(), initMatchEffectsCIDList.end(), field->p0LeaderID)) {
		//CardEffectManager::checkEffect(field->p0LeaderID);
	}
	if (std::count(initMatchEffectsCIDList.begin(), initMatchEffectsCIDList.end(), field->p1LeaderID)) {
		//CardEffectManager::checkEffect(field->p1LeaderID);
	}
}

void MatchDirector::P0Turn()
{
	updateField();
	if (field->p0Pass) {
		//GUI->playerPassedTurn();
		field->whosTurn = 1;
		return;
	}
	//GUI->annoucePlayerTurn();
	bool played=false;

	////////////////////

	while (played) {
		int promptCID;

		if (field->p0Hand.size() == 0 && field->p0LeaderAviable == false) {
			promptCID = -1; // 没手牌没领导牌自动结束回合
		}
		else {
			// promptCID = GUI->promptPlayCard();
				// -2 为领导牌，不过如果已经使用过了领导牌，GUI不让点领导牌
				// -1 为回合结束
		}

		if (promptCID == -1) {
			field->p0Pass = true;
			//GUI->PlayerPassing();
			break;
		}

		std::vector<CPosition> leaglPlayTargetZones;
		std::vector<int> leaglPlayTargetCIDs;
		CardEffectManager::checkPrompt(0, promptCID, leaglPlayTargetZones,leaglPlayTargetCIDs);
		// 上一个函数的后两个para是pass by reference

		CPosition promptZone;
		int promptTargetCID;
		// GUI->setPromptPlayCardZoneAndCID(promptZone, promptTargetCID);
		// 上一个函数的两个para是pass by reference
		// 对于及时Spell Zone回是墓地

		bool legalPlay;
		if (std::count(leaglPlayTargetZones.begin(), leaglPlayTargetZones.end(), promptZone) == 0) {
			legalPlay = false;
		}
		else {
			if (std::count(leaglPlayTargetCIDs.begin(), leaglPlayTargetCIDs.end(), promptTargetCID) == 0 &&
				leaglPlayTargetCIDs.size() > 0) {
				legalPlay = false;
			}
			else {
				legalPlay = true;
			}
		}

		if (!legalPlay) {
			//GUI->illegalPrompt();
			continue;
		}
		else {
			BattleInfoManager::getInstance()->playCardFromHand(0, promptCID, promptZone);
			// GUI->PlayAnimation(0, promptCID, promptZone);
			played = true;
		}
		//下版本再做
		//CardEffectManager::checkEffect(0, promptCID, promptZone， promptTarget);
	}
	
	IndicatingWinning();
	field->whosTurn = 1;
}

void MatchDirector::P1Turn()
{
	updateField();
	if (field->p1Pass) {
		//GUI->playerPassedTurn();
		field->whosTurn = 0;
		return;
	}
	//GUI->annoucePlayerTurn();
	bool played = false;
	while (played) {
		int promptCID;
		CPosition promptZone;
		int promptTargetCID;
		
		if (field->p1Hand.size() == 0 && field->p1LeaderAviable == false) {
			promptCID = -1; // 没手牌没领导牌自动结束回合
		}
		else {
			
			promptCID = AI::getInstance()->selectCardToPlay(Hand1, promptZone, promptTargetCID);
			
			// -2 为领导牌，不过如果已经使用过了领导牌，GUI不让点领导牌
			// -1 为回合结束
			
			// 上一个函数的两个para是pass by reference
			// 对于及时Spell Zone回是墓地
		}

		if (promptCID == -1) {
			field->p1Pass = true;
			//GUI->OppentPassing();
			break;
		}

		std::vector<CPosition> leaglPlayTargetZones;
		std::vector<int> leaglPlayTargetCIDs;
		//CardEffectManager::checkPrompt(1， promptCID, leaglPlayTargetZones,leaglPlayTargetCIDs);
		// 上一个函数的后两个para是pass by reference		

		bool legalPlay=true;
		// 默认AIobj一定正确
		if (!legalPlay) {
			cocos2d::log("AI doing illegal play.  Forced to end its turn.");
			field->p1Pass = true;
			//GUI->OppentPassing();
			continue;
		}
		else {
			BattleInfoManager::getInstance()->playCardFromHand(1, promptCID, promptZone);
			// GUI->PlayAnimation(1, promptCID, promptZone);
			played = true;
		}
		//CardEffectManager::checkEffect(1, promptCID, promptZone， promptTarget);
	}

	IndicatingWinning();
	field->whosTurn = 0;
}

void MatchDirector::IndicatingWinning()
{
	updateField();
	if (field->p0Pass == true && field->p1Pass == true) {
		int p0Total=0;
		int p1Total=0;
		for (int i : field->p0Combat) {
			p0Total += CardEffectManager::getInstance()->getCardCurrentStrengthWithPositon(i, Combat1);
		}
		for (int i : field->p1Combat) {
			p1Total += CardEffectManager::getInstance()->getCardCurrentStrengthWithPositon(i, Combat2);
		}
		for (int i : field->p0Ranged) {
			p0Total += CardEffectManager::getInstance()->getCardCurrentStrengthWithPositon(i, Ranged1);
		}
		for (int i : field->p1Ranged) {
			p0Total += CardEffectManager::getInstance()->getCardCurrentStrengthWithPositon(i, Ranged2);
		}
		for (int i : field->p0Siege) {
			p0Total += CardEffectManager::getInstance()->getCardCurrentStrengthWithPositon(i, Siege1);
		}
		for (int i : field->p1Siege) {
			p0Total += CardEffectManager::getInstance()->getCardCurrentStrengthWithPositon(i, Siege2);
		}

		// Nilf Effect
		if (p0Total == p1Total) {
			if (getCardSetOfPlayer(0) == Nilfgaardian &&
				getCardSetOfPlayer(1) != Nilfgaardian) {
				roundResult(0);
			}
			else if (getCardSetOfPlayer(1) == Nilfgaardian &&
					getCardSetOfPlayer(0) != Nilfgaardian)
			{
				roundResult(1);
			}
			else {
				roundResult(-1);
			}
		}
		else {
			roundResult((p0Total > p1Total) ? 0 : 1);
		}
	}
	matchResult();
}

void MatchDirector::roundResult(int winner)
{
	updateField();
	if (winner == 0) {
		field->p0Wins += 1;
	}
	else if (winner == 1) {
		field->p1Wins += 1;
	}
	else {
		field->p0Wins += 1;
		field->p1Wins += 1;
	}
	updateField();
	//GUI->announceRoundResult(int winner);

	BattleInfoManager::getInstance()->moveAllCardsToGrave();
	field->whosTurn = winner;
	field->p0Pass = false;
	field->p1Pass = false;
	updateField();

	//GUI->clearFieldToGrave();
	//记得清理天气

	//To-do Monster阵营效果
	//To-do 北方阵营效果
}

void MatchDirector::matchResult()
{
	if (field->p0Wins == 2) {
		//GUI->announceMatchResout(0);
	}
	else if (field->p1Wins == 2) {
		//GUI->announceMatchResout(1);
	}
}




