#include "Character.hpp"
#include <filesystem>
#include <iostream>

Character::Character(const std::string & characterName, const std::pair<const std::string &, const std::string &> & texture ):
	name(characterName),
	idleTexture(new(sf::Texture)),
	deathTexture(new(sf::Texture)),
	sprite(new sf::Sprite)
{
	idleTexture->loadFromFile(texture.first);
	idleTexture->setSmooth(true);

	sf::Image tmpImage;
	tmpImage.loadFromFile(texture.second);

	unsigned int frameAmount = idleTexture->getSize().x / tmpImage.getSize().x;
	currentAnimation = Animation(sprite, idleTexture, float(1.0), frameAmount);

	if (!deathTexture->loadFromFile("Assets/Rip.png")) {
		std::cout << "Error loading Rip.png, constructor 2" << std::endl;
	}

	currentAnimation = Animation(sprite, idleTexture, float(1.0), frameAmount);
	deathAnimation = Animation(sprite, deathTexture, float(1.0), 1);

	update();
	auto spriteSize = sf::Vector2f(250, 300);
	sprite->setOrigin(getSpriteMidpoint());
	sprite->setScale(spriteSize.x / sprite->getGlobalBounds().width, spriteSize.y / sprite->getGlobalBounds().height);
	
	srand(clock.getElapsedTime().asMilliseconds());
}

void Character::makeMonster() {
	sprite->scale(-1.0f, 1.0f);
}

void Character::update() {
	currentAnimation.update();
}

Character::~Character(){
}

void Character::draw(sf::RenderWindow & window) {
	window.draw(*sprite);
	healthBar.draw(window);
}

void Character::draw(VirtualScreen & window) {
	window.drawSurfaceDraw(*sprite);
	healthBar.draw(window);
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
	else if (currentHealth - modifier < 0) {
		std::cout << "INSTAKILL!\n";
		currentHealth = 0;
	}
	else {
		currentHealth -= modifier;
	}
	healthBar.setCurrentResource(currentHealth);
}

void Character::increaseHealth(const int & modifier) {
	if (modifier < 0) {
		std::cout << "Je probeert de health te verhogen met een negatief getal\n";
	}
	else if (currentHealth + modifier > maxHealth) {
		std::cout << "INSTAHEAL!!\n";
		currentHealth = maxHealth;
	}
	else {
		currentHealth += modifier;
	}
	healthBar.setCurrentResource(currentHealth);
}

void Character::decreaseMana(const int & modifier) {
	if (modifier < 0) {
		std::cout << "Je probeert de mana te verminderen met een negatief getal\n";
	}
	else if (currentMana - modifier < 0) {
		std::cout << "INSTADEPLETE!\n";
		currentMana = 0;
	}
	else {
		currentMana -= modifier;
	}
}

void Character::increaseMana(const int & modifier) {
	if (modifier < 0) {
		std::cout << "Je probeert de mana te verhogen met een negatief getal\n";
	}
	else if (currentMana + modifier > maxMana) {
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

const int Character::getCharlevel() {
	return level;
}

void Character::setCharlevel(const int & lvl)
{
	level = lvl;
}

std::unordered_map<AbilityScores, int> Character::getStats() {
	return characterStats;
}

std::unordered_map<DamageTypes, float> Character::getWeaknesses() {
	return weaknessModifiers;
}

AbilityScores Character::getScaling(const DamageTypes & type) {
	return scalingsMap[type];
}

void Character::doDeath() {
	showDeathTexture();
}

void Character::showDeathTexture() {
	currentAnimation = deathAnimation;
}

//-Here is where I would put my generateAttack() functions
//=========================================================================================================
// IF I HAD ONE!!!
//=========================================================================================================

int Character::processDamage(const std::vector<std::pair<DamageTypes, int>> & attackInformation) {
	int totalDamage = 0;

	for (auto & damagePair : attackInformation) {
		int tempCalcDamage = static_cast<int>(damagePair.second * getModifier(damagePair.first));
		this->decreaseHealth(tempCalcDamage);

		totalDamage += tempCalcDamage;
	}

	return totalDamage;
}

sf::Vector2f Character::getSpriteMidpoint() {
	sf::Vector2f midpoint = sf::Vector2f(
		sprite->getGlobalBounds().left + (sprite->getGlobalBounds().width / 2),
		sprite->getGlobalBounds().top + (sprite->getGlobalBounds().height / 2)
	);
	return midpoint;
}

std::shared_ptr<ResourceBar> Character::getHealthBar() {
	return std::make_shared<ResourceBar>(healthBar);
}

void Character::centreHealthBar() {
	healthBar.setPosition(int(getSpriteMidpoint().x), int(getSpriteMidpoint().y) - 150);
}

void Character::positionHealthbar(const sf::Vector2f & position) {
	healthBar.setPosition(position);
}


std::unordered_map<AbilityScores, int> Character::getCharacterStats() {
	return characterStats;
}

void Character::setCharacterStats(const std::unordered_map<AbilityScores, int> & newStats) {
	characterStats = newStats;
}

void Character::setWeakness(const DamageTypes & type, const float & factor) {
	weaknessModifiers[type] = factor;
}

bool Character::checkLuckStat() {
	if ((rand() % 100 + 1) <= characterStats[AbilityScores::luck]) {
		return true;
	}
	return false;
}

void Character::stopAnimation() {
	currentAnimation.stop();
}

void Character::startAnimation() {
	currentAnimation.start();
}

void Character::setSpriteBottomPosition(const sf::Vector2f & position) {
	sf::Vector2f newPosition;

	newPosition.x += position.x;
	newPosition.y += position.y;
	newPosition.y -= sprite->getGlobalBounds().height /2;
	sprite->setPosition(newPosition);
}

