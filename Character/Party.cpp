#include "Party.hpp"

Party::Party(const std::vector<std::shared_ptr<PlayerCharacter>> & players) :
	CharacterContainer<std::shared_ptr<PlayerCharacter>, 4>(players) {
};

void Party::addExperience(const int & exp) {
	int splitExp = static_cast<int>(exp / this->characters.size());
	for (auto p : this->characters) {
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

void Party::setOverworldPosition(const int & position) {
	overworldPosition = position;
}

int Party::getOverworldPosition() {
	return overworldPosition;
}