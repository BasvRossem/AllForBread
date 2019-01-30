#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <functional>
#include "background.hpp"
#include "KeyboardHandler.hpp"
#include "Tile.hpp"

class Menu {
private:
	std::vector<std::shared_ptr<Tile>> tiles;
	sf::Vector2f size;
	sf::RectangleShape selectRectangle;
	BackGround backGround;
	std::string surroundings;
	unsigned int selectedID = 0;
public:
	Menu(std::string & surroundings, BackGround & backGround);
	void addTile(std::string & imageName, std::function<void()> & f);
	void update(sf::RenderWindow & window);
	void draw(sf::RenderWindow & window);
	void select();
	void selectChangePosition(const unsigned int & id);
};

