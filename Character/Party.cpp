#include "Party.hpp"

Party::Party(const std::vector<std::shared_ptr<PlayerCharacter>> & players) :
	CharacterContainer<std::shared_ptr<PlayerCharacter>, 4>(players) {
};

std::vector<std::pair<std::shared_ptr<PlayerCharacter>, bool>> Party::addExperience(const int & exp) {
	int splitExp = static_cast<int>(exp / characters.size());
	std::vector<std::pair<std::shared_ptr<PlayerCharacter>, bool>> luckyBastards;

	for (auto p : characters) {
		if (p->checkLuckStat()) {
			luckyBastards.push_back({ p, true });
			p->increaseExperience(splitExp * 2);

		} else {
			luckyBastards.push_back({ p, false });
			p->increaseExperience(splitExp);

		}
	}
	return luckyBastards;
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

int Party::getAverageStat(const AbilityScores & stat) {
	int totalStat = 0;

	for (auto p : characters) {
		totalStat += p->getStat(stat);
	}

	return static_cast<int>(totalStat / characters.size());
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

void Party::addToInventory(const std::shared_ptr<Item>& item){
	inventory.push_back(item);
}

void Party::eraseItem(std::shared_ptr<Item> i) {
	inventory.erase(std::remove(inventory.begin(), inventory.end(), i), inventory.end());
}