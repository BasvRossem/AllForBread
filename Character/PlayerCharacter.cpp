#include "PlayerCharacter.hpp"

PlayerCharacter::PlayerCharacter(const std::string & characterName, const std::pair<const std::string &, const std::string &> & texture, const int & exp) :
	Character(characterName, texture),
	experience(exp){
};

void PlayerCharacter::draw(sf::RenderWindow & window) {
	window.draw(*sprite);
	healthBar.draw(window);
}

void PlayerCharacter::draw(VirtualScreen & virtualWindow) {
	virtualWindow.drawSurfaceDraw(*sprite);
	healthBar.draw(virtualWindow);
}

void PlayerCharacter::increaseExperience(const int & exp) {
	//-Safeguard from negative xpReward Values
	if (exp <= 0) {
		return;
	}

	if (experience + exp >= experienceGauge) {
		int excessExperience = (experience + exp) - experienceGauge;
		experience = 0;
		level++;
		isLevelUp = true;
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

bool PlayerCharacter::getLevelUp() {
	return isLevelUp;
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

const int PlayerCharacter::getCurrentExperience() {
	return experience;
}

const int PlayerCharacter::getMaxExperience() {
	return experienceGauge;
}

void PlayerCharacter::setPortraitFilename(const std::string & filename) {
	if (filename.size() > 0) {
		portraitFileName = filename;
	}
}

const std::string PlayerCharacter::getFilename() {
	return portraitFileName;
}

std::unordered_map<WeaponSlots, Weapon> PlayerCharacter::getWeaponMap(){
	return weapons;
}

std::unordered_map<ArmorSlots, Armor> PlayerCharacter::getArmorMap(){
	return armor;
}

void PlayerCharacter::clearEquipment() {
	weapons.clear();
	armor.clear();
}

//====================================================================================================================================
// Itereer over de map weapons, kijk welke handslots occupied zijn en return deze in een vector van tuples (attacks)
std::vector<std::tuple<std::string, WeaponSlots, int>> PlayerCharacter::getAvailableAttacks() {

	std::vector<std::tuple<std::string, WeaponSlots, int>> attackDefenitions = attacks.getAttacks();
	std::vector<std::tuple<std::string, WeaponSlots, int>> availableAttacks;

	// Types of attacks: { "Mainhand", WeaponSlots::mainhand, 7 }, { "Offhanded",  WeaponSlots::offhand, 5 }, { "Twohanded", WeaponSlots::twohanded, 10 }

	for (auto & index : weapons) {
		for (auto & defenition : attackDefenitions) {
			if (index.first == std::get<1>(defenition)) {
				availableAttacks.push_back(defenition);
			}
		}
	}

	// Safeguard for when a player does not have weapons
	if (availableAttacks.size() == 0) {
		availableAttacks.push_back({ "Punch", WeaponSlots::mainhand, 1 });
	}

	return availableAttacks;
}

// Parameter wordt tuple met attackDefenition, dan weet je zeker dat weaponslot occupied is
std::vector<std::pair<DamageTypes, int>> PlayerCharacter::generateAttack(const std::tuple<std::string, WeaponSlots, int> & attackDefenition) {

	std::vector<std::pair<DamageTypes, int>> attackInformation = { {} };

	// Safeguard from when a player does not have weapons
	if (std::get<0>(attackDefenition) == "Punch") {
		attackInformation[0].first = DamageTypes::bludgeoning;
		//Punch Damage = 											  [Base Value]	  *			[Strength]
		attackInformation[0].second = static_cast<int>(std::get<2>(attackDefenition) * (getStat(AbilityScores::strength)));

		return attackInformation;

	} else {

		Weapon currentWeapon = this->getWeapon(std::get<1>(attackDefenition));

		DamageTypes weaponDamageType = currentWeapon.getPrimaryDamageEffect().first;

		attackInformation[0].first = weaponDamageType;
		
		int primaryTypeDamage = currentWeapon.getPrimaryDamageEffect().second;

		//Attack Damage				[AbilityScore Value]				*	[Weapon Value]	 +	[Twohanded Base Damage]
		int finalAttackDamage = ((getStat(getScaling(weaponDamageType)) * primaryTypeDamage) + std::get<2>(attackDefenition));

		attackInformation[0].second = finalAttackDamage;

		// Add Secondary DamageTypes and DamageValues
		for (auto & index : currentWeapon.getSecondaryDamageEffects()) {
			attackInformation.push_back(index);
		}

		return attackInformation;
	}
}
//====================================================================================================================================


void PlayerCharacter::setIsLevelUp(bool value) {
	isLevelUp = value;
}

void PlayerCharacter::setAbilityPoints(const unsigned int & ap) {
	abilityPoints = ap;
}


int PlayerCharacter::getAbilityPoints() {
	return abilityPoints;
}

int PlayerCharacter::getExperienceGauge() {
	return experienceGauge;
}

int PlayerCharacter::getExperience() {
	return experience;
}

void PlayerCharacter::setExperience(const int & exp)
{
	experience = exp;
}

std::unordered_map<AbilityScores, int> PlayerCharacter::getArmorModifierTotal() {
	std::unordered_map<AbilityScores, int> totals;
	for (auto armorPiece : armor) {
		for (auto stat : armorPiece.second.getPropertyModifiers()) {
			totals[stat.first] += stat.second;
		}
	}


	return totals;
}

void PlayerCharacter::removeArmor(const ArmorSlots & slot) {
	armor.erase(slot);

	/*sf::sleep(sf::seconds(0.5f));
	sound.playSoundEffect(SoundEffect::scrollClose);
	sf::sleep(sf::seconds(0.5f));*/
	isLevelUp = false;
}

void PlayerCharacter::removeWeapon(const WeaponSlots & slot) {
	weapons.erase(slot);
}
