#pragma once
#include <vector>
#include <memory>
#include "SFML/Graphics.hpp"
#include "Party.hpp"
#include "../Core/Tile.hpp"

class PartyOverview {
private:
	bool isOpen = false;

	Party party;
	std::shared_ptr<PlayerCharacter> selected;
	std::vector<std::shared_ptr<Tile>> playerPortraitTiles;

	void drawAllPlayerCharacters(sf::RenderWindow & window);
	void drawSelectedPlayerStats();

	sf::Vector2u leftScreenSize = sf::Vector2u(500, 1040);
	VirtualScreen leftScreen;
	std::vector<std::shared_ptr<VirtualScreen>> leftScreens;
	sf::Vector2u characterWindowSize = sf::Vector2u(500, 220);

	sf::Vector2u rightScreenSize = sf::Vector2u(500, 1040);
	VirtualScreen rightScreen;
public:
	PartyOverview(Party & party);

	void open(sf::RenderWindow & window);
	void close();
};