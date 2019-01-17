#include "Character.hpp"
#include <filesystem>
#include <iostream>

Character::Character(const std::string & characterName, const std::string & textureName):
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

Character::Character(const std::string & characterName, const std::string & textureName, const int & frameAmount):
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
		std::cout << "INSTADEPLETE!\n";
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

void Character::increaseAbilityScore(const AbilityScores & stat, const int & statIncrease) {
	//-Safeguard for negative integers in parameter: "statIncrease"
	if (statIncrease < 0) {
		std::cout << "Parameter: 'statIncrease' value is smaller than 0, Value: " << statIncrease << "\n";
		return;
	}
	if (characterStats[stat] + statIncrease > 99) {
		characterStats[stat] = 99;
	} else {
		characterStats[stat] += statIncrease;
	}
}

void Character::decreaseAbilityScore(const AbilityScores & stat, const int & statDecrease) {
	//-Safeguard from negative	 integers in parameter: "statDecrease"
	if (statDecrease < 0) {
		std::cout << "Parameter: 'statDecrease' value is smaller than 0, Value: " << statDecrease << "\n";
		return;
	}

	if (characterStats[stat] - statDecrease < 0) {
		characterStats[stat] = 0;
	} else {
		characterStats[stat] -= statDecrease;
	}
}

void Character::printAbilityStats() {
	std::cout << "Str:	" << characterStats[AbilityScores::strength] << "\n";
	std::cout << "Dex:	" << characterStats[AbilityScores::dexterity] << "\n";
	std::cout << "End:	" << characterStats[AbilityScores::endurance] << "\n";
	std::cout << "Arc:	" << characterStats[AbilityScores::arcanism] << "\n";
	std::cout << "Cha:	" << characterStats[AbilityScores::charisma] << "\n";
	std::cout << "\n";
}

int Character::getStat(const AbilityScores & stat) {
	return characterStats[stat];
}

void Character::addCombatAction(std::shared_ptr<Action> a) {
	actions.push_back(a);
}

void Character::activateCombatAction(const unsigned int & id, std::shared_ptr<Character> target) {
	if (id < actions.size()) {
		actions[id]->activate(name, target->GetName());
	}
}

std::string Character::getActionName(const unsigned int &id) {
	if (id < actions.size()) {
		return actions[id]->getName();
	}
	return "";
}