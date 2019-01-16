#pragma once
#include "Character.hpp"
#include <memory>
#include <vector>
#include <iostream>

template<typename T, int N>
class CharacterContainer {
protected:
	std::vector<T> characters;
public:
	CharacterContainer(std::vector<T> characters) : characters(characters) {	};

	void add(T character) {
		if (characters.size < N) {
			characters.push_back(character);
		} else {
			std::cout << "Je probeert een character toe te voegen aan een volle container\n";
		}
	}
	T &operator[](const unsigned int & index) {
		if (index < characters.size()) { // Not N, because the party might not be full
			return characters.at(index);
		} else {
			std::cout << "Je probeert een character te vinden die niet bestaat\n";
			return characters.at(0);
		}
	}
};