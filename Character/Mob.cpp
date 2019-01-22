#include "Mob.hpp"

Mob::Mob(const std::vector<std::shared_ptr<Monster>> & monsters) :
	CharacterContainer<std::shared_ptr<Monster>, 4>(monsters) {
}

int Mob::getRewardExperience() {
	int totalExperience = 0;

	for (unsigned int i = 0; i < characters.size(); i++) {
		totalExperience += characters[i]->getRewardExperience();
	}

	return totalExperience;
}