#pragma once
#include <string>
class Action {
	int counter;
public:
	virtual void activate(const std::string &, const std::string &) {};
	virtual std::string  getName() { return ""; };
};
