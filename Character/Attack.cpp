#include "Attack.hpp"



Attack::Attack(const std::string & name, const unsigned int & damage) :
	name(name),
	damage(damage)
{}


std::pair<int, int> Attack::activate() {
	return (std::pair<int, int>(ID, damage));
}

std::string Attack::getName() {
	return name;
}
