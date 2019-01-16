#pragma once
#include "Character.hpp"
#include <memory>
#include <vector>
#include <iostream>

template<typename T, int N>
class CharacterContainer {
protected:
	std::vector<std::shared_ptr<T>> characters;
public:
	CharacterContainer(std::vector<std::shared_ptr<T>> characters) : characters(characters) {	};

	void add(std::shared_ptr<T> character) {
		if (characters.size < N) {
			characters.push_back(character);
		} else {
			std::cout << "Je probeert een character toe te voegen aan een volle container\n";
		}
	}
	std::shared_ptr<T> operator[](const int & index) {
		if (index < characters.size()) { // Not N, because the party might not be full
			return characters.at(index);
		} else {
			std::cout << "Je probeert een character te vinden die niet bestaat\n";
		}
	}
};