#pragma once
#include "Item.hpp"
#include <functional>

class Consumable : public Item {
private:
	std::function<void()> action;
	int quantityUses = 1;
public:
	Consumable();
	Consumable(const std::function<void()> & func);

	int getQuantityUses();
	void setQuantityUses(const int & uses);

	void setAction(const std::function<void()> & newAction);
	void activate();
};

