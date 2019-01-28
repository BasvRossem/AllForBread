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
	sprite->scale(-1.0f, 1.0f);
}

void Monster::printRewards() {
	std::cout << "Reward experience: " << rewardExperience << "\nReward currency: " << rewardCurrency << "\n";
}

