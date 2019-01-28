#pragma once
#include <SFML/Graphics.hpp>
<<<<<<< HEAD
#include "../virtualScreen/virtualScreen.hpp"
=======
>>>>>>> 26e74fc4f29028a33835e8492b38ef346ba68011
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
	void draw(VirtualScreen & vScreen);
	
	sf::FloatRect getGlobalBound();
};
