#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <String>
#include <sstream>
#include "State.hpp"
#include "../Character/Party.hpp"
#include "../virtualScreen/virtualScreen.hpp"
#include "../TransformableMovement/TransformableMovement.hpp"
#include "../Core/dialogBox.h"
#include "../Core/background.hpp"
#include "../Core/KeyboardHandler.hpp"
#include "../Character/action.hpp"
#include "../Character/Attack.hpp"
#include "../Character/ResourceBar.hpp"

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
	
	BackGround backgrnd;
	sf::Clock clock;
	float deltaTime = 0.0f;

	KeyboardHandler keyhandle;

	uint_fast16_t curInitiative = 0;

	std::string surrounding;

public:
	bool CombatStarted = false;
	bool CombatFinished = false;

	Combat(sf::RenderWindow & window, Party & party, CharacterContainer<std::shared_ptr<Character>> & monster, std::string surrounding, BackGround & backgrnd);
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
	void calculateInitiative(std::vector<std::shared_ptr<Character>> &characterVector);
	std::shared_ptr<Character> getMonster(unsigned int i);
};