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
	virtual ~Item();
	const int getWeight() const;
	const int getBaseValue() const;
	const std::string getName() const;
	const std::string getDescription() const;


	void setWeight(const int & newWeight);
	void setBaseValue(const int & newBaseValue);
	void setName(const std::string & newName);
	void setDescription(const std::string & newDescription);
};