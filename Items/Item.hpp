#pragma once
class Item {
private:
	int weight = 0;
	int baseValue = 0;
public:

	int getWeight();
	int getBaseValue();
	void setWeight(const int & newWeight);
	void setBaseValue(const int & newBaseValue);
};

