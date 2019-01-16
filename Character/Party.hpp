#pragma once
#include "PlayerCharacter.hpp"
#include "PlayerContainer.hpp"
#include <memory>
#include <vector>

template<int N = 4>
class Party : public CharacterContainer<std::shared_ptr<PlayerCharacter>, N> {
private:
	int currency = 0;

public:
	Party(const std::vector<std::shared_ptr<PlayerCharacter>> players):
		CharacterContainer<std::shared_ptr<PlayerCharacter>, N>(players){
	};

	void addExperience(const int & exp) {
		int splitExp = static_cast<int>(exp / this->characters.size());
		for (std::shared_ptr<PlayerCharacter> p : this->characters) {
			p->increaseExperience(splitExp);
		}
	}

	void addCurrency(const int & currencyModifier) {
		if (currencyModifier < 0) {
			std::cout << "Je probeert currency te verhogen met een negatieve waarde\n";
		}
	}

};