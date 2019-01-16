#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "State.hpp"
#include "Character.hpp"

class Combat : public State {
private:
	
	std::vector<Character*> players;
	std::vector<Character*> monsters;

	std::vector<std::string> initiative; //Players and monsters

	std::string surroundings;

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::Clock clock;
	float deltaTime = 0.0f;
public:
	bool CombatStarted = false;
	bool CombatFinished = false;

	Combat(sf::RenderWindow & window, std::vector<Character*> & players, std::vector<Character*> & monsters, std::string & surroundings);
	~Combat();

	void start();
	virtual State update();
	void Show();
	void Stop();
};