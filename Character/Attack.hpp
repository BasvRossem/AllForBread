#pragma once
#include <string>
#include <iostream>
#include "Action.hpp"

class Attack : public Action {
private:
	const int ID = 0;
	std::string name;
	unsigned int damage;
public:
	Attack(const std::string & name, const unsigned int & damage);
	std::pair<int, int> activate();
	std::string getName() override;
	unsigned int getModifier();
};