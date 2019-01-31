#include "Monster.hpp"

Monster::Monster(const std::string & characterName, const std::pair< std::string, std::string> & texture) :
	Character(characterName, texture),
	rewardExperience((rand() % 6 + 5) * level),
	rewardCurrency((rand() % 5 + 1) * level)
{
	printRewards();
	makeMonster();
}

void Monster::draw(sf::RenderWindow & window) {
	window.draw(*sprite);
}

void Monster::draw(VirtualScreen & virtualWindow) {
	virtualWindow.drawSurfaceDraw(*sprite);
}

const int Monster::getRewardExperience() {
	return rewardExperience;
}

const int Monster::getRewardCurrency() {
	return rewardCurrency;
}

void Monster::doDeath() {
	std::cout << name << " is dead!\n";
	currentAnimation = deathAnimation;
}

void Monster::printRewards() {
	std::cout << "Reward experience: " << rewardExperience << "\nReward currency: " << rewardCurrency << "\n";
}

std::vector<std::tuple<std::string, WeaponSlots, int>> Monster::getAvailableAttacks() {
	std::vector < std::tuple < std::string, WeaponSlots, int >> availableAttack = { { "Punch", WeaponSlots::mainhand, 1 } };
	return availableAttack;
}

std::vector<std::pair<DamageTypes, int>> Monster::generateAttack(const std::tuple<std::string, WeaponSlots, int> & attackDefenition){
	int randomAttackIndex = (rand() % 2 + 0);

	std::vector<std::vector<std::pair<DamageTypes, int>>> attackInformation = { {{DamageTypes::slashing, 10 * level}}, { {DamageTypes::bludgeoning, 20 * level}} };
	return attackInformation[randomAttackIndex];
}

