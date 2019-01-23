#pragma once
#include "Monster.hpp"
#include "CharacterContainer.hpp"
#include <memory>
#include <vector>
/// @file

/// \brief
/// A class that handles the storage of monster characters
/// This is a specialisation of the charactercontainer
class Mob : public CharacterContainer< std::shared_ptr<Monster>, 4> {
private:
	// Currently Empty

public:
	Mob(const std::vector<std::shared_ptr<Monster>> &);

	/// \brief
	///	Returns Mob total reward experience
	int getRewardExperience();
};