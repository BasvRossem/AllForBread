#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include "../Animation/Animation.hpp"
#include <unordered_map>
#include "EnumClasses.hpp"
#include "Action.hpp"
#include "Attack.hpp"
#include "../virtualScreen/virtualScreen.hpp"
/// @file

/// \brief
/// The baseclass of characters
class Character{
private:
	std::shared_ptr<sf::Texture> idleTexture ;
	std::shared_ptr<sf::Sprite> sprite;
	Animation currentAnimation;
	
	std::vector<std::shared_ptr<Action>> actions;

	std::string name;
	sf::Vector2f position;
protected:
	int maxHealth = 10;
	int maxMana = 100;
	int level = 1;

	int currentHealth = maxHealth;
	int currentMana = maxMana;

	std::unordered_map<AbilityScores, int> characterStats = {
		{AbilityScores::strength,	10},
		{AbilityScores::dexterity,	10},
		{AbilityScores::endurance,	10},
		{AbilityScores::arcanism,	10},
		{AbilityScores::charisma,	10}
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
	void draw(sf::RenderWindow &);

	/// \brief
	/// Draws character to given VirtualScreen
	void draw(VirtualScreen &);

	/// \brief
	/// Creates an idleAnimation
	void IdleAnimation();

	/// \brief
	/// Draws character to mirrored position
	void makeMonster();

	/// \brief
	/// Returns charactername
	std::string GetName();

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
	/// Lowers health by given amount
	void decreaseHealth(const int &);

	/// \brief
	/// Increases health by given amount
	void increaseHealth(const int &);

	/// \brief
	/// Lowers mana by given amount
	void decreaseMana(const int &);

	/// \brief
	/// Increases mana by given amount
	void increaseMana(const int &);

	/// \brief
	/// Lowers given ability score by given amount
	void decreaseAbilityScore(const AbilityScores &, const int &);

	/// \brief
	/// Increases given ability score by given amount
	void increaseAbilityScore(const AbilityScores &, const int &);

	/// \brief
	/// Prints all abilities and values
	void printAbilityStats();

	/// \brief
	/// Returns value of given ability
	int getStat(const AbilityScores &);

	/// \brief
	/// Adds a combat action
	void addCombatAction(std::shared_ptr<Action>);

	/// \brief
	/// Activates action at given index, target at given character
	void activateCombatAction(const unsigned int &, Character  &c);

	/// \brief
	/// Returns action name at given index. If index is out of bounds, return empty string
	std::string getActionName(const unsigned int &);
};
