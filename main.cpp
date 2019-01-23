#include <iostream>
#include <string>
#include "Items/Weapon.hpp"
#include "Character/PlayerCharacter.hpp"

int main( int argc, char *argv[] ){
	Weapon sword(WeaponSlots::twohanded, std::pair<DamageTypes, int>(DamageTypes::slashing, 6));
	PlayerCharacter anubis("Anubis, de simpele ziel", "Assets/AnubisIdle");
	
}
