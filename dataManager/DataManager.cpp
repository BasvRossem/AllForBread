#include "DataManager.hpp"



DataManager::DataManager(const char * s, std::map<std::string, std::function<void()>>&func) :
	functions(func)
{
	db.open(s);

	abilityScores["vitality"]	=	AbilityScores::vitality;
	abilityScores["strength"]	=	AbilityScores::strength;
	abilityScores["dexterity"]	=	AbilityScores::dexterity;
	abilityScores["arcanism"]	=	AbilityScores::arcanism;
	abilityScores["charisma"]	=	AbilityScores::charisma;
	abilityScores["luck"]		=	AbilityScores::luck;

	damageTypes["piercing"]		=	DamageTypes::piercing;
	damageTypes["bludgeoning"]	=	DamageTypes::bludgeoning;
	damageTypes["slashing"]		=	DamageTypes::slashing;
	damageTypes["acid"]			=	DamageTypes::acid;
	damageTypes["frost"]		=	DamageTypes::frost;
	damageTypes["fire"]			=	DamageTypes::fire;
	damageTypes["force"]		=	DamageTypes::force;
	damageTypes["lightning"]	=	DamageTypes::lightning;
	damageTypes["necrotic"]		=	DamageTypes::necrotic;
	damageTypes["poison"]		=	DamageTypes::poison;
	damageTypes["psychic"]		=	DamageTypes::psychic;
	damageTypes["radiant"]		=	DamageTypes::radiant;
	damageTypes["thunder"]		=	DamageTypes::thunder;

	armorSlots["helmet"]		=	ArmorSlots::helmet;
	armorSlots["chestplate"]	=	ArmorSlots::chestplate;
	armorSlots["legs"]			=	ArmorSlots::legs;
	armorSlots["gauntlets"]		=	ArmorSlots::gauntlets;
	armorSlots["ring"]			=	ArmorSlots::ring;
	armorSlots["boots"]			=	ArmorSlots::boots;

	weaponSlots["mainhand"]		=	WeaponSlots::mainhand;
	weaponSlots["offhand"]		=	WeaponSlots::offhand;
	weaponSlots["twohanded"]	=	WeaponSlots::twohanded;

	abilityScoresId[AbilityScores::vitality]	= 1;
	abilityScoresId[AbilityScores::strength]	= 2;
	abilityScoresId[AbilityScores::dexterity]	= 3;
	abilityScoresId[AbilityScores::arcanism]	= 4;
	abilityScoresId[AbilityScores::charisma]	= 5;
	abilityScoresId[AbilityScores::luck]		= 6;
}


DataManager::~DataManager()
{
	db.close();
}
