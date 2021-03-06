#include "EnumClasses.hpp"

const std::string EnumMethods::getAbilityScoreName(const AbilityScores & score) {
	switch (score) {
		case AbilityScores::vitality:
			return "Vitality";
			break;
		case AbilityScores::strength:
			return "Strength";
			break;
		case AbilityScores::dexterity:
			return "Dexterity";
			break;
		case AbilityScores::arcanism:
			return "Arcanism";
			break;
		case AbilityScores::charisma:
			return "Charisma";
			break;
		case AbilityScores::luck:
			return "Luck";
			break;
		default:
			return "";
			break;
	}

}

const std::string EnumMethods::getDamageTypeName(const DamageTypes & type) {

	switch (type) {
	case DamageTypes::piercing:
		return "Piercing";
		break;
	case DamageTypes::bludgeoning:
		return "Bludgeoning";
		break;
	case DamageTypes::slashing:
		return "Slashing";
		break;
	case DamageTypes::acid:
		return "Acid";
		break;
	case DamageTypes::frost:
		return "Frost";
		break;
	case DamageTypes::fire:
		return "Fire";
		break;
	case DamageTypes::force:
		return "Force";
		break;
	case DamageTypes::lightning:
		return "Lightning";
		break;
	case DamageTypes::necrotic:
		return "Necrotic";
		break;
	case DamageTypes::poison:
		return "Poison";
		break;
	case DamageTypes::psychic:
		return "Psychic";
		break;
	case DamageTypes::radiant:
		return "Radiant";
		break;
	case DamageTypes::thunder:
		return "Thunder";
		break;

	default:
		return "";
		break;
	}
}

const std::string EnumMethods::getArmorSlotName(const ArmorSlots & slot) {
	switch (slot) {
	case ArmorSlots::chestplate:
		return "Chestplate";
		break;
	
	case ArmorSlots::boots:
		return "Boots";
		break;

	case ArmorSlots::gauntlets:
		return "Gauntlets";
		break;

	case ArmorSlots::helmet:
		return "Helmet";
		break;

	case ArmorSlots::legs:
		return "Legs";
		break;

	case ArmorSlots::ring:
		return "Ring";
		break;

	default:
		return "";
		break;
	}
}

const std::string EnumMethods::getWeaponSlotName(const WeaponSlots & slot) {
	switch (slot) {
	case WeaponSlots::mainhand:
		return "Mainhand";
		break;

	case WeaponSlots::offhand:
		return "Offhand";
		break;

	case WeaponSlots::twohanded:
		return "Twohanded";
		break;

	default:
		return "";
		break;
	}
}

const sf::Color EnumMethods::getDamageTypeColor(const DamageTypes & type) {
	switch (type) {
		case DamageTypes::acid:
			return sf::Color(83, 204, 14);
		break;
		case DamageTypes::bludgeoning:
			return sf::Color(68, 70, 73);
		break;
		case DamageTypes::piercing:
			return sf::Color(68, 70, 73);
		break;
		case DamageTypes::slashing:
			return sf::Color(68, 70, 73);
		break;
		case DamageTypes::fire:
			return sf::Color(155, 36, 12);
		break;
		case DamageTypes::force:
			return sf::Color(127, 118, 49);
		break;
		case DamageTypes::frost:
			return sf::Color(45, 167, 181);
		break;
		case DamageTypes::lightning:
			return sf::Color(200, 209, 33);
		break;
		case DamageTypes::necrotic:
			return sf::Color(13, 51, 0);
		break;
		case DamageTypes::poison:
			return sf::Color(67, 249, 4);
		break;
		case DamageTypes::radiant:
			return sf::Color(235, 255, 107);
		break;
		case DamageTypes::thunder:
			return sf::Color(194, 197, 234);
		break;
		default:
			return sf::Color::Black;
		break;
	}


}
