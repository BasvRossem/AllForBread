#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character.hpp"

class Battle {
private:
	
	std::vector<Character*> players;
	std::vector<Character*> monsters;

	std::vector<std::string> initiative; //Players and monsters

	std::string surroundings;
	sf::RenderWindow & window;

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::Clock clock;
	float deltaTime = 0.0f;
public:
	bool battleStarted = false;
	bool battleFinished = false;

	Battle(sf::RenderWindow & window, std::vector<Character*> & players, std::vector<Character*> & monsters, std::string & surroundings);
	~Battle();

	void start();
	void update();
	void Show();
	void Stop();
};