#pragma once
#include <unordered_map>
#include <functional>
#include "SFML/Graphics.hpp"


/// @file

/// \brief
/// A class to handle SFML keyboard keypresses. Each key can only be mapped once.
class KeyboardHandler {
private:
	std::unordered_map<sf::Keyboard::Key, std::function<void()>> keyMap;
	bool overrideKeys = false;
public:
	/// \brief
	/// Add a single keybind matched to a function.
	void addListener(const sf::Keyboard::Key &, const std::function<void()> &);

	/// \brief
	/// Add a vector of pairs consisting of a key and a std::function.
	void addListener(const std::vector < std::pair<sf::Keyboard::Key, std::function<void()>>> &);

	/// \brief
	/// Removes a listener if it exists.
	void removeListener(const sf::Keyboard::Key&);

	/// \brief
	/// Processes given key. If the key exists, the asociated function will be called.
	void processKey(const sf::Keyboard::Key &);

	/// \brief
	/// Sets the internal override boolean to given parameter. 
	/// If this parameter is true, new additions will override current listeners with the same key.
	/// If this parameter is false, new additions will not override current listeners with the same key.
	void setOverride(const bool &);


	/// \brief
	/// Checks if a key is already mapped to a function.
	/// Returns true if given key already maps to a function.
	/// Returns false if given key does not map to a function.
	bool checkKey(const sf::Keyboard::Key &);
};