#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "State.hpp"
#include "../Character/Party.hpp"
#include "../virtualScreen/virtualScreen.hpp"

class Combat : public State {
private:
	
	Party party;
	CharacterContainer<Character> monsters;
	sf::Vector2i animationScreenSize = sf::Vector2i(1920, 680);
	sf::Vector2i menuScreenSize = sf::Vector2i(1920, 450);
	VirtualScreen animationScreen;
	VirtualScreen menuScreen;
	std::vector<std::shared_ptr<Character>> initiative; //Players and monsters

	std::string surroundings;

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::Clock clock;
	float deltaTime = 0.0f;
public:
	bool CombatStarted = false;
	bool CombatFinished = false;

	Combat(sf::RenderWindow & window, Party & party, CharacterContainer<Character> & monster, std::string surrounding);
	~Combat();

	void start();
	virtual State* update();
	void draw();
	void Stop();
};