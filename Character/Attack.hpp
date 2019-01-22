#pragma once
#include <string>
#include <iostream>
#include <array>

class Attacks{
private:
	std::array<std::pair<std::string, int>,4> attacks;
	const int ID = 0;
	std::string name = "Attacks";
public:
	Attacks();
	void changeDamage(const unsigned int & id, const unsigned int & damage);
	std::pair<int, int> activate(const unsigned int & i);
	std::string getName();
	std::string getNameAttack(const unsigned int & i);
	unsigned int getModifier(const unsigned int & i);
	std::array<std::pair<std::string, int>, 4> getAttacks();
};