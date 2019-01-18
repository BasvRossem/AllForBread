#pragma once
#include <string>


class Action {
public:
	virtual std::pair<int, int> activate() = 0;
	virtual std::string  getName() = 0;
	virtual unsigned int getModifier() = 0;
};
