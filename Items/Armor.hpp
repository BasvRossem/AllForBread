#pragma once
#include <vector>
#include "Item.hpp"
#include "../Character/EnumClasses.hpp"

class Armor : public Item {
private:
	ArmorSlots armorSlot = ArmorSlots::chestplate;
	int physicalProtection;
	int magicalProtecton;
	std::vector<std::pair<AbilityScores, int>> propertyModifiers;
public:
	Armor();
	Armor(const ArmorSlots & slot);

	const ArmorSlots getArmorSlot() const;
	const int getPhysicalProtection() const;
	const int getMagicalProtection() const;
	const std::vector<std::pair<AbilityScores, int>> getPropertyModifiers() const;

	void setArmorSlot(const ArmorSlots & slot);
	void setPhysicalProtection(const int & newPhysicalProtection);
	void setMagicalProtection(const int & newMagicalProtection);
	void setPropertyModifiers(const std::vector<std::pair<AbilityScores, int>> & newPropertyModifiers);

	void addPropertyModifier(const std::pair<AbilityScores, int> & propertyModifier);
};