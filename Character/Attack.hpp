#pragma once
#include <string>
#include <iostream>
#include "Action.hpp"

class Attack : public Action {
private:
	int ID;
	std::string name;
	unsigned int damage;
public:
	Attack(const std::string &, const unsigned int &);
	void activate(const std::string &, const std::string &) override;
	std::string getName() override;
};