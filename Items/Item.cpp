#include "Item.hpp"

Item::Item() :
	name(std::string()),
	description(std::string())
{}

Item::~Item() {

}

const int Item::getWeight() const {
	return weight;
}

const int Item::getBaseValue() const {
	return baseValue;
}

const std::string Item::getName() const {
	return name;
}

const std::string Item::getDescription() const {
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