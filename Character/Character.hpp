#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <unordered_map>
#include "EnumClasses.hpp"

class Character{
private:
	sf::Texture characterTexture;
	sf::RectangleShape player;
	sf::IntRect uvRect;
	sf::Vector2u currentImage;
	sf::Vector2u imageCount;

	std::string name;
	sf::Vector2f position;
	float totalTime;
	float switchTime;
	
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
	Character(std::string & textureName, const sf::Vector2u & imageCount, const float & switchTime, const sf::Vector2f & imageSize);
	~Character();
	void update(int row, float deltaTime);
	void Show(sf::RenderWindow & window);
	//void ShowMonster(sf::RenderWindow & window);
	std::string GetName();

	int getHealth();
	int getMana();
	void decreaseHealth(const int & );
	void increaseHealth(const int & );
	void decreaseMana(const int & );
	void increaseMana(const int & );
};

