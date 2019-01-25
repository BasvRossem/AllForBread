#pragma once
#include "PlayerCharacter.hpp"
#include "CharacterContainer.hpp"
#include <memory>
#include <vector>
#include "../Items/Item.hpp"
/// @file

/// \brief
/// A class that handles the storage of player characters.
/// This is a specialisation of the charactercontainer
class Party : public CharacterContainer< std::shared_ptr<PlayerCharacter>, 4> {
private:
	int currency = 0;
	int overworldPosition = 0;
	std::vector<std::shared_ptr<Item> > inventory;
public:
	Party(const std::vector<std::shared_ptr<PlayerCharacter>> & players);

	/// \brief
	/// Awards experience distributed evenly between all members
	void addExperience(const int & exp);

	/// \brief
	/// Adds currency given amount
	void addCurrency(const int & currencyModifier);

	/// \brief
	/// Lowers currency by given amount
	void decreaseCurrency(const int & currencyModifier);

	/// \brief
	/// Returns current currency
	int getCurrency();


	/// \brief
	/// sets Overworld Position to given value
	void setOverworldPosition(const int &);

	/// \brief
	/// Returns current Overworld Position
	int getOverworldPosition();

	std::vector<std::shared_ptr<Item> > getInventory();

	void addToInventory(const std::shared_ptr<Item> & item);
	
	void eraseItem(std::shared_ptr<Item> i);

	void addWeapontoPartyMember(std::shared_ptr<PlayerCharacter> ,std::shared_ptr<Weapon> i);

	void addArmortoPartyMember(std::shared_ptr<PlayerCharacter>, std::shared_ptr<Armor> i);


};