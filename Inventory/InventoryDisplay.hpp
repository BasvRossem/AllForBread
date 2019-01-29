#pragma once
#include <iostream>
#include <functional>
#include "../Character/Party.hpp"
#include "../Items/Consumable.hpp"
#include "../Items/Item.hpp"
#include <vector>
#include <SFML/Graphics.hpp>
#include "InventoryTile.hpp"
#include "playerInventoryTile.hpp"
#include "../Core/KeyboardHandler.hpp"


/// \brief
/// A class that handles the inventory display.
class InventoryDisplay{
private:
	bool isOpen = false;

	std::shared_ptr<Consumable> itemToUse = nullptr;
	Party & party;

	sf::RenderWindow & window;
	sf::Vector2u leftScreenSize = sf::Vector2u(930, 1040);
	sf::Vector2u rightScreenSize = sf::Vector2u(930, 1040);
	VirtualScreen leftScreen;
	VirtualScreen rightScreen;

	sf::Texture takatiki;
	sf::Sprite background;

	sf::Color halfTransparent = sf::Color(0, 0, 0, 125);
	sf::RectangleShape selectBox;
	std::pair<std::vector<std::shared_ptr<PlayerInventoryTile>>, std::vector<std::shared_ptr<InventoryTile>>> pTile;

	std::pair<int, int> selected;
	std::pair<int, int> lastSelected;

	KeyboardHandler keyHandler;

	sf::Font font;
	sf::Text text;
public:
	InventoryDisplay(Party & party, sf::RenderWindow & window);
	~InventoryDisplay();

	/// \brief
	/// This function opens the inventory screen.
	void use();

	/// \brief
	/// This function draws the inventory.
	void draw();

	/// \brief
	/// This function draws the left part.
	void drawLeftScreen();

	/// \brief
	/// This function draws the right part.
	void drawRightScreen();

	/// \brief
	/// With this function you can delete a item form the player his inventory.
	/// It requires a index of the item tile in the vector pTiles.second.
	void deleteItem(const int & i);

	/// \brief
	/// With this function you can select a tile from the pTile pair.
	/// It requires a index of the collum and row.
	/// if you want to select a character item it needs a character index from the pTile.first vector.
	void changeSelected(const int x, const int y, const int &character = 4);

	/// \brief
	/// With this function you can select a Living tile. 
	/// It requires a index of the collum.
	/// if you want to select a character item it needs a character index from the pTile.first vector.
	void setZeroSelected(const int & collum, const int &character  =4);

	/// \brief
	/// With this function you can change the collor of a Tile.
	/// It requires a index of the collum and row.
	void select(const int & collom, const int & row);

	/// \brief
	/// With this function you can add a item from the itemlist to a character.
	/// It requires a index of the character index from pTile.first and item index form pTile.second.
	/// if it is a Weapon or Armor it will add the item to the character and delete it from the party inventory.
	/// if it isn't a Weapon or Armor it won't do anything.
	void addItemToCharacter(const int & character , const int & item);

	/// \brief
	/// With this function you can remove a item from the character and add it to the party inventory.
	/// It requires a character index from pTile.first, item colom index form a character and a item row index form a character.
	void removeItemFromCharacer(const int & character, int & collom, const int & row);

	/// \brief
	/// This function delets the tiles and add a updated version to the pTile.
	void reloadTiles();

	/// \brief
	/// With this function you can use a consumable and add it to the private.
	/// It requires a index of the items that u wil consume in pTile.second
	/// If it is a consumble it will set it to the private usedItem and delete the item form the pTile.second
	/// If it isn't a consumble it won't do anything and the usedItem will stay a null_ptr
	void useItem(const unsigned int & row);

	/// \brief
	/// With this function you can use a get the private usedItem.
	/// It will always return a pointer. 
	/// After retuning it will set the usedItem pointer to null_ptr
	std::shared_ptr<Consumable> getUsedItem();
};