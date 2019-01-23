#include "Armor.hpp"

Armor::Armor() {

}

Armor::Armor(const ArmorSlots & slot) :
	armorSlot(slot)
{}

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