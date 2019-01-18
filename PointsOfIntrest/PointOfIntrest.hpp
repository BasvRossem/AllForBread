#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

class PointOfIntrest {
private:
	sf::CircleShape point;
	sf::Vector2f position;
	float size;
	std::string locationType;
	std::function<void(std::string)> function;
public:
	PointOfIntrest(const sf::Vector2f &position, const float &size, const sf::Color & color, const std::string &locationType, const std::function<void(std::string)> & function);
	void activate();
	void draw(sf::RenderWindow &window);
};
