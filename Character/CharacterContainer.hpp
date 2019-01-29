#pragma once
#include "Character.hpp"
#include <memory>
#include <vector>
#include <iostream>
#include <stdexcept>
/// @file

/// \brief
/// Templates character base class for containing objects of class T.
template<typename T, unsigned int N = 4>
class CharacterContainer {
protected:
	std::vector<T> characters;
public:
	CharacterContainer(const std::vector<T> & characters) : characters(characters) {	};
	CharacterContainer(): characters(std::vector<T>()){};

	/// \brief
	/// Adds element T to internal container
	virtual void add(T character) {
		if (characters.size() < N) {
			characters.push_back(character);
		}
		else {
			std::cout << "Je probeert een character toe te voegen aan een volle container\n";
		}
	}

	/// \brief
	/// Adds a vector of T to internal container
	template<typename C>
	void add( C & additionalCharacters) {
		if (characters.size() + additionalCharacters.size() <= N) {
			for (unsigned int i = 0; i < additionalCharacters.size(); i++) {
				characters.push_back(additionalCharacters[i]);
			}
		}
	}

	/// \brief
	/// Allows access to internal container through [] at given index
	T &operator[](const unsigned int & index) {
		if (index < characters.size()) { // Not N, because the party might not be full
			return characters.at(index);
		}
		else {
			std::cout << "Je probeert een character te vinden die niet bestaat\n";
			throw std::out_of_range("Je probeert een character te vinden die niet bestaat");
		}
	}

	/// \brief
	/// Returns signed integer size of the container
	unsigned int size() {
		return characters.size();
	}

	/// \brief
	/// Returns the character at given index, and erases it from internal container
	T pop(const int & index) {
		if (index < N && index < characters.size()) {
			T tmpChar = characters[index];
			characters.erase(characters.begin() + index);
			return tmpChar;
		} else {
			throw std::out_of_range("Je probeert een character te poppen die niet bestaat.");
		}
	}
};