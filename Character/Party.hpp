#pragma once
#include "PlayerCharacter.hpp"
#include "CharacterContainer.hpp"
#include <memory>
#include <vector>
/// @file

/// \brief
/// A class that handles the storage of player characters.
/// This is a specialisation of the charactercontainer
class Party : public CharacterContainer< std::shared_ptr<PlayerCharacter>, 4> {
private:
	int currency = 0;
	int overworldPosition = 0;
public:
	Party(const std::vector<std::shared_ptr<PlayerCharacter>> &);

	/// \brief
	/// Awards experience distributed evenly between all members
	void addExperience(const int &);

	/// \brief
	/// Adds currency given amount
	void addCurrency(const int &);

	/// \brief
	/// Lowers currency by given amount
	void decreaseCurrency(const int &);

	/// \brief
	/// Returns current currency
	int getCurrency();


	/// \brief
	/// sets Overworld Position to given value
	void setOverworldPosition(const int &);

	/// \brief
	/// Returns current Overworld Position
	int getOverworldPosition();
};