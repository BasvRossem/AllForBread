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

	std::unordered_map<WeaponSlots, Weapon> weapons;
	std::unordered_map<ArmorSlots, Armor> armor;

public:
	PlayerCharacter(const std::string & characterName, const std::pair<const std::string &, const std::string &> & texture, const int & exp = 99);
	//- Fix constructor initialization sequence to a logical order

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


	std::unordered_map<WeaponSlots, Weapon> getWeaponMap();

	std::unordered_map<ArmorSlots, Armor> getArmorMap();

	/// \brief
	/// Creates a window the player can interact with to level up
	void levelUp(sf::RenderWindow & window);
};