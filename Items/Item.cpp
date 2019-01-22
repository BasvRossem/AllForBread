#include "Item.hpp"

int Item::getWeight() {
	return weight;
}

int Item::getBaseValue() {
	return baseValue;
}

void Item::setWeight(const int & newWeight) {
	if (newWeight >= 0) {
		weight = newWeight;
	}
}

void Item::setBaseValue(const int & newBaseValue) {
	if (newBaseValue >= 0) {
		baseValue = newBaseValue;
	}
}