#pragma once
#include <unordered_map>
#include "EnumClasses.hpp"
#include "Character.hpp"
#include <string>
/// @file

/// \brief
/// A class that represents a playable character
class PlayerCharacter : public Character {
private:
	int experience = 0;
	int experienceGauge = 100;
	int abilityPoints = 0;

public:
	PlayerCharacter(const std::string & characterName, const std::string & textureName, const int & exp = 0);
	PlayerCharacter(const std::string & characterName, const std::string & textureName, const int & frameAmount, const int & exp = 0);

	/// \brief
	/// Increases experience by given amount
	void increaseExperience(const int &);

	/// \brief
	/// Returns total experience this character has gained
	int calculateTotalExperience();

	/// \brief
	/// Prints current experience
	void printExperience();

	/// \brief
	/// Prints total experience this character has gained
	void printTotalExperience();
};