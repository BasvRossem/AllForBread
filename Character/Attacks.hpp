#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "EnumClasses.hpp"
#include <tuple>

class Attacks {
private:
	std::vector<std::tuple<std::string, WeaponSlots, int>> attacksVector;

	bool validIndex(const int & index);

public:
	Attacks();

	/// \brief
	/// Sets the name of the given index' attack
	void setName(const int & index, const std::string & string);

	/// \brief
	/// Sets the weapon slot of the given index' attack
	void setWeaponSlot(const int & index, const WeaponSlots & slot);

	/// \brief
	/// Sets the damage of the given index' attack
	void setDamage(const int & index, const int & value);

	/// \brief
	/// Returns the name of the given index' attack
	std::string getName(const int & index);

	/// \brief
	/// Returns the weaponslot of the given index' attack
	WeaponSlots getWeaponSlot(const int & index);

	/// \brief
	/// Returns the baseDamage of the given index' attack
	int getBaseDamage(const int & index);

	/// \brief
	/// Returns a vector of all the current attacks
	std::vector<std::tuple<std::string, WeaponSlots, int>> getAttacks();

	/// \brief
	/// Returns a single element from the attacksVector
	std::tuple<std::string, WeaponSlots, int> getAttackDefenition(const int & index);
};