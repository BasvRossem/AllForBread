#pragma once
#include "Item.hpp"
#include "../Character/EnumClasses.hpp"
#include <utility>
#include <vector>

class Weapon : public Item {
	WeaponSlots weaponSlot;
	std::pair<DamageTypes, int> primaryDamageEffect;
	std::vector<std::pair<DamageTypes, int>> secondaryDamageEffects;
public:
	Weapon();
	~Weapon();
};

