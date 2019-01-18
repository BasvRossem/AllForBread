#include "KeyboardHandler.hpp"

void KeyboardHandler::addListener(const sf::Keyboard::Key & k, const std::function<void()>& action) {
	if (overrideKeys) {
		keyMap[k] = action;
	} else {
		//Check if key doesn't exist in map
		if (keyMap.find(k) == keyMap.end()) {
			keyMap[k] = action;
		}
	}
}
void KeyboardHandler::addListener(const std::vector<std::pair<sf::Keyboard::Key, std::function<void()>>> & binds) {
	for (const std::pair < sf::Keyboard::Key, std::function<void()>> & binding : binds) {
		addListener(binding.first, binding.second);
	}
}

void KeyboardHandler::removeListener(const sf::Keyboard::Key & k) {
	if (keyMap.find(k) != keyMap.end()) {
		keyMap.erase(k);
	}
}

void KeyboardHandler::processKey(const sf::Keyboard::Key & k) {
	if (sf::Keyboard::isKeyPressed(k) && (keyMap.find(k) != keyMap.end())) {
		keyMap[k]();
	}
}

void KeyboardHandler::setOverride(const bool & b) {
	overrideKeys = b;
}

bool KeyboardHandler::checkKey(const sf::Keyboard::Key & k) {
	return (keyMap.find(k) != keyMap.end());
}