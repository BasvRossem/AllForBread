#include "PlayerCharacter.hpp"

void PlayerCharacter::increaseExperience(const int & exp) {

	//-Safeguard from negative xpReward Values
	if (exp <= 0) {
		return;
	}

	if (experience + exp >= experienceGauge) {
		int excessExperience = (experience + exp) - experienceGauge;
		experience = 0;
		level++;
		abilityPoints++;
		float newExperienceGauge = experienceGauge * float(1.2);
		experienceGauge = static_cast<int>(newExperienceGauge);
		increaseExperience(excessExperience);

	} else {
		experience += exp;
		return;
	}
}


int PlayerCharacter::calculateTotalExperience() {
	int totalExperience = 0;
	int experiencePerLevel = 100;

	for (int i = 1; i < level; i++) {
		totalExperience += experiencePerLevel;
		float newExperiencePerLevel = experiencePerLevel * float(1.2);
		experiencePerLevel = static_cast<int>(newExperiencePerLevel);
	}

	totalExperience += experience;

	return totalExperience;
}

int PlayerCharacter::requiredExperience() {
	return experienceGauge - experience;
}

void PlayerCharacter::increaseAbilityScore(const AbilityScores & stat, const int & statIncrease) {
	//-Safeguard for negative integers in parameter: "statIncrease"
	if (statIncrease < 0) {
		std::cout << "Parameter: 'statIncrease' value is smaller than 0, Value: " << statIncrease << "\n";
		return;
	}
	if (characterStats[stat] + statIncrease > 99) {
		characterStats[stat] = 99;
	} else {
		characterStats[stat] += statIncrease;
	}
}

void PlayerCharacter::decreaseAbilityScore(const AbilityScores & stat, const int & statDecrease) {
	//-Safeguard from negative	 integers in parameter: "statDecrease"
	if (statDecrease < 0) {
		std::cout << "Parameter: 'statDecrease' value is smaller than 0, Value: " << statDecrease << "\n";
		return;
	}

	if (characterStats[stat] - statDecrease < 0) {
		characterStats[stat] = 0;
	} else {
		characterStats[stat] -= statDecrease;
	}
}

void PlayerCharacter::printAbilityStats() {
	std::cout << "Vit:	" << characterStats[AbilityScores::vitality]	<< "\n";
	std::cout << "Str:	" << characterStats[AbilityScores::strength]	<< "\n";
	std::cout << "Dex:	" << characterStats[AbilityScores::dexterity]	<< "\n";
	std::cout << "Arc:	" << characterStats[AbilityScores::arcanism]	<< "\n";
	std::cout << "Cha:	" << characterStats[AbilityScores::charisma]	<< "\n";
	std::cout << "Lck:	" << characterStats[AbilityScores::luck]		<< "\n";
	std::cout << "\n";
}

void PlayerCharacter::printTotalExperience() {
	std::cout << "Total experience aquired: " << calculateTotalExperience() << "\n";
}

void PlayerCharacter::printExperience() {
	std::cout << "Current Experience:	" << experience << "\n";
	std::cout << "Experience Gauge:	" << experienceGauge << "\n";
	std::cout << "Player Level:		" << level << "\n";
	std::cout << "\n";
}