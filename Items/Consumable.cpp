#include "Consumable.hpp"

Consumable::Consumable():
	action([]() {})
{}

Consumable::Consumable(const std::function<void()> & func):
	action(func)
{}

int Consumable::getQuantityUses() {
	return quantityUses;
}

void Consumable::setQuantityUses(const int & uses) {
	if (uses >= 0) {
		quantityUses = uses;
	}
}

void Consumable::activate() {
	action();
}
