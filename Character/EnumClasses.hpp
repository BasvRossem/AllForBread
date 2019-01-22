#pragma once

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