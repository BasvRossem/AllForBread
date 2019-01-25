#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include "../Animation/Animation.hpp"
#include <unordered_map>
#include "EnumClasses.hpp"
#include "../virtualScreen/virtualScreen.hpp"
#include <cstdlib>
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
	
	Attacks attacks;

	std::string name;
	sf::Vector2f position;
	sf::Clock clock;

	int maxHealth = 1;
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
	virtual void draw(sf::RenderWindow & window);

	/// \brief
	/// Draws character to given VirtualScreen
	virtual void draw(VirtualScreen & window);

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

	/// \brief
	/// Death function called when character dies.
	virtual void doDeath();

	/// \brief 
	/// Sets the current animation to death texture with 1 frame
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
	/// Returns the coodinates of the midpoint of the sprite
	sf::Vector2f getSpriteMidpoint();


	void activateAttack(const std::shared_ptr<Character> &c, const unsigned int & i);

	std::array<std::pair<std::string, int>, 4> getAttacks();

	unsigned int getModifier(const unsigned int & i);

	/// brief
	/// Returns a shared pointer to the healthBar
	std::shared_ptr<ResourceBar> getHealthBar(); \

	/// \brief
	/// Repositions the healthbar to directly above the characterSprite
	void centreHealthBar();

	/// \brief
	/// Passes parameter position to the healthbar of the character
	void positionHealthbar(const sf::Vector2f & position);

	/// \brief
	/// Checks wether a lucky event can be generated by checking the charaters luck stat
	bool checkLuckStat();

};
