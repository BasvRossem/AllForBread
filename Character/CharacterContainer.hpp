#pragma once
#include "Character.hpp"
#include <memory>
#include <vector>
#include <iostream>
#include <stdexcept>

template<typename T, int N = 4>
class CharacterContainer {
protected:
	std::vector<T> characters;
public:
	CharacterContainer(const std::vector<T> & characters) : characters(characters) {	};

	/// \brief
	/// Adds element T to internal container
	void add(T character) {
		if (characters.size < N) {
			characters.push_back(character);
		} else {
			std::cout << "Je probeert een character toe te voegen aan een volle container\n";
		}
	}

	/// \brief
	/// Allows access to internal container through []
	T &operator[](const unsigned int & index) {
		if (index < characters.size()) { // Not N, because the party might not be full
			return characters.at(index);
		} else {
			std::cout << "Je probeert een character te vinden die niet bestaat\n";
			throw std::out_of_range("blah");
		}
	}

	/// \brief
	/// dereferencing operator
	T operator*(T * objToDereference) {
		return &objToDereference;
	}

	/// \brief
	/// returns begin iterator from container
	T* begin() {
		return characters.begin();
	}

	/// \brief
	/// returns end iterator from container
	T* end() {
		return characters.end();
	}

	/// \brief
	/// Adds a vector of T to internal container
	void add(const std::vector<T> & additionalCharacters) {
		characters.insert(additionalCharacters);
	}

	/// \brief
	/// Returns signed integer size of the container
	int size() {
		return static_cast<int>(characters.size());
	}
};