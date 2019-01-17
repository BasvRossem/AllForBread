#include "Monster.hpp"

Monster::Monster(std::string characterName, std::string textureName):
	Character(characterName, textureName),
	rewardExperience((rand() % 6 + 5) * level),
	rewardCurrency((rand() % 5 + 1) * level)
{
	printRewards();
}

const int Monster::getRewardExperience() {
	return rewardExperience;
}

const int Monster::getRewardCurrency() {
	return rewardCurrency;
}

void Monster::doDeath() {
	std::cout << name << " is dead!\n";
	currentAnimation = Animation(sprite, deathTexture, float(1.0));
}

void Monster::printRewards() {
	std::cout << "Reward experience: " << rewardExperience << "\nReward currency: " << rewardCurrency << "\n";
}