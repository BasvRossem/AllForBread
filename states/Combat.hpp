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

class Combat : public State {
private:
	//End of Combat
	bool CombatFinished = false;

	//Party and monsters
	Party party;
	CharacterContainer<std::shared_ptr<Character>> monsters;
	std::vector<std::shared_ptr<Character>> initiative;
	uint_fast16_t currentInitiative = 0;
	std::shared_ptr<Character> currentCharacter;

	//Virtual screens
	sf::Vector2u animationScreenSize = sf::Vector2u(1920, 680);
	sf::Vector2u damageScreenSize = sf::Vector2u(1920, 680);
	sf::Vector2u menuScreenSize = sf::Vector2u(1920, 450);
	
	VirtualScreen animationScreen;
	VirtualScreen damageScreen;
	VirtualScreen menuScreen;

	//Dialog box
	DialogBox diaBox;
	std::vector<std::string> combatChoices;

	//Attack feedback
	bool attackFeedbackFinished = 1;
	sf::Vector2f damageTextMidPoint;
	sf::Vector2f characterMidpoint;
	TransformableMovement damageMover;
	sf::Font attackFont;
	std::shared_ptr<sf::Text> damageText;

	//Background
	BackGround backgrnd;
	std::string surrounding;

	//Keyboard
	KeyboardHandler keyhandle;

	//Functions
	void attackFeedbackInitialiser(const std::shared_ptr<Character> & target, const sf::String& info);

	bool attackFeedbackDone = true;
public:


	Combat(sf::RenderWindow & window, Party & party, CharacterContainer<std::shared_ptr<Character>> & monster, std::string surrounding, BackGround & backgrnd);
	~Combat();

	void checkEvents();

	virtual State* update();
	void newCurrentCharacter();
	void draw();
	void stop();


	void makeAttackFeedback(const std::shared_ptr<Character> & target, const int & info);
	void makeAttackFeedback(const std::shared_ptr<Character> & target, const std::string & info);
	void updateAttackFeedback();

	//-Added 3 function (Niels)
	void checkMonstersDeath();

	void partyVictory();
	void monsterVictory();
	void calculateInitiative(std::vector<std::shared_ptr<Character>> &characterVector);
	std::shared_ptr<Character> getMonster(unsigned int i);
};