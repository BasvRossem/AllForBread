#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include "../Animation/Animation.hpp"
#include <unordered_map>
#include "EnumClasses.hpp"
#include "../virtualScreen/virtualScreen.hpp"
#include <cstdlib>
#include "Attacks.hpp"
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
	sf::Image singleAnimationFrame;
	Attacks attacks;

	std::string name;
	sf::Vector2f position;
	sf::Clock clock;


	int maxHealth = 100;
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

	std::unordered_map<DamageTypes, AbilityScores> scalingsMap = {
		{DamageTypes::piercing,		AbilityScores::dexterity},
		{DamageTypes::bludgeoning,	AbilityScores::strength	},
		{DamageTypes::slashing,		AbilityScores::dexterity},
		{DamageTypes::acid,			AbilityScores::arcanism	},
		{DamageTypes::frost,		AbilityScores::arcanism },
		{DamageTypes::fire,			AbilityScores::arcanism	},
		{DamageTypes::force,		AbilityScores::strength	},
		{DamageTypes::lightning,	AbilityScores::arcanism },
		{DamageTypes::necrotic,		AbilityScores::arcanism },
		{DamageTypes::poison,		AbilityScores::arcanism },
		{DamageTypes::psychic,		AbilityScores::arcanism },
		{DamageTypes::radiant,		AbilityScores::arcanism },
		{DamageTypes::thunder,		AbilityScores::arcanism }
	};


public:
	Character(const std::string & characterName, const std::pair<const std::string &, const std::string &> & texture);
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
	/// Returns characte level
	const int getCharlevel();

	/// \brief
	/// Sets the level of the character
	virtual void setLevel(const int & newLevel);
	
	/// \brief
	/// sets characte level
	void setCharlevel(const int & lvl);

	/// \brief
	/// Returns unordered map of ability scores
	std::unordered_map<AbilityScores, int> getStats();

	/// \brief
	/// Returns unordered map of weaknesses
	std::unordered_map<DamageTypes, float> getWeaknesses();

	/// Returns an AbilityScore type which the damagetype and damage will scale with
	AbilityScores getScaling(const DamageTypes & type);

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
	void decreaseAbilityScore(const AbilityScores & stat, const int & statDecrease);

	/// \brief
	/// Increases given ability score by given amount
	void increaseAbilityScore(const AbilityScores & stat, const int & statIncrease);

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

	//Currently not yet implemented for default characters or monsters because lack of weapons and time
	//-Niels
	//=========================================================================================================
	/// \brief
	/// Returns a vector containing attacks that the player can use
	virtual std::vector<std::tuple<std::string, WeaponSlots, int>> getAvailableAttacks() = 0;

	/// \brief 
	/// Generates an attack message and returns this as a vector containing pairs of damagetype and damagevalue,
	/// Can be applied to characters using the processDamage() function
	/// Index 0 always contains the weapons primary damage type and will scale based on AbilityScores
	virtual std::vector<std::pair<DamageTypes, int>> generateAttack(const std::tuple<std::string, WeaponSlots, int> & attackDefenition) = 0;

	//=========================================================================================================
	
	//-Process Damage
	//=========================================================================================================

	/// \brief
	/// Process the damage and applies it to the character, and returns an integer with the total damage applied
	int processDamage(const std::vector<std::pair<DamageTypes, int>> & attackInformation);

	//=========================================================================================================

	/// brief
	/// Returns a shared pointer to the healthBar
	std::shared_ptr<ResourceBar> getHealthBar();

	/// \brief
	/// Repositions the healthbar to directly above the characterSprite
	void centreHealthBar();

	/// \brief
	/// Passes parameter position to the healthbar of the character
	void positionHealthbar(const sf::Vector2f & position);
	std::unordered_map<AbilityScores, int> getCharacterStats();
	void setCharacterStats(const std::unordered_map<AbilityScores, int> & newStats);

	void setWeakness(const DamageTypes & type, const float & factor);

	/// \brief
	/// Checks wether a lucky event can be generated by checking the charaters luck stat
	bool checkLuckStat();

	/// \brief
	/// Stops the animation on the current frame
	void stopAnimation();

	/// \brief
	/// Starts the animation
	void startAnimation();

	/// \brief
	/// Sets the position of the bottom of the sprite to a given point
	void setSpriteBottomPosition(const sf::Vector2f & position);

	/// \brief
	/// Recalculated health based on points specced into vitality
	void reCalculateHealth();
	
	/// \brief
	/// Sets the deathanimation of the character
	void setDeathAnimation(const std::string & deathTexturePath);

};

