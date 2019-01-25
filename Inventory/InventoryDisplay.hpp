#pragma once
#include <iostream>
#include "../Character/Party.hpp"
#include "../Items/Consumable.hpp"
#include "../Items/Item.hpp"
#include <vector>
#include <SFML/Graphics.hpp>
#include "InventoryTile.hpp"
#include "playerInventoryTile.hpp"
#include "../Core/KeyboardHandler.hpp"

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
	//sf::Texture book;
	//sf::Sprite bookSprite;

	sf::Color halfTransparent = sf::Color(0, 0, 0, 125);
	sf::RectangleShape selectBox;
	std::pair<std::vector<std::shared_ptr<PlayerInventoryTile>>, std::vector<std::shared_ptr<InventoryTile>>> pTile;
	bool firstCollum = true;
	int i = 0;
	int selected = 4;

	KeyboardHandler keyHandler;
public:
	InventoryDisplay(Party & party, sf::RenderWindow & window);
	~InventoryDisplay();
	void use();
	void draw();
	void drawLeftScreen();
	void drawRightScreen();
	void del();
	void deletePlayerItem();
	void deleteItem();
	void select();
	void selectPlayer();
	void selectItem();

	void switchCollumSelectbox();
	void switchRowSelectbox(unsigned int index);
};