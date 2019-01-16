#include "Character.hpp"
#include <filesystem>
#include <iostream>

Character::Character(std::string characterName, std::string textureName):
	name(characterName),
	idleTexture(new(sf::Texture)),
	sprite(new sf::Sprite)
{
	idleTexture->loadFromFile(textureName);
	
	idleTexture->setSmooth(true);
	
	sprite->setPosition(sf::Vector2f(200, 200));
	sprite->setScale(0.5, 0.5);
	currentAnimation = Animation(sprite, idleTexture, float(1.0));
}

void Character::update() {
	currentAnimation.update();
}

Character::~Character()
{
}

void Character::Show(sf::RenderWindow & window) {
	window.draw(*sprite);
}

void Character::IdleAnimation() {
	currentAnimation = Animation(sprite, idleTexture, float(1.0));
}

std::string Character::GetName() {
	return name;
}

int Character::getHealth() {
	return currentHealth;
}

int Character::getMana() {
	return currentMana;
}

void Character::decreaseHealth(const int & modifier) {
	if (modifier < 0) {
		std::cout << "Je probeert de health te verminderen met een negatief getal\n";
	}
	else if (modifier > maxHealth) {
		std::cout << "INSTAKILL!\n";
		currentHealth = 0;
	}
	else {
		currentHealth -= modifier;
	}
}

void Character::increaseHealth(const int & modifier) {
	if (modifier <= 0) {
		std::cout << "Je probeert de health te verhogen met een negatief getal\n";
	}
	else if (modifier > maxHealth) {
		std::cout << "INSTAHEAL!!\n";
		currentHealth = maxHealth;
	}
	else {
		currentHealth += maxHealth;
	}
}

void Character::decreaseMana(const int & modifier) {
	if (modifier < 0) {
		std::cout << "Je probeert de mana te verminderen met een negatief getal\n";
	}
	else if (modifier > maxMana) {
		std::cout << "INSTAKILL!\n";
		currentMana = 0;
	}
	else {
		currentMana -= modifier;
	}
}

void Character::increaseMana(const int & modifier) {
	if (modifier <= 0) {
		std::cout << "Je probeert de mana te verhogen met een negatief getal\n";
	}
	else if (modifier > maxMana) {
		std::cout << "INSTAREGEN!!\n";
		currentMana = maxMana;
	}
	else {
		currentMana += maxMana;
	}
}

int Character::getStat(const AbilityScores & stat) {
	return characterStats[stat];
}