#pragma once
#include <unordered_map>
#include <string>
#include "EnumClasses.hpp"
#include "Character.hpp"
#include "../Items/Weapon.hpp"
#include "../Items/Armor.hpp"
#include "ResourceBar.hpp"
#include "../Core/KeyboardHandler.hpp"
#include "../Core/background.hpp"
#include "../Core/dialogBox.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>

/// @file

/// \brief
/// A class that represents a playable character
class PlayerCharacter : public Character {
private:
	bool isLevelUp = false;
	int experience = 0;
	int experienceGauge = 100;
	int abilityPoints = 2;

	// Filename for the portrait
	std::string portraitFileName;


	std::unordered_map<WeaponSlots, Weapon> weapons;
	std::unordered_map<ArmorSlots, Armor> armor;

public:
	PlayerCharacter(const std::string & characterName, const std::string & textureName, const int & exp = 99);
	//- Fix constructor initialization sequence to a logical order
	PlayerCharacter(const std::string & characterName, const std::string & textureName, const int & frameAmount, const int & exp = 99);

	/// \brief
	/// Increases experience by given amount
	void increaseExperience(const int & exp);

	/// \brief
	/// Returns total experience this character has gained
	int calculateTotalExperience();

	/// \brief
	/// Returns boolean if the playercharacter levelled up 
	bool getLevelUp();

	/// \brief
	/// \Returns the required experience for level up
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

	/// \brief
	/// Sets given armor to given armorslot
	void removeArmor(const ArmorSlots & slot);

	/// \brief
	/// Sets given weapon to given weaponslot
	void removeWeapon(const WeaponSlots & slot);


	std::unordered_map<WeaponSlots, Weapon> getWeaponMap();

	std::unordered_map<ArmorSlots, Armor> getArmorMap();


	void clearEquipment();

	int getAbilityPoints();
	int getExperienceGauge();
	int getExperience();
	void setIsLevelUp(bool value);
	void setAbilityPoints(const unsigned int & ap);

	/// \brief
	/// Creates a window the player can interact with to level up
	void levelUp(sf::RenderWindow & window);
	
	/// \brief
	/// gets all modifiers combined from armor
	std::unordered_map<AbilityScores, int> getArmorModifierTotal();

};