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
