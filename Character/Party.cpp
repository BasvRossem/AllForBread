#include "Party.hpp"
#include <typeinfo>


Party::Party(const std::vector<std::shared_ptr<PlayerCharacter>> & players) :
	CharacterContainer<std::shared_ptr<PlayerCharacter>, 4>(players) {
	if (characters.size() > 0) {
		partyLeader = &characters[0];
	}
}

Party::Party(const Party & p):
	Party(p.characters)
{}

void Party::add(std::shared_ptr<PlayerCharacter> character) {
	CharacterContainer< std::shared_ptr<PlayerCharacter>, 4>::add(character);
	if (characters.size() == 1) {
		partyLeader = &characters[0];
	}
	
}

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


void Party::setCurrency(const int & money) {
	currency = money;
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

unsigned int Party::getOverworldPosition() {
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

std::shared_ptr<PlayerCharacter>* Party::getPartyLeader() {
	return partyLeader;
}

void Party::setPartyLeader(std::shared_ptr<PlayerCharacter>* newLeader) {
	if (newLeader != nullptr) {
		partyLeader = newLeader;
	}
}

void Party::addWeapontoPartyMember(std::shared_ptr<PlayerCharacter> c, std::shared_ptr<Weapon> w) {
	c->setWeapon(w->getWeaponSlot(), *w);
}


void Party::addArmortoPartyMember(std::shared_ptr<PlayerCharacter> c, std::shared_ptr<Armor> a) {
	c->setArmor(a->getArmorSlot(), *a);
}