#pragma once
#include <string>

class Item {
private:
	int weight = 0;
	int baseValue = 0;
	std::string name;
	std::string description;
public:
	Item();

	int getWeight();
	int getBaseValue();
	std::string getName();
	std::string getDescription();


	void setWeight(const int & newWeight);
	void setBaseValue(const int & newBaseValue);
	void setName(const std::string & newName);
	void setDescription(const std::string & newDescription);
};