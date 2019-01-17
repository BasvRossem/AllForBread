#include "Attack.hpp"



Attack::Attack(const std::string & name, const unsigned int & damage) :
	name(name),
	damage(damage)
{}


void Attack::activate(const std::string & playername, const std::string & enemy) {
	std::cout << playername << " sla "<< enemy <<"  voor " << damage <<std::endl;
}

std::string Attack::getName() {
	return name;
}