#include "InventoryTile.hpp"



InventoryTile::InventoryTile(std::shared_ptr<Item> item, const sf::Vector2f & position, const sf::Vector2f & size) :
	item(item)
{
	float outLine = 2;
	float spaceBetweenTiles = 5;

	rect.setPosition(sf::Vector2f{ position.x + outLine + spaceBetweenTiles, position.y + outLine + spaceBetweenTiles });
	rect.setSize(sf::Vector2f{ size.x - 2 * (outLine + spaceBetweenTiles), size.y - 2 * (outLine + spaceBetweenTiles) });
	rect.setFillColor(sf::Color(124, 79, 33));
	rect.setOutlineThickness(outLine);
	rect.setOutlineColor(sf::Color(102, 51, 0));

	font.loadFromFile("Assets/arial.ttf");
	text.setFont(font);
	text.setPosition(sf::Vector2f{ position.x + 10, position.y + size.y / 4 });
	text.setCharacterSize(int(size.y / 2));
	text.setFillColor(sf::Color::White);
	text.setOutlineThickness(1);
	text.setOutlineColor(sf::Color::Black);
	text.setString(item->getName());
}




void InventoryTile::draw(sf::RenderWindow & window) {
	window.draw(rect);
	window.draw(text);
}

void InventoryTile::draw(VirtualScreen & vScreen) {
	vScreen.drawSurfaceDraw(rect);
	vScreen.drawSurfaceDraw(text);
}


int InventoryTile::getWeight() {
	return item->getWeight();
}

int InventoryTile::getBaseValue() {
	return item->getBaseValue();
}

std::string InventoryTile::getName() {
	return item->getName();

}

std::string InventoryTile::getDescription() {
	return item->getDescription();
}

sf::Vector2f InventoryTile::getSelectboxPosition() {
	return sf::Vector2f{ rect.getPosition().x + (rect.getSize().x - 110) + 970, rect.getPosition().y + 23  };
}

sf::Vector2f InventoryTile::getSelectboxPositionMini() {
	return sf::Vector2f{ rect.getPosition().x + rect.getSize().x - 20 , rect.getPosition().y +23};
}


std::shared_ptr<Item> InventoryTile::getItem() {
	return item;
}

void InventoryTile::setColor(sf::Color color) {
	rect.setFillColor(color);
}

void InventoryTile::setBorderColor(sf::Color color) {
	rect.setOutlineColor(color);
}


