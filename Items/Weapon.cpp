#include "Weapon.hpp"

Weapon::Weapon() {

}

Weapon::Weapon(const WeaponSlots & slot, const std::pair<DamageTypes, int>& damage):
	weaponSlot(slot),
	primaryDamageEffect(damage)
{}

WeaponSlots Weapon::getWeaponSlot() {
	return weaponSlot;
}

std::pair<DamageTypes, int> Weapon::getPrimaryDamageEffect() {
	return primaryDamageEffect;
}

std::vector<std::pair<DamageTypes, int>> Weapon::getSecondaryDamageEffects() {
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