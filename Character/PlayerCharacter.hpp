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

	// Filename for the portrait
	std::string portraitFileName;


	std::unordered_map<WeaponSlots, Weapon> weapons;
	std::unordered_map<ArmorSlots, Armor> armor;

public:
	PlayerCharacter(const std::string & characterName, const std::string & textureName, const int & exp = 0);
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

	/// \brief
	/// Returns the current experience this player has
	const int getCurrentExperience();

	/// \brief
	/// Returns the maximum experience required to levelup
	const int getMaxExperience();

	/// \brief
	/// Sets the filename of the portrait
	void setPortraitFilename(const std::string & filename);

	/// \brief
	/// Returns current portrait filename
	/// Remember that the portrait gets loaded at the open function of partyOverview
	const std::string getFilename();
};