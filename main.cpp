#include <iostream>
#include <string>
#include "Items/Weapon.hpp"
#include "Character/PlayerCharacter.hpp"

std::string damageTypeText(const DamageTypes & type) {
	std::string toReturn;
	switch (type) {
	case DamageTypes::slashing:
		toReturn = "slashing";
		break;
	case DamageTypes::piercing:
		toReturn = "piercing";
		break;
	case DamageTypes::force:
		toReturn = "force";
		break;
	case DamageTypes::poison:
		toReturn = "poison";
		break;
	case DamageTypes::fire:
		toReturn = "fire";
		break;

	default:
		toReturn = "Generieke schade";
		break;
	}
	return toReturn;
}

std::string armorTypeText(const AbilityScores & slot) {
	std::string toReturn;
	switch (slot) {
	case AbilityScores::charisma:
		toReturn = "charisma";
		break;
	case AbilityScores::dexterity:
		toReturn = "dexterity";
		break;
	case AbilityScores::strength:
		toReturn = "dexterity";
		break;
	case AbilityScores::vitality:
		toReturn = "vitality";
		break;
	case AbilityScores::arcanism:
		toReturn = "arcanism";
		break;
	case AbilityScores::luck:
		toReturn = "luck";
		break;
	default:
		toReturn = "Generieke ability";
		break;
	}
	return toReturn;
}

int main( int argc, char *argv[] ){

	//=======================================================
	// Weapon testing
	//=======================================================
	
	Weapon zweihander(WeaponSlots::twohanded, std::pair<DamageTypes, int>(DamageTypes::slashing, 6));
	zweihander.addSecondaryDamageEffect(std::pair<DamageTypes, int>(DamageTypes::force, 3));
	zweihander.addSecondaryDamageEffect(std::pair<DamageTypes, int>(DamageTypes::fire, 3));
	zweihander.setName("Zweihander");
	
	Weapon dagger(WeaponSlots::twohanded, std::pair<DamageTypes, int>(DamageTypes::piercing, 2));
	dagger.addSecondaryDamageEffect(std::pair<DamageTypes, int>(DamageTypes::force, 4));
	dagger.addSecondaryDamageEffect(std::pair<DamageTypes, int>(DamageTypes::poison, 3));
	dagger.setName("Dagger");
	

	auto differences = zweihander.compareTo(dagger);
	std::cout << "Als je dagger equipped, volgen er de volgende verschillen.\n";

	for (auto & difference : differences) {
		if (std::get<2>(difference) == &zweihander) {
			std::cout << "Je verliest ";
		} else {
			std::cout << "Je krijgt ";
		}
		std::cout
			<< std::get<1>(difference)
			<< ' '
			<< damageTypeText(std::get<0>(difference))
			<< " schade!"
			<< '\n';
	}
	
	//=======================================================
	// Armor testing
	//=======================================================
	Armor chainmail(ArmorSlots::chestplate);
	chainmail.setName("Chainmail");
	chainmail.addPropertyModifier({ AbilityScores::charisma,	2 });
	chainmail.addPropertyModifier({ AbilityScores::strength,	4 });
	chainmail.addPropertyModifier({ AbilityScores::dexterity,	-2 });
	chainmail.addPropertyModifier({ AbilityScores::luck,		1 });
	chainmail.addPropertyModifier({ AbilityScores::vitality,	3 });
	Armor leather(ArmorSlots::chestplate);
	leather.setName("Leather chest armor +2");
	leather.addPropertyModifier({ AbilityScores::charisma,		1 });
	leather.addPropertyModifier({ AbilityScores::strength,		1 });
	leather.addPropertyModifier({ AbilityScores::dexterity,		5 });
	leather.addPropertyModifier({ AbilityScores::arcanism,		-1 });

	auto armorDifferences = chainmail.compareTo(leather);
	std::cout << "De volgende modifiers veranderen door het equippen van " << leather.getName() << '\n';
	for (auto & difference : armorDifferences) {
		if (std::get<1>(difference) < 0 ) {
			std::get<1>(difference) *= -1;
			if (std::get<2>(difference) == &chainmail) {
				std::cout << "Je krijgt ";
			} else {
				std::cout << "Je verliest ";
			}
		} else if(std::get<1>(difference) > 0){
			if (std::get<2>(difference) == &chainmail) {
				std::cout << "Je verliest ";
			} else {
				std::cout << "Je krijgt ";
			}
		} else {
			std::cout << "Er gebeurt iets?:";
		}
		std::cout << std::get<1>(difference)
			<< ' '
			<< armorTypeText(std::get<0>(difference))
			<< " ability!"
			<< '\n';
	}
}
