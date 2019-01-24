#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>


class Tile{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	std::function<void()> function;
public:
	Tile(std::string & imageName, sf::Vector2f & position, sf::Vector2f & size, std::function<void()> & f);
	Tile(std::string & imageName, sf::Vector2f & position, sf::Vector2f & size);
	void activate();
	void draw(sf::RenderWindow & window);
	sf::FloatRect getGlobalBound();
};
