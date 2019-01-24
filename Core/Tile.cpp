#include "Tile.hpp"



Tile::Tile(std::string & imageName, sf::Vector2f & position, sf::Vector2f & size, std::function<void()> & f) :
	function(f)
{
	if (texture.loadFromFile(imageName)) {
		sf::Vector2f sizeImage = sf::Vector2f{ texture.getSize() };
		sprite.setTexture(texture);
		sprite.setPosition(position);
		sprite.setScale(sf::Vector2f{ size.x / sizeImage.x, size.y / sizeImage.y });
	}
}

Tile::Tile(std::string & imageName, sf::Vector2f & position, sf::Vector2f & size)
{
	if (texture.loadFromFile(imageName)) {
		sf::Vector2f sizeImage = sf::Vector2f{ texture.getSize() };
		sprite.setTexture(texture);
		sprite.setPosition(position);
		sprite.setScale(sf::Vector2f{ size.x / sizeImage.x, size.y / sizeImage.y });
	}
}

void Tile::activate() {
	function();
}

void Tile::draw(sf::RenderWindow & window) {
	window.draw(sprite);
}

sf::FloatRect Tile::getGlobalBound() {
	return sprite.getGlobalBounds();
}
