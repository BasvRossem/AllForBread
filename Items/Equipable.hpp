#pragma once
#include "../Character/PlayerCharacter.hpp"
#include <memory>

class Equipable {
protected:
	PlayerCharacter * equipped; //Normal pointer because an equipable will never take ownership of a playercharacter
public:
	virtual void equip(PlayerCharacter * pc) = 0;
	virtual void unequip() = 0;
};

