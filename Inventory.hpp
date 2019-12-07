#pragma once
#include <vector>
#include <algorithm>
#include "Items/Item.hpp"


class Inventory
{
private:
	std::vector<std::pair<std::shared_ptr<Item>, int>> itemlist;

public:
	Inventory();
	Inventory(const std::pair<std::shared_ptr<Item>, int>& newItem);
	Inventory(const std::vector<std::pair<std::shared_ptr<Item>, int>>& newItemList);

	void addItem(std::shared_ptr<Item> item, const int & amount);
	void removeItem(const std::string& name, const int& amount);
};

