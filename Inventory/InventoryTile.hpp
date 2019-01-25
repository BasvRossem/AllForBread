#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "../Items/Item.hpp"
#include "../virtualScreen/virtualScreen.hpp"
#include "../Items/Weapon.hpp"

class InventoryTile
{
private:
	sf::RectangleShape rect;
	sf::Font font;
	sf::Text text;
	std::shared_ptr<Item> item;
public:
	InventoryTile(std::shared_ptr<Item> item, const sf::Vector2f & position, const sf::Vector2f & size);
	void draw(sf::RenderWindow & window);
	void draw(VirtualScreen & vScreen);
	int getWeight();
	int getBaseValue();
	std::string getName();
	std::string getDescription();
	sf::Vector2f getSelectboxPosition();
	std::shared_ptr<Item> getItem();
};

