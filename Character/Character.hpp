#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include "../Animation/Animation.hpp"
#include <unordered_map>
#include "EnumClasses.hpp"
#include "Action.hpp"
#include "../virtualScreen/virtualScreen.hpp"

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

	int getStat(const AbilityScores &);
	
	void addCombatAction(std::shared_ptr<Action>);
	void activateCombatAction(const unsigned int &, const std::string &, const std::string &);
	std::string getActionName(const unsigned int &);
};
