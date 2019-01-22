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
#include "ResourceBar.hpp"
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
	int currentHealth = maxHealth;

	int maxMana = 100;
	int currentMana = maxMana;

	int level = 1;

	ResourceBar healthBar = ResourceBar(sf::Vector2f(0.0f, 0.0f), maxHealth, currentHealth);

	std::unordered_map<AbilityScores, int> characterStats = {
		{AbilityScores::vitality,	10},
		{AbilityScores::strength,	10},
		{AbilityScores::dexterity,	10},
		{AbilityScores::arcanism,	10},
		{AbilityScores::charisma,	10},
		{AbilityScores::luck,		10}
	};

	std::unordered_map<DamageTypes, float> weaknessModifiers = {
		{DamageTypes::piercing,		1.0f},
		{DamageTypes::bludgeoning,	1.0f},
		{DamageTypes::slashing,		1.0f},
		{DamageTypes::acid,			1.0f},
		{DamageTypes::frost,		1.0f},
		{DamageTypes::fire,			1.0f},
		{DamageTypes::force,		1.0f},
		{DamageTypes::lightning,	1.0f},
		{DamageTypes::necrotic,		1.0f},
		{DamageTypes::poison,		1.0f},
		{DamageTypes::psychic,		1.0f},
		{DamageTypes::radiant,		1.0f},
		{DamageTypes::thunder,		1.0f}
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
	/// Returns DamageType modifier float
	float getModifier(const DamageTypes & modifier);

	/// \brief
	/// Returns action name at given index. If index is out of bounds, return empty string
	std::string getActionName(const unsigned int & id);


	/// \brief
	/// Returns all character actions in a vector
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
	/// Increases given weakness modifier by given amount
	void increaseWeakness(const DamageTypes & modifierName, const float & modifierValue);

	/// \brief
	/// Decreases given weakness modifier by given amount
	void decreaseWeakness(const DamageTypes & modifierName, const float & modifierValue);

	/// \brief
	/// Prints all abilities and values
	void printAbilityStats();

	/// \brief
	/// Adds a combat action
	void addCombatAction(std::shared_ptr<Action>);

	/// \brief
	/// Activates action at given index, target at given character
	void activateCombatAction(const unsigned int & id, const std::shared_ptr<Character> &c);

	/// \brief
	/// Returns the coodinates of the midpoint of the sprite
	sf::Vector2f getSpriteMidpoint();

	/// brief
	/// Returns a shared pointer to the healthBar
	std::shared_ptr<ResourceBar> getHealthBar(); \

	/// \brief
	/// Repositions the healthbar to directly above the characterSprite
	void centreHealthBar();

	void positionHealthbar(const sf::Vector2f & position);
};
