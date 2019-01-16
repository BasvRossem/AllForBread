#pragma once
#include <unordered_map>
#include <functional>
#include "SFML/Graphics.hpp"


class KeyboardHandler {
private:
	std::unordered_map<sf::Keyboard::Key, std::function<void()>> keyMap;
public:
	void addListener(sf::Keyboard::Key, )
};