#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <String>
#include "State.hpp"
#include "../Character/Party.hpp"
#include "../virtualScreen/virtualScreen.hpp"
#include "../TransformableMovement/TransformableMovement.hpp"
#include "../Core/dialogBox.h"

class Combat : public State {
private:
	
	Party party;
	CharacterContainer<std::shared_ptr<Character>> monsters;
	sf::Vector2u animationScreenSize = sf::Vector2u(1920, 680);
	sf::Vector2u damageScreenSize = sf::Vector2u(1920, 680);
	sf::Vector2u menuScreenSize = sf::Vector2u(1920, 450);
	
	VirtualScreen animationScreen;
	VirtualScreen damageScreen;
	VirtualScreen menuScreen;

	DialogBox diaBox;
	std::vector<std::string> combatChoices;

	bool attackFeedbackDone = 1;
	sf::Vector2f damageTextMidPoint;
	sf::Vector2f characterMidpoint;
	TransformableMovement damageMover;
	sf::Font attackFont;
	std::shared_ptr<sf::Text> damageText;

	std::vector<std::shared_ptr<Character>> initiative; //Players and monsters

	std::string surroundings;

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::Clock clock;
	float deltaTime = 0.0f;
public:
	bool CombatStarted = false;
	bool CombatFinished = false;

	Combat(sf::RenderWindow & window, Party & party, CharacterContainer<std::shared_ptr<Character>> & monster, std::string surrounding);
	~Combat();

	void start();
	virtual State* update();
	void draw();
	void Stop();

	void attackFeedback(std::shared_ptr<Character> & attacked, int dmg);

	//-Added 3 function (Niels)
	void checkMonstersDeath();

	void partyVictory();
	void monsterVictory();
};