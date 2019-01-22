#pragma once
#include "Item.hpp"
#include "../Character/EnumClasses.hpp"
#include <vector>

class Armor : public Item {
private:
	ArmorSlots armorSlot;
	int physicalProtection;
	int magicalProtecton;
	std::vector<std::pair<AbilityScores, int>> propertyModifiers;
public:
	Armor();
	~Armor();
};