#pragma once
#include <string>

//-Character stats		(Issue 39)
//================================
enum class AbilityScores {
	vitality,
	strength,
	dexterity,
	arcanism,
	charisma,
	luck
};

//-Weapon damage types	(Issue ??)
//================================
enum class DamageTypes {
	piercing,
	bludgeoning,
	slashing,
	acid,
	frost,
	fire,
	force,
	lightning,
	necrotic,
	poison,
	psychic,
	radiant,
	thunder
};

enum class ArmorSlots {
	helmet,
	chestplate,
	legs,
	gauntlets,
	ring,
	boots
};

enum class WeaponSlots {
	mainhand,
	offhand,
	twohanded
};


struct EnumMethods {
public:
	const std::string static getAbilityScoreName(const AbilityScores & score);
	const std::string static getDamageTypeName(const DamageTypes & type);
	const std::string static getArmorSlotName(const ArmorSlots & slot);
	const std::string static getWeaponSlotName(const WeaponSlots & slot);
};
