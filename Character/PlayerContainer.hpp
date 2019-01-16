#pragma once
#include "CharacterContainer.hpp"
#include "Player.hpp"

template<int N>
class CharacterContainer<PlayerCharacter, N> {
public:
	CharacterContainer<PlayerCharacter, N>(std::vector<T> characters) : CharacterContainer(characters) {};
};