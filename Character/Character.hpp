#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include "../Animation.hpp"
#include <unordered_map>
#include "EnumClasses.hpp"

class Character{
private:
	std::shared_ptr<sf::Texture> idleTexture ;
	std::shared_ptr<sf::Sprite> sprite;
	Animation currentAnimation;

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
	Character(std::string characterName, std::string textureName);
	~Character();

	void update();
	void Show(sf::RenderWindow & window);
	void IdleAnimation();
	
	std::string GetName();
	int getHealth();
	int getMana();
	void decreaseHealth(const int &);
	void increaseHealth(const int &);
	void decreaseMana(const int &);
	void increaseMana(const int &);
};
