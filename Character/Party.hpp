#pragma once
#include "PlayerCharacter.hpp"
#include "CharacterContainer.hpp"
#include <memory>
#include <vector>


class Party : public CharacterContainer< std::shared_ptr<PlayerCharacter>, 4> {
private:
	int currency = 0;

public:
	Party(std::vector<std::shared_ptr<PlayerCharacter>> players):
		CharacterContainer<std::shared_ptr<PlayerCharacter>, 4>(players)
	{};

	void addExperience(const int & exp) {
		int splitExp = static_cast<int>(exp / this->characters.size());
		for (auto p : this->characters) {
			p->increaseExperience(splitExp);
		}
	}

	void addCurrency(const int & currencyModifier) {
		if (currencyModifier < 0) {
			std::cout << "Je probeert currency te verhogen met een negatieve waarde\n";
		} else {
			currency += currencyModifier;
		}
	}

};