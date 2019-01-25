#pragma once
#include "Item.hpp"
#include "../Character/EnumClasses.hpp"
#include <utility>
#include <vector>
#include <tuple>

class Weapon : public Item {
private:
	WeaponSlots weaponSlot = WeaponSlots::mainhand;
	std::pair<DamageTypes, int> primaryDamageEffect;
	std::vector<std::pair<DamageTypes, int>> secondaryDamageEffects;
public:
	Weapon();
	Weapon(const WeaponSlots & slot, const std::pair<DamageTypes, int> & damage);
	virtual ~Weapon() override;

	const WeaponSlots getWeaponSlot() const;
	const std::pair<DamageTypes, int> getPrimaryDamageEffect() const;
	const std::vector<std::pair<DamageTypes, int>> getSecondaryDamageEffects() const;

	void setWeaponSlot(const WeaponSlots & newSlot);
	void setPrimaryDamageEffect(const std::pair<DamageTypes, int> & newPrimaryDamageEffect);
	void setSecondaryDamageEffects(const std::vector<std::pair<DamageTypes, int>> & newSecondaryDamageEffects);

	void addSecondaryDamageEffect(const std::pair<DamageTypes, int> & damage);

	std::vector<std::tuple<DamageTypes, int, const Weapon*>> compareTo(const Weapon & otherWeapon);
};

