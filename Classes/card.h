#ifndef __card_H__ 
#define __card_H__ 

#include <json/json.h>

enum CardType { NullCType, Unit, Spell };
enum CardSet {NullCSet, Northern, Nilfgaarian, Monster, Scoiateal, Neutral};
enum UnitType {NullUType, CloseCombat, RangedCombat, Seige, CloseRangedCombat};
enum UnitLevel {NullULevel, Ordinary, Hero };
enum SpellType {NullSType, Weather, Horn, Decoy, Scorch};
enum WeatherType {NullWType, Bitingfroest, Fog, Rain, ClearWeather};
enum EffectType {NullEType, Agile, Spy, TightBond, Decoy, Medic, 
				SpellHorn, UnitHorn, SpellScorch, UnitScorch, Muster, 
				MoraleBoost, BitingFrost, Fog, Rain, ClearWeather };

class Card {
private:
	int cardID;
	int countLimit;
	int strength;
	std::string picDir;
	std::string name;
	std::string discription;
	CardType cardType;
	CardSet cardSet;
	UnitType unitType;
	UnitLevel unitLevel;
	SpellType spellType;
	WeatherType weatherType;
	std::vector<EffectType> effects;
	bool exEffect;

public:
	Card();
	Card(int id);
	~Card() {}

	void reload(int id);

/*return the collection limit of this card*/
	int getCountLimit();
/*return the direction of the picture*/
	std::string getPicDir();
/*return the card name*/
	std::string getCardName();
/*return the card type*/
	std::string getCardDiscription();
/*return the card type*/
	CardType getCardType();
/*return the card set*/
	CardSet getSet();
/*return the card set*/
	UnitType getCardSet();
/*return the strength*/
	int getStrength();
/*return the unit level*/
	UnitLevel getUnitLevel();
/*return the spell type*/
	SpellType getSpellType();
/*return the weather type*/
	WeatherType getWeatherType();
/*return whether there is extral effect(this is under constraction)*/
	bool existEx();
/*change strenth*/
	void changeStrengthTo(int CStrength);


};

#endif __card_H__ 
