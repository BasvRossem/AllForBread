#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include "../Animation/Animation.hpp"
#include <unordered_map>
#include "EnumClasses.hpp"
#include "../virtualScreen/virtualScreen.hpp"
#include <cstdlib>
#include "Action.hpp"
#include "Attack.hpp"
/// @file

/// \brief
/// The baseclass of characters
class Character{
protected:
	std::shared_ptr<sf::Texture> idleTexture;
	std::shared_ptr<sf::Texture> deathTexture;
	std::shared_ptr<sf::Sprite> sprite;
	Animation currentAnimation;
	Animation deathAnimation;
	
	std::vector<std::shared_ptr<Action>> actions;

	std::string name;
	sf::Vector2f position;
	sf::Clock clock;

	int maxHealth = 10;
	int maxMana = 100;
	int level = 1;

	int currentHealth = maxHealth;
	int currentMana = maxMana;

	std::unordered_map<AbilityScores, int> characterStats = {
		{AbilityScores::vitality,	10},
		{AbilityScores::strength,	10},
		{AbilityScores::dexterity,	10},
		{AbilityScores::arcanism,	10},
		{AbilityScores::charisma,	10},
		{AbilityScores::luck,		10}
	};

public:
	Character(const std::string &, const std::string &);
	Character(const std::string &, const std::string &, const int &);
	~Character();

	/// \brief
	/// Updates current animation
	void update();

	/// \brief
	/// Draws character to given window
	void draw(sf::RenderWindow & window);

	/// \brief
	/// Draws character to given VirtualScreen
	void draw(VirtualScreen & window);

	/// \brief
	/// Creates an idleAnimation
	void idleAnimation();

	/// \brief
	/// Draws character to mirrored position
	void makeMonster();

	/// \brief
	/// Returns charactername
	std::string getName();

	/// \brief
	/// Returnes sharedpointer to drawable of character
	std::shared_ptr<sf::Sprite> getDrawable();

	/// \brief
	/// Returns current health
	int getHealth();

	/// \brief
	/// Returns current mana
	int getMana();

	/// \brief
	/// Returns value of given ability
	int getStat(const AbilityScores & stat);

	/// \brief
	/// Returns action name at given index. If index is out of bounds, return empty string
	std::string getActionName(const unsigned int & id);

	std::vector<std::shared_ptr<Action>> getActions();

	/// \brief
	/// Lowers health by given amount
	void decreaseHealth(const int & modifier);

	/// \brief
	/// Increases health by given amount
	void increaseHealth(const int & modifier);

	/// \brief
	/// Lowers mana by given amount
	void decreaseMana(const int & modifier);

	/// \brief
	/// Increases mana by given amount
	void increaseMana(const int & modifier);

	//-Added 2 functions (Niels)
	virtual void doDeath();
	void showDeathTexture();

	/// \brief
	/// Lowers given ability score by given amount
	void decreaseAbilityScore(const AbilityScores & stat, const int & statIncrease);

	/// \brief
	/// Increases given ability score by given amount
	void increaseAbilityScore(const AbilityScores & stat, const int & statDecrease);

	/// \brief
	/// Prints all abilities and values
	void printAbilityStats();

	/// \brief
	/// Adds a combat action
	void addCombatAction(std::shared_ptr<Action>);

	/// \brief
	/// Activates action at given index, target at given character
	void activateCombatAction(const unsigned int & id, const std::shared_ptr<Character> &c);
};
