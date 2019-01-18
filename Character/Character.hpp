#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include "../Animation/Animation.hpp"
#include <unordered_map>
#include "EnumClasses.hpp"
#include "../virtualScreen/virtualScreen.hpp"
#include <cstdlib>

class Character{
protected:
	std::shared_ptr<sf::Texture> idleTexture;
	std::shared_ptr<sf::Texture> deathTexture;
	std::shared_ptr<sf::Sprite> sprite;
	Animation currentAnimation;
	Animation deathAnimation;

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
	Character(std::string characterName, std::string textureName);
	Character(std::string characterName, std::string textureName, int frameAmount);
	~Character();

	void update();
	void draw(sf::RenderWindow & window);
	void draw(VirtualScreen & window);
	void IdleAnimation();
	void makeMonster();
	std::string GetName();
	std::shared_ptr<sf::Sprite> getDrawable();
	int getHealth();
	int getMana();
	void decreaseHealth(const int &);
	void increaseHealth(const int &);
	void decreaseMana(const int &);
	void increaseMana(const int &);

	//-Added 2 functions (Niels)
	virtual void doDeath();
	void showDeathTexture();

	int getStat(const AbilityScores &);
};
