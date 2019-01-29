#include "Party.hpp"

Party::Party(const std::vector<std::shared_ptr<PlayerCharacter>> & players) :
	CharacterContainer<std::shared_ptr<PlayerCharacter>, 4>(players) {
};

void Party::addExperience(const int & exp) {
	int splitExp = static_cast<int>(exp / characters.size());
	for (auto p : characters) {
		p->increaseExperience(splitExp);
	}
}

void Party::addCurrency(const int & currencyModifier) {
	if (currencyModifier < 0) {
		std::cout << "Je probeert currency te verhogen met een negatieve waarde\n";
	} else {
		currency += currencyModifier;
	}
}

void Party::decreaseCurrency(const int & currencyModifier) {
	if (currencyModifier < 0) {
		std::cout << "Je probeert currency te verlagen met een negatieve waarde\n";
	} else {
		if (currencyModifier > currency) {
			currency = 0;
		} else {
			currency -= currencyModifier;
		}
	}
}

int Party::getCurrency() {
	return currency;
}

void Party::setCurrency(const int & money) {
	currency = money;
}

void Party::setOverworldPosition(const int & position) {
	overworldPosition = position;
}

int Party::getOverworldPosition() {
	return overworldPosition;
}

std::vector<std::shared_ptr<Item>> Party::getInventory(){
	return inventory;
}

void Party::setInventory(std::vector<std::shared_ptr<Item>>& inv)
{
	inventory = inv;
}

void Party::addToInventory(const std::shared_ptr<Item>& item){
	inventory.push_back(item);
}

void Party::clearInventory() {
	inventory.clear();
}

void Party::eraseItem(std::shared_ptr<Item> i) {
	inventory.erase(std::remove(inventory.begin(), inventory.end(), i), inventory.end());
}