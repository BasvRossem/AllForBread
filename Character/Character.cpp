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
	
	sprite->setPosition(sf::Vector2f(150, 350));
	//Zorg dat setscale netjes wordt gedaan Dank u
	sprite->setScale(0.4f, 0.4f);
	currentAnimation = Animation(sprite, idleTexture, float(1.0));
}

Character::Character(std::string characterName, std::string textureName, int frameAmount):
	name(characterName),
	idleTexture(new(sf::Texture)),
	sprite(new sf::Sprite)
{
	idleTexture->loadFromFile(textureName);

	idleTexture->setSmooth(true);

	sprite->setPosition(sf::Vector2f(50, 400));
	//Zorg dat setscale netjes wordt gedaan Dank u
	sprite->setScale(0.5, 0.5);
	currentAnimation = Animation(sprite, idleTexture, float(1.0));
}

void Character::makeMonster() {
	sprite->scale(-1.0f, 1.0f);
	//BESTE BAS VAN MORGEN FIX DAT DIT NETJHES MET EEN TESTFRAME EN EEN OFFSET WORDT GEDAAN SetOrigin
	sprite->setPosition(sf::Vector2f(1770, 400));
}

void Character::update() {
	currentAnimation.update();
}

Character::~Character()
{
}

void Character::draw(sf::RenderWindow & window) {
	window.draw(*sprite);
}

void Character::draw(VirtualScreen & window) {
	window.drawSurfaceDraw(*sprite);
}

std::shared_ptr<sf::Sprite> Character::getDrawable() {
	return sprite;
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

void Character::addCombatAction(std::shared_ptr<Action> a) {
	actions.push_back(a);
}

void Character::activateCombatAction(const unsigned int & id, const std::string & playername, const std::string & enemy) {
	if (id < actions.size()) {
		actions[id]->activate(playername, enemy);
	}
}

std::string Character::getActionName(const unsigned int &id) {
	if (id < actions.size()) {
		return actions[id]->getName();
	}
	return "";
}