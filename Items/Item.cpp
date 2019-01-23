#include "Item.hpp"

Item::Item() :
	name(std::string()),
	description(std::string())
{}

int Item::getWeight() {
	return weight;
}

int Item::getBaseValue() {
	return baseValue;
}

std::string Item::getName() {
	return name;
}

std::string Item::getDescription() {
	return description;
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

void Item::setName(const std::string & newName) {
	name = newName;
}

void Item::setDescription(const std::string & newDescription) {
	description = newDescription;
}