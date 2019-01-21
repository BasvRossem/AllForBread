#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include <iostream>
#include "../states/State.hpp"
class PointOfInterest {
private:
	sf::CircleShape point;
	sf::Vector2f position;
	float size;
	std::string locationType;
	std::function<void()> function;
	std::vector<sf::Vector2f> path;

public:
	PointOfInterest(const sf::Vector2f &position, const float &size, const sf::Color & color, const std::string &locationType, const std::function<void()> & function, std::vector<sf::Vector2f> forward);
	void activate();
	void draw(sf::RenderWindow &window);
	sf::Vector2f getPosition();
	std::vector<sf::Vector2f> getPath();

};
