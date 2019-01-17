#pragma once

#include "Character.hpp"
#include <SFML/Graphics.hpp>
#include <cstdlib>


class Monster : public Character {
private:
	const int rewardExperience;
	const int rewardCurrency;

public:
	Monster(std::string characterName, std::string textureName);

	const int getRewardExperience();
	const int getRewardCurrency();

	void doDeath() override;

	//-Debug printing function
	void printRewards();
};