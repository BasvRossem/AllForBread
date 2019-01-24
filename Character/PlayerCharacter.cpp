#include "PlayerCharacter.hpp"

PlayerCharacter::PlayerCharacter(const std::string & characterName, const std::string & textureName, const int & exp) :
	Character(characterName, textureName),
	experience(exp) {
};

PlayerCharacter::PlayerCharacter(const std::string & characterName, const std::string & textureName, const int & frameAmount, const int & exp) :
	Character(characterName, textureName, frameAmount),
	experience(exp) {
};

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


void PlayerCharacter::printTotalExperience() {
	std::cout << "Total experience aquired: " << calculateTotalExperience() << "\n";
}

void PlayerCharacter::printExperience() {
	std::cout << "Current Experience:	" << experience << "\n";
	std::cout << "Experience Gauge:	" << experienceGauge << "\n";
	std::cout << "Player Level:		" << level << "\n";
	std::cout << "\n";
}

Armor PlayerCharacter::getArmor(const ArmorSlots & slot) {
	return armor.at(slot);
}

Weapon PlayerCharacter::getWeapon(const WeaponSlots & slot) {
	return weapons.at(slot);
}

void PlayerCharacter::setArmor(const ArmorSlots & slot, const Armor & newArmor) {
	armor[slot] = newArmor;
}

void PlayerCharacter::setWeapon(const WeaponSlots & slot, const Weapon & newWeapon) {
	switch (slot) {
	case WeaponSlots::twohanded:
		if (weapons.find(WeaponSlots::mainhand) != weapons.end()) {
			weapons.erase(WeaponSlots::mainhand);
		}
		if (weapons.find(WeaponSlots::offhand) != weapons.end()) {
			weapons.erase(WeaponSlots::offhand);
		}
		break;

	case WeaponSlots::offhand:
	case WeaponSlots::mainhand:
		if (weapons.find(slot) != weapons.end()) {
			weapons.erase(WeaponSlots::twohanded);
		}
		break;
	}
	weapons[slot] = newWeapon;
}

std::unordered_map<WeaponSlots, Weapon> PlayerCharacter::getWeaponMap(){
	return weapons;
}

std::unordered_map<ArmorSlots, Armor> PlayerCharacter::getArmorMap(){
	return armor;
}
