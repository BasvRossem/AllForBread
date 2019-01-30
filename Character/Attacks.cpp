#include "Attacks.hpp"

Attacks::Attacks(){
	attacksVector = { 
		{ "Mainhand",	WeaponSlots::mainhand,	5 },
		{ "Offhanded",  WeaponSlots::offhand,	3 },
		{ "Twohanded",	WeaponSlots::twohanded,	8 }
	};
}

bool Attacks::validIndex(const int & index) {
	return (index >= 0 && index < static_cast<signed int>(attacksVector.size()));
}

void Attacks::setName(const int & index, const std::string & string) {
	if (validIndex(index)) {
		std::get<0>(attacksVector[index]) = string;
	}
	std::cout << "Failed to set name of attacksVector index: " << index << "\n";
}

void Attacks::setWeaponSlot(const int & index, const WeaponSlots & slot) {
	if (validIndex(index)) {
		std::get<1>(attacksVector[index]) = slot;
	}
	std::cout << "Failed to set weaponslot of attacksVector index: " << index << "\n";
}

void Attacks::setDamage(const int & index, const int & value) {
	if (validIndex(index)) {
		std::get<2>(attacksVector[index]) = value;
	}
	std::cout << "Failed to set baseDamage of attacksVector index: " << index << "\n";
}

std::string Attacks::getName(const int & index) {
	if (validIndex(index)) {
		return std::get<0>(attacksVector[index]);
	}
	std::cout << "In function: getName - Invalid index, returned index 0 instead\n";
	return std::get<0>(attacksVector[0]);
}

WeaponSlots Attacks::getWeaponSlot(const int & index) {
	if (validIndex(index)) {
		return std::get<1>(attacksVector[index]);
	}
	std::cout << "In function: getWeaponSlot - Invalid index, returned index 0 instead\n";
	return std::get<1>(attacksVector[0]);
}

int Attacks::getBaseDamage(const int & index) {
	if (validIndex(index)) {
		return std::get<2>(attacksVector[index]);
	}
	std::cout << "In function: getBaseDamage - Invalid index, returned index 0 instead\n";
	return std::get<2>(attacksVector[0]);
}

std::vector<std::tuple<std::string, WeaponSlots, int>> Attacks::getAttacks() {
	return attacksVector;
}

std::tuple<std::string, WeaponSlots, int> Attacks::getAttackDefenition(const int & index) {
	if (validIndex(index)) {
		return attacksVector[index];
	}
	std::cout << "Failed to return tuple element from attacksVector from index: " << index << "\n";
	return attacksVector[0];
}