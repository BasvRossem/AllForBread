#pragma once
#include <unordered_map>
#include "EnumClasses.hpp"
#include "Character.hpp"

class PlayerCharacter : public Character {
private:
	int experience = 0;
	int experienceGauge = 100;
	int abilityPoints = 0;

public:
	PlayerCharacter(std::string & textureName, const sf::Vector2u & imageCount, const float & switchTime, const sf::Vector2f & imageSize, const int & exp = 0) :
		Character(textureName, imageCount, switchTime, imageSize),
		experience(exp) {
	};

	void increaseExperience(const int &);
	int calculateTotalExperience();
	void increaseAbilityScore(const AbilityScores &, const int &);
	
	void printAbilityStats();
	void printTotalExperience();
};