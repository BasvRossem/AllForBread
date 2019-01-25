#include "Monster.hpp"

Monster::Monster(const std::string & characterName, const std::string & textureName) :
	Character(characterName, textureName),
	rewardExperience((rand() % 6 + 5) * level),
	rewardCurrency((rand() % 5 + 1) * level)
{
	printRewards();
}

Monster::Monster(const std::string & characterName, const std::string & textureName, const int & frameAmount) :
	Character(characterName, textureName, frameAmount),
	rewardExperience((rand() % 6 + 5) * level),
	rewardCurrency((rand() % 5 + 1) * level)
{
	printRewards();
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
	sprite->scale(-1.0f, 1.0f);
}

void Monster::printRewards() {
	std::cout << "Reward experience: " << rewardExperience << "\nReward currency: " << rewardCurrency << "\n";
}