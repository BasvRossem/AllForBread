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

	/// \brief
	/// This function draws a Tile on a window
	void draw(sf::RenderWindow & window);

	/// \brief
	/// This function draws a Tile on a VirtualScreen
	void draw(VirtualScreen & vScreen);

	/// \brief
	/// This function gets the weight of a item inside the Tile
	int getWeight();

	/// \brief
	/// This function gets the baseValue of a item inside the Tile
	int getBaseValue();

	/// \brief
	/// With this function you can set the color of a tile.
	void setColor(sf::Color color);

	/// \brief
	/// With this function you can set the outline color.
	void setBorderColor(sf::Color color);

	/// \brief
	/// This function gets the name of a item inside the Tile.
	std::string getName();

	/// \brief
	/// This function gets the description of a item inside the Tile.
	std::string getDescription();

	/// \brief
	/// This function gets the postion of a normal size Tile for the selectbox.
	sf::Vector2f getSelectboxPosition();

	/// \brief
	/// This function gets the postion of a mini size Tile for the selectbox.
	sf::Vector2f getSelectboxPositionMini();

	/// \brief
	/// This function gets the shared_ptr from the item inside the Tile.
	std::shared_ptr<Item> getItem();
};

