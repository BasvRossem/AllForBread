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
#include "../Character/Attack.hpp"
#include "../Character/ResourceBar.hpp"
#include "../Character/Mob.hpp"
#include "../Core/Sounds.hpp"

class Combat : public State {
private:
	//End of Combat
	bool CombatFinished = false;

	//Party and monsters
	Party party;
	Mob monsters;

	std::vector<std::shared_ptr<Character>> allCharacters = {};

	//Combat initiative (Character turn order)
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
	DialogBox afterCombatBox;

	//Sound and Music
	Sounds sound;

	//Attack feedback
	bool attackFeedbackFinished = true;
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


	Combat(sf::RenderWindow & window, Party & party, Mob & monster, std::string surrounding, BackGround & backgrnd);
	~Combat();

	void checkEvents();

	virtual State* update();
	void newCurrentCharacter();
	void draw();
	void stop();


	void makeAttackFeedback(const std::shared_ptr<Character> & target, const int & info);
	void makeAttackFeedback(const std::shared_ptr<Character> & target, const std::string & info);
	void updateAttackFeedback();


	void checkMonstersDeath();
	void checkPlayerDeath();

	/// \brief
	/// Party victory function, closes the combat screen and state as if the players won
	void partyVictory();

	/// \brief
	/// Monster victory function, closes the combat screen and state as if monsters won
	void monsterVictory();

	/// \brief
	/// Sorts the initiative vector by dexterity value (high to low)
	void calculateInitiative(std::vector<std::shared_ptr<Character>> &characterVector);

	/// \brief
	/// Removed given character from the initiative vector
	void removeFromInitiative(const std::shared_ptr<Character> & character);

	/// \brief
	/// Checks wether the given parameter is a player or a monster
	bool isPlayer(const std::shared_ptr<Character> & character);

	std::shared_ptr<Monster> getMonster(unsigned int i);
};