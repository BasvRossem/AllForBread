#include "Inventory.hpp"

Inventory::Inventory():
	itemlist()
{
}

Inventory::Inventory(const std::pair<std::shared_ptr<Item>, int>& newItem):
	itemlist()
{
	itemlist.push_back(newItem);
}

Inventory::Inventory(const std::vector<std::pair<std::shared_ptr<Item>, int>>& newItemList):
	itemlist(newItemList)
{
}


void Inventory::addItem(std::shared_ptr<Item> item, const int& amount){
	if (item != nullptr && amount > 0) {
		itemlist.push_back(std::make_pair(item, amount));
	}
}

void Inventory::removeItem(const std::string& name, const int& amount){
	auto it = std::find_if(itemlist.begin(), itemlist.end(), [&name](const std::pair<std::shared_ptr<Item>, int>& val) {
		if (val.first->getName() == name) {
			return true;
		}
	});

	if (it != itemlist.end()) {
		if (it->second <= amount) {
			itemlist.erase(it);
		} else {
			it->second -= amount;
		}
	}

}