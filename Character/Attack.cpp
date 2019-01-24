#include "Attack.hpp"

Attacks::Attacks()
{
	attacks[0].first = "sword";
	attacks[1].first = "box";
	attacks[2].first = "normal attack";
	attacks[3].first = "special attack";
	for (auto & a : attacks) {
		a.second = 1;
	}
}

std::pair<int, int> Attacks::activate(const unsigned int & i) {
	
	return (std::pair<int, int>(ID, attacks[i].second));
}

std::string Attacks::getName() {
	return name;
}

std::string Attacks::getNameAttack(const unsigned int & i) {
	return attacks[i].first;
}


unsigned int Attacks::getModifier(const unsigned int & i) {
	return attacks[i].second;
}

std::array<std::pair<std::string, int>, 4> Attacks::getAttacks() {
	return attacks;
}