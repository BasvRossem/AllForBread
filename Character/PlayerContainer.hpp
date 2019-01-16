#pragma once
#include "CharacterContainer.hpp"
#include "PlayerCharacter.hpp"

template<int N>
class CharacterContainer<std::shared_ptr<PlayerCharacter>, N> {
public:
	CharacterContainer<std::shared_ptr<PlayerCharacter>, N>(std::vector<std::shared_ptr<PlayerCharacter>> chars) : 
		characters(chars)
	{};
};