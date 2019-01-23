#pragma once
#include <unordered_map>
#include <string>
#include "EnumClasses.hpp"
#include "Character.hpp"
#include "../Items/Weapon.hpp"
#include "../Items/Armor.hpp"

/// @file

/// \brief
/// A class that represents a playable character
class PlayerCharacter : public Character {
private:
	int experience = 0;
	int experienceGauge = 100;
	int abilityPoints = 0;

	std::unordered_map<WeaponSlots, Weapon> weapons;
	std::unordered_map<ArmorSlots, Armor> armor;

public:
	PlayerCharacter(const std::string & characterName, const std::string & textureName, const int & exp = 0);
	//- Fix constructor initialization sequence to a logical order
	PlayerCharacter(const std::string & characterName, const std::string & textureName, const int & frameAmount, const int & exp = 0);

	/// \brief
	/// Increases experience by given amount
	void increaseExperience(const int & exp);

	/// \brief
	/// Returns total experience this character has gained
	int calculateTotalExperience();


	int requiredExperience();

	/// \brief
	/// Prints current experience
	void printExperience();

	/// \brief
	/// Prints total experience this character has gained
	void printTotalExperience();

	/// \brief
	/// Returns armor for requested slot
	Armor getArmor(const ArmorSlots & slot);

	/// \brief
	/// Returns weapon for requested slot
	Weapon getWeapon(const WeaponSlots & slot);

	/// \brief
	/// Sets given armor to given armorslot
	void setArmor(const ArmorSlots & slot, const Armor & newArmor);

	/// \brief
	/// Sets given weapon to given weaponslot
	void setWeapon(const WeaponSlots & slot, const Weapon & newWeapon);
};