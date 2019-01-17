#pragma once
#include <string>


class Action {
public:
	virtual std::pair<int, int> activate() { return std::pair<int,int>(0,0); };
	virtual std::string  getName() { return ""; };
};
