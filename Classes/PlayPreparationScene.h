#pragma once

#include "cocos2d.h"
#include "MainScene.h"
#include "BattleInfoManager.h"
#include "SinglePlayScene.h"

#define WIN_CORDINATE_2_GL(xc, yc, w, l) visibleSize.width/33.867*(xc+w/2), visibleSize.height/19.05*(19.05-yc-l/2)


const std::string PLAY_PREPARATION_BG = "PlayScene/PlayPreparationScene/PreparationBG.jpg";
const std::string PLAY_PREPARATION_TITLE_PIC = "PlayScene/PlayPreparationScene/TitleText.png";
const std::string PLAY_PREPARATION_ScoiataelText_PIC = "PlayScene/PlayPreparationScene/ScoiataelText.png";
const std::string PLAY_PREPARATION_NorthernKingdomsText_PIC = "PlayScene/PlayPreparationScene/NorthernKingdomsText.png";
const std::string PLAY_PREPARATION_NilfgaardianEmpireText_PIC = "PlayScene/PlayPreparationScene/NilfgaardianEmpireText.png";
const std::string PLAY_PREPARATION_MonsterText_PIC = "PlayScene/PlayPreparationScene/MonsterText.png";

const std::string PLAY_PREPARATION_ScoiataelBack_PIC = "PlayScene/PlayPreparationScene/ScoiataelBack.jpg";
const std::string PLAY_PREPARATION_NorthernRealmsBack_PIC = "PlayScene/PlayPreparationScene/NorthernRealmsBack.jpg";
const std::string PLAY_PREPARATION_NilfgaardianEmpireBack_PIC = "PlayScene/PlayPreparationScene/NilfgaardianEmpireBack.jpg";
const std::string PLAY_PREPARATION_MonstersBack_PIC = "PlayScene/PlayPreparationScene/MonstersBack.jpg";



struct GUIActCell {
	ActCell actCell;
	std::string info;
};

struct GUICell {

};


class PlayPreparationScene : public cocos2d::Layer
{
private:
	bool clickable;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void GoBackToMainSceneCallback(cocos2d::Ref* pSender);

	std::vector<int> getUserDeck();
	void passDeckBeforPassScene(CardSet set);

	void PlayPreparationScene::replaceToPlaySceneCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(PlayPreparationScene);
};
