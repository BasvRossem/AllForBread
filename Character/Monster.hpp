#pragma once

#include "Character.hpp"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <utility>
/// @file

/// \brief
/// A class that represents a single fightable monster
class Monster : public Character {
private:
	const int rewardExperience;
	const int rewardCurrency;

public:
	Monster(const std::string & characterName, const std::pair< std::string,  std::string> & texture);

	/// \brief
	/// Returns rewardExperience 
	const int getRewardExperience();

	/// \brief
	/// Returns rewardCurrency
	const int getRewardCurrency();

	/// \brief
	/// Function call for when monster dies
	void doDeath() override;

	/// \brief
	/// DEBUG!
	/// Prints all reward variables in console
	void printRewards();

};