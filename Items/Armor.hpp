#pragma once
#include <vector>
#include "Item.hpp"
#include "Equipable.hpp"
#include "../Character/EnumClasses.hpp"

class Armor : public Item, public Equipable {
private:
	ArmorSlots armorSlot;
	int physicalProtection;
	int magicalProtecton;
	std::vector<std::pair<AbilityScores, int>> propertyModifiers;
public:
	Armor(const ArmorSlots & slot);

	ArmorSlots getArmorSlot();
	int getPhysicalProtection();
	int getMagicalProtection();
	std::vector<std::pair<AbilityScores, int>> getPropertyModifiers();

	void setArmorSlot(const ArmorSlots & slot);
	void setPhysicalProtection(const int & newPhysicalProtection);
	void setMagicalProtection(const int & newMagicalProtection);
	void setPropertyModifiers(const std::vector<std::pair<AbilityScores, int>> & newPropertyModifiers);

	void addPropertyModifier(const std::pair<AbilityScores, int> & propertyModifier);

	// Inherited via Equipable
	virtual void equip(PlayerCharacter * pc) override;
	virtual void unequip() override;
};