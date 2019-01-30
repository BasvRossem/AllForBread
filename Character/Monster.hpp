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
	/// Draws the monster on the renderwindow
	void draw(sf::RenderWindow & window) override;

	/// \brief
	/// Draws the monster on the virtualscreen
	void draw(VirtualScreen & virtualWindow) override;

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

	/// \brief
	/// Returns a vector containing all the attacks a monster can perform
	std::vector<std::tuple<std::string, WeaponSlots, int>> getAvailableAttacks() override;

	/// \brief 
	/// Simplified version of the players generateAttack, damage scales with level
	std::vector<std::pair<DamageTypes, int>> generateAttack(const std::tuple<std::string, WeaponSlots, int> & attackDefenition) override;

};