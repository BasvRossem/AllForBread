#include "Weapon.hpp"
#include <algorithm>
#include <iostream>

Weapon::Weapon() {

}

Weapon::Weapon(const WeaponSlots & slot, const std::pair<DamageTypes, int>& damage):
	weaponSlot(slot),
	primaryDamageEffect(damage)
{}

Weapon::~Weapon() {
	
}

const WeaponSlots Weapon::getWeaponSlot() const {
	return weaponSlot;
}

const std::pair<DamageTypes, int> Weapon::getPrimaryDamageEffect() const {
	return primaryDamageEffect;
}

const std::vector<std::pair<DamageTypes, int>> Weapon::getSecondaryDamageEffects() const {
	return secondaryDamageEffects;
}

void Weapon::setWeaponSlot(const WeaponSlots & newSlot) {
	weaponSlot = newSlot;
}

void Weapon::setPrimaryDamageEffect(const std::pair<DamageTypes, int> & newPrimaryDamageEffect) {
	primaryDamageEffect = newPrimaryDamageEffect;
}

void Weapon::setSecondaryDamageEffects(const std::vector<std::pair<DamageTypes, int>> & newSecondaryDamageEffects) {
	secondaryDamageEffects = newSecondaryDamageEffects;
}

void Weapon::addSecondaryDamageEffect(const std::pair<DamageTypes, int> & damage) {
	secondaryDamageEffects.push_back(damage);
}

std::vector<std::tuple<DamageTypes, int, const Weapon*>> Weapon::compareTo(const Weapon & otherWeapon) {
	std::vector<std::tuple<DamageTypes, int, const Weapon*>> differences;
	if (otherWeapon.getWeaponSlot() != weaponSlot) {
		//=======================================================
		// If the weaponslots are not the same, the comparison is impossible for now
		//=======================================================
		return differences;
	}


	if (otherWeapon.getPrimaryDamageEffect().first == primaryDamageEffect.first) {
		//=======================================================
		// Calculate the difference in primary damage, if the types are equal
		//=======================================================

		if (otherWeapon.getPrimaryDamageEffect().second != primaryDamageEffect.second) {
			std::tuple<DamageTypes, int, const Weapon*> primaryDifference;
			int highest = std::max(otherWeapon.getPrimaryDamageEffect().second, primaryDamageEffect.second);
			if (highest == primaryDamageEffect.second) {
				std::get<0>(primaryDifference) = primaryDamageEffect.first;
				std::get<1>(primaryDifference) = highest;
				std::get<2>(primaryDifference) = this;
			} else {
				std::get<0>(primaryDifference) = otherWeapon.getPrimaryDamageEffect().first;
				std::get<1>(primaryDifference) = highest;
				std::get<2>(primaryDifference) = &otherWeapon;
			}
			differences.push_back(primaryDifference);
		}
	} else {
		std::tuple<DamageTypes, int, const Weapon*> otherDamage;
		std::get<0>(otherDamage) = otherWeapon.getPrimaryDamageEffect().first;
		std::get<1>(otherDamage) = otherWeapon.getPrimaryDamageEffect().second;
		std::get<2>(otherDamage) = &otherWeapon;
		differences.push_back(otherDamage);
		std::tuple<DamageTypes, int, const Weapon*> myDamage;
		std::get<0>(myDamage) = primaryDamageEffect.first;
		std::get<1>(myDamage) = primaryDamageEffect.second;
		std::get<2>(myDamage) = this;
		differences.push_back(myDamage);
	}

	std::vector<DamageTypes> alreadyCompared;
	//=======================================================
	// Cycle through own secondary effects
	//=======================================================

	for (const auto & secondaryEffect : secondaryDamageEffects) {
		// Check if both weapons have the damagetype
		auto otherSecondaryEffects = otherWeapon.getSecondaryDamageEffects();
		auto found = std::find_if(
			otherSecondaryEffects.begin(),
			otherSecondaryEffects.end(),
			[&secondaryEffect](const std::pair<DamageTypes, int> & effect) {
			return effect.first == secondaryEffect.first;
		});

		if (found != otherSecondaryEffects.end()) {
			std::tuple<DamageTypes, int, const Weapon*> secondaryDifference;
			int highest = std::max(secondaryEffect.second, found->second);

			if (highest == secondaryEffect.second) {
				//this weapon has a higher modifier, so you lose something
				std::get<0>(secondaryDifference) = found->first;
				std::get<1>(secondaryDifference) = highest - found->second;
				std::get<2>(secondaryDifference) = this;
			} else {
				//other weapon has a higher modifier, so you gain something
				std::get<0>(secondaryDifference) = secondaryEffect.first;
				std::get<1>(secondaryDifference) = highest - secondaryEffect.second;
				std::get<2>(secondaryDifference) = &otherWeapon;
			}
			differences.push_back(secondaryDifference);
		} else {
			// not found on the other armor means you lose this property
			std::tuple<DamageTypes, int, const Weapon*> secondaryDifference;
			std::get<0>(secondaryDifference) = secondaryEffect.first;
			std::get<1>(secondaryDifference) = secondaryEffect.second;
			std::get<2>(secondaryDifference) = this;
			differences.push_back(secondaryDifference);
		}
	}

	//=======================================================
	// Cycle through other secondary effects
	//=======================================================
	for (const auto & secondaryOther : otherWeapon.getSecondaryDamageEffects()) {
		//Check if it is already compared to prevent double comparisons
		if (std::find(alreadyCompared.begin(), alreadyCompared.end(), secondaryOther.first) == alreadyCompared.end()) {

			// Check if both weapons have the damagetype
			auto found = std::find_if(
				secondaryDamageEffects.begin(),
				secondaryDamageEffects.end(),
				[&secondaryOther](const std::pair<DamageTypes, int> & effect) {
				return effect.first == secondaryOther.first;
			});

			if (found == secondaryDamageEffects.end()) {
				// If they don't you gain damage
				std::tuple<DamageTypes, int, const Weapon*> secondaryDifference;
				std::get<0>(secondaryDifference) = secondaryOther.first;
				std::get<1>(secondaryDifference) = secondaryOther.second;
				std::get<2>(secondaryDifference) = &otherWeapon;
				differences.push_back(secondaryDifference);

			}
		}
	}

	return differences;
}
