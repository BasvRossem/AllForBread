#include "Character.hpp"
#include <filesystem>
#include <iostream>

Character::Character(const std::string & characterName, const std::string & textureName):
	name(characterName),
	idleTexture(new(sf::Texture)),
	deathTexture(new(sf::Texture)),
	sprite(new sf::Sprite)
{
	idleTexture->loadFromFile(textureName);
	idleTexture->setSmooth(true);
	sprite->setPosition(sf::Vector2f(150, 350));
	//Zorg dat setscale netjes wordt gedaan Dank u
	sprite->setScale(0.4f, 0.4f);
	currentAnimation = Animation(sprite, idleTexture, float(1.0));
	if (!deathTexture->loadFromFile("Assets/Rip.png")) {
		std::cout << "Error loading Rip.png, constructor 1" << std::endl;
	}
	currentAnimation = Animation(sprite, idleTexture, float(1.0));
	deathAnimation = Animation(sprite, deathTexture, float(1.0), 1);

	srand(clock.getElapsedTime().asMilliseconds());
}


Character::Character(const std::string & characterName, const std::string & textureName, const int & frameAmount):
	name(characterName),
	idleTexture(new(sf::Texture)),
	deathTexture(new(sf::Texture)),
	sprite(new sf::Sprite)
{
	idleTexture->loadFromFile(textureName);

	idleTexture->setSmooth(true);

	sprite->setPosition(sf::Vector2f(50, 400));
	//Zorg dat setscale netjes wordt gedaan Dank u
	sprite->setScale(0.5, 0.5);
	currentAnimation = Animation(sprite, idleTexture, float(1.0), frameAmount);

	if (!deathTexture->loadFromFile("Assets/Rip.png")) {
		std::cout << "Error loading Rip.png, constructor 2" << std::endl;
	}

	currentAnimation = Animation(sprite, idleTexture, float(1.0), frameAmount);
	deathAnimation = Animation(sprite, deathTexture, float(1.0), 1);
	srand(clock.getElapsedTime().asMilliseconds());
}

void Character::makeMonster() {
	sprite->scale(-1.0f, 1.0f);
	//BESTE BAS VAN MORGEN FIX DAT DIT NETJHES MET EEN TESTFRAME EN EEN OFFSET WORDT GEDAAN SetOrigin
	sprite->setPosition(sf::Vector2f(1770, 400));
}

void Character::update() {
	currentAnimation.update();
}

Character::~Character(){
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
void Character::idleAnimation() {
	currentAnimation = Animation(sprite, idleTexture, float(1.0));
}

std::string Character::getName() {
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

void Character::increaseWeakness(const DamageTypes & modifierName, const float & modifierValue) {
	if (modifierValue < 0.0) {
		std::cout << "Parameter: 'modifierValue' is smaller than 0, Value: " << modifierValue << "\n";
	}

	if (weaknessModifiers[modifierName] + modifierValue > 10.0) {
		weaknessModifiers[modifierName] = 10.0;
	} else {
		weaknessModifiers[modifierName] += modifierValue;
	}
}

void Character::decreaseWeakness(const DamageTypes & modifierName, const float & modifierValue) {
	if (modifierValue < 0.0) {
		std::cout << "Parameter: 'modifierValue' is smaller than 0, Value: " << modifierValue << "\n";
		return;
	}

	if (weaknessModifiers[modifierName] - modifierValue < 0.0) {
		weaknessModifiers[modifierName] = 0.0;
	} else {
		weaknessModifiers[modifierName] -= modifierValue;
	}
}

void Character::printAbilityStats() {
	std::cout << "Vit:	" << characterStats[AbilityScores::vitality]	<< "\n";
	std::cout << "Str:	" << characterStats[AbilityScores::strength]	<< "\n";
	std::cout << "Dex:	" << characterStats[AbilityScores::dexterity]	<< "\n";
	std::cout << "Arc:	" << characterStats[AbilityScores::arcanism]	<< "\n";
	std::cout << "Cha:	" << characterStats[AbilityScores::charisma]	<< "\n";
	std::cout << "Lck:	" << characterStats[AbilityScores::luck]		<< "\n";
	std::cout << "\n";
}

int Character::getStat(const AbilityScores & stat) {
	return characterStats[stat];
}

float Character::getModifier(const DamageTypes & modifier) {
	return weaknessModifiers[modifier];
}

void Character::doDeath() {
	showDeathTexture();
}

void Character::showDeathTexture() {
	currentAnimation = deathAnimation;
}

void Character::addCombatAction(std::shared_ptr<Action> a) {
	actions.push_back(a);
}

void Character::activateCombatAction(const unsigned int & id, const std::shared_ptr<Character> &c) {
	if (id < actions.size()) {
		std::pair<int, int> IDandInfo = actions[id]->activate();
		if (IDandInfo.first == 0) {
			c->decreaseHealth(IDandInfo.second);
		}
	}
}

std::string Character::getActionName(const unsigned int &id) {
	if (id < actions.size()) {
		return actions[id]->getName();
	}
	return "";
}

std::vector<std::shared_ptr<Action>> Character::getActions() {
	return actions;
}

sf::Vector2f Character::getSpriteMidpoint() {
	sf::Vector2f midpoint = sf::Vector2f(
		sprite->getGlobalBounds().left + (sprite->getGlobalBounds().width / 2),
		sprite->getGlobalBounds().top + (sprite->getGlobalBounds().height / 2)
	);
	return midpoint;
}