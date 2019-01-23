#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "PointsOfInterest/PointOfInterest.hpp"
#include "PointsOfInterest/pointOfInterestContainer.hpp"
#include "core/background.hpp"
#include "TransformableMovement/TransformableMovement.hpp"
#include "Core/KeyboardHandler.hpp"
#include "Character/Party.hpp"
#include "states/Combat.hpp"
#include "dataManager/DataManager.hpp"
#include <map>
#include "Items/Weapon.hpp"
#include "Character/PlayerCharacter.hpp"

int main( int argc, char *argv[] ){
	Weapon sword(WeaponSlots::twohanded, std::pair<DamageTypes, int>(DamageTypes::slashing, 6));
	PlayerCharacter anubis("Anubis, de simpele ziel", "Assets/AnubisIdle");
	
}
