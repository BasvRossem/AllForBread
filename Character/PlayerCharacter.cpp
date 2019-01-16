#include "PlayerCharacter.hpp"

void PlayerCharacter::increaseExperience(const int & exp) {

	//-Safeguard from negative xpReward Values
	if (exp <= 0) {
		return;
	}

	//-Experience + xpReward >= experienceGauge = level up
	if (experience + exp >= experienceGauge) {
		int excessExperience = (experience + exp) - experienceGauge;
		experience = 0;
		level++;
		abilityPoints++;
		experienceGauge *= 1.2;
		increaseExperience(excessExperience);

	} else {
		experience += exp;
		return;
	}
}


int PlayerCharacter::calculateTotalExperience() {
	int totalExperience = 0;
	int experiencePerLevel = 100;
	for (unsigned int i = 1; i < level; i++) {
		totalExperience += experiencePerLevel;
		experiencePerLevel *= 1.2;
		float newExperiencePerLevel = experiencePerLevel * 1.2;
		experiencePerLevel = static_cast<int>(newExperiencePerLevel);
		std::cout << "Levelcounter: " << i << " totalExperience: " << totalExperience << " experiencePerLevel: " << experience << "\n";
	}

	totalExperience += experience;

	return totalExperience;
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

void PlayerCharacter::printAbilityStats() {
	std::cout << "Str:	" << characterStats[AbilityScores::strength] << "\n";
	std::cout << "Dex:	" << characterStats[AbilityScores::dexterity] << "\n";
	std::cout << "End:	" << characterStats[AbilityScores::endurance] << "\n";
	std::cout << "Arc:	" << characterStats[AbilityScores::arcanism] << "\n";
	std::cout << "Cha:	" << characterStats[AbilityScores::charisma] << "\n";
	std::cout << "\n";
}

void PlayerCharacter::printTotalExperience() {
	std::cout << "Total experience aquired: " << calculateTotalExperience() << "\n";
}