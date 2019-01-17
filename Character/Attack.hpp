#pragma once
#include <string>
#include <iostream>
#include "Action.hpp"

class Attack : public Action {
private:
	const int ID = 1;
	std::string name;
	unsigned int damage;
public:
	Attack(const std::string &, const unsigned int &);
	std::pair<int, int> activate();
	std::string getName() override;
};