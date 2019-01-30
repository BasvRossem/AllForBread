#include "Armor.hpp"
#include <algorithm>
#include <iostream>

Armor::Armor() {

}

Armor::Armor(const ArmorSlots & slot) :
	armorSlot(slot)
{}

Armor::~Armor() {
	
}

const ArmorSlots Armor::getArmorSlot() const {
	return armorSlot;
}

const int Armor::getPhysicalProtection() const {
	return physicalProtection;
}

const int Armor::getMagicalProtection() const {
	return magicalProtecton;
}

const std::vector<std::pair<AbilityScores, int>> Armor::getPropertyModifiers() const {
	return propertyModifiers;
}

void Armor::setArmorSlot(const ArmorSlots & slot) {
	armorSlot = slot;
}

void Armor::setPhysicalProtection(const int & newPhysicalProtection) {
	if (newPhysicalProtection >= 0) {
		physicalProtection = newPhysicalProtection;
	}
}

void Armor::setMagicalProtection(const int & newMagicalProtection) {
	if (newMagicalProtection >= 0) {
		magicalProtecton = newMagicalProtection;
	}
}

void Armor::setPropertyModifiers(const std::vector<std::pair<AbilityScores, int>>& newPropertyModifiers) {
	propertyModifiers = newPropertyModifiers;
}

void Armor::addPropertyModifier(const std::pair<AbilityScores, int>& propertyModifier) {
	propertyModifiers.push_back(propertyModifier);
}


std::vector<std::tuple<AbilityScores, int, const Armor*>> Armor::compareTo(const Armor & otherArmor) {
	std::vector<std::tuple<AbilityScores, int, const Armor*>> differences;
	if (otherArmor.getArmorSlot() != armorSlot) {
		//=======================================================
		// If the armorslot is not the same, the comparison is impossible for now
		//=======================================================
		return differences;
	}
	
	std::vector<AbilityScores> alreadyCompared;

	//=======================================================
	// Check own stats
	//=======================================================
	for (auto & abilityMods : propertyModifiers) {
		auto otherProperties = otherArmor.getPropertyModifiers();
		auto found = std::find_if(
			otherProperties.begin(),
			otherProperties.end(),
			[&abilityMods](auto propertyModifier) {
				return propertyModifier.first == abilityMods.first;
			}
		);

		if (found != otherProperties.end()) {
			if (std::find(alreadyCompared.begin(), alreadyCompared.end(), found->first) == alreadyCompared.end()) {
				alreadyCompared.push_back(found->first);

				int highestMod = std::max(found->second, abilityMods.second);

				std::tuple<AbilityScores, int, const Armor*> difference;
				std::get<0>(difference) = abilityMods.first;
				if (highestMod = abilityMods.second) {
					// Own armorpiece has highest propertymod, so you will lose something
					std::get<1>(difference) = highestMod - found->second;
					std::get<2>(difference) = this;
				} else {
					// Other armorpiece has highest propertymod, so you will gain something
					std::get<1>(difference) = highestMod - abilityMods.second;
					std::get<2>(difference) = &otherArmor;
				}
				differences.push_back(difference);
			}
		} else {
			// not found on the other armor means you lose this property
			std::tuple<AbilityScores, int, const Armor*> difference;
			std::get<0>(difference) = abilityMods.first;
			std::get<1>(difference) = abilityMods.second;
			std::get<2>(difference) = this;
			differences.push_back(difference);
		}
	}


	//=======================================================
	// Check other stats not already checked
	//=======================================================
	for (auto & otherAbilityMods : otherArmor.getPropertyModifiers()) {
		//stat hasn't been checked before
		if (std::find(alreadyCompared.begin(), alreadyCompared.end(), otherAbilityMods.first) == alreadyCompared.end()) {

			//Find the other property in this armor
			auto found = std::find_if(propertyModifiers.begin(), propertyModifiers.end(), [&otherAbilityMods](auto propertyModifier) {
				return propertyModifier.first == otherAbilityMods.first;
			});

			std::tuple<AbilityScores, int, const Armor*> propertyDifference;
			// Only add new comparisons that havend been compared before
			if (found == propertyModifiers.end()) {

				//If this armor doesn't have other property, it means you gain this property
				std::get<0>(propertyDifference) = otherAbilityMods.first;
				std::get<1>(propertyDifference) = otherAbilityMods.second;
				std::get<2>(propertyDifference) = &otherArmor;

			}
			differences.push_back(propertyDifference);
		}
	}

	return differences;
}