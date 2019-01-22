#pragma once
#include "Equipable.hpp"
#include "Item.hpp"
#include "../Character/EnumClasses.hpp"
#include <utility>
#include <vector>

class Weapon : public Item, public Equipable {
private:
	WeaponSlots weaponSlot;
	std::pair<DamageTypes, int> primaryDamageEffect;
	std::vector<std::pair<DamageTypes, int>> secondaryDamageEffects;
public:
	Weapon(const WeaponSlots & slot, const std::pair<DamageTypes, int> & damage);

	WeaponSlots getWeaponSlot();
	std::pair<DamageTypes, int> getPrimaryDamageEffect();
	std::vector<std::pair<DamageTypes, int>> getSecondaryDamageEffects();

	void setWeaponSlot(const WeaponSlots & newSlot);
	void setPrimaryDamageEffect(const std::pair<DamageTypes, int> & newPrimaryDamageEffect);
	void setSecondaryDamageEffects(const std::vector<std::pair<DamageTypes, int>> & newSecondaryDamageEffects);

	void addSecondaryDamageEffect(const std::pair<DamageTypes, int> & damage);

	virtual void equip(PlayerCharacter * pc) override;
	virtual void unequip() override;
};

