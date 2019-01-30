#pragma once
#include <vector>
#include <memory>
#include "SFML/Graphics.hpp"
#include "Party.hpp"
#include "../Core/Tile.hpp"

class PartyOverview {
private:
	bool isOpen = false;
	BackGround & backGround;
	std::string surrounding;

	Party & party;
	std::shared_ptr<PlayerCharacter>* selected;
	std::vector<std::shared_ptr<Tile>> playerPortraitTiles;

	std::shared_ptr<sf::Texture> partyLeaderTexture;
	std::shared_ptr<sf::Texture> nonPartyLeaderTexture;
	std::shared_ptr<sf::Sprite> partyIconSprite;


	sf::Font font;

	void drawAllPlayerCharacters(sf::RenderWindow & window);
	void drawSelectedPlayerStats(sf::RenderWindow & window);
	void drawModifierBox();
	void drawProtectionStats();


	sf::Vector2u leftScreenSize = sf::Vector2u(500, 1040);
	sf::Vector2f characterScreenSize = sf::Vector2f(static_cast<float>(leftScreenSize.x), static_cast<float>((leftScreenSize.y - 40) / 4));
	VirtualScreen leftScreen;
	std::vector<std::shared_ptr<VirtualScreen>> leftScreens;

	sf::Vector2u rightScreenSize = sf::Vector2u(900, 1040);
	VirtualScreen rightScreen;

public:
	PartyOverview(Party & party, BackGround & backGround, const std::string & surrounding );

	void open(sf::RenderWindow & window);
};