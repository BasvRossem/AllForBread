#pragma once
#include <unordered_map>
#include "EnumClasses.hpp"
#include "Character.hpp"
#include <string>

class PlayerCharacter : public Character {
private:
	int experience = 0;
	int experienceGauge = 100;
	int abilityPoints = 0;

public:
	PlayerCharacter(std::string characterName, std::string textureName, const int & exp = 0) :
		Character(characterName, textureName),
		experience(exp) {
	};

	void increaseExperience(const int &);
	int calculateTotalExperience();
	void decreaseAbilityScore(const AbilityScores &, const int &);
	void increaseAbilityScore(const AbilityScores &, const int &);
	
	void printAbilityStats();
	void printExperience();
	void printTotalExperience();
};