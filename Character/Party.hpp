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
	unsigned int overworldPosition = 0;
	std::vector<std::shared_ptr<Item> > inventory;
	std::shared_ptr<PlayerCharacter> * partyLeader;
public:
	Party(const std::vector<std::shared_ptr<PlayerCharacter>> & players);
	
	Party(const Party& p);


	virtual void add(std::shared_ptr<PlayerCharacter> character) override;



	/// \brief
	/// Awards experience distributed evenly between all members and returns a vector of characters who got double xp
	std::vector<std::pair<std::shared_ptr<PlayerCharacter>, bool>> addExperience(const int & exp);

	/// \brief
	/// Adds currency given amount
	void addCurrency(const int & currencyModifier);

	/// \brief
	/// Lowers currency by given amount
	void decreaseCurrency(const int & currencyModifier);

	/// \brief
	/// Returns current currency
	int getCurrency();


	void setCurrency(const int & money);

	/// \brief
	/// Returns party average stat
	int getAverageStat(const AbilityScores & stat);

	/// \brief
	/// sets Overworld Position to given value
	void setOverworldPosition(const int &);

	/// \brief
	/// Returns current Overworld Position
	unsigned int getOverworldPosition();

	std::vector<std::shared_ptr<Item> > getInventory();

	void setInventory(std::vector<std::shared_ptr<Item>>& inv);

	void addToInventory(const std::shared_ptr<Item> & item);

	void clearInventory();
	
	void eraseItem(std::shared_ptr<Item> i);


	std::shared_ptr<PlayerCharacter>* getPartyLeader();
	
	void setPartyLeader(std::shared_ptr<PlayerCharacter>* newLeader);

	void addWeapontoPartyMember(std::shared_ptr<PlayerCharacter> ,std::shared_ptr<Weapon> i);

	void addArmortoPartyMember(std::shared_ptr<PlayerCharacter>, std::shared_ptr<Armor> i);
};