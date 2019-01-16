#include "Character.hpp"
#include <filesystem>


Character::Character(std::string & textureName, const sf::Vector2u & imageCount, const float & switchTime, const sf::Vector2f & imageSize) :
	imageCount(imageCount),
	switchTime(switchTime)
{
	totalTime = 0.0f;
	currentImage.x = 0;

	characterTexture.loadFromFile(textureName);
	characterTexture.setSmooth(true);
	uvRect.width = characterTexture.getSize().x / float(imageCount.x);
	uvRect.height = characterTexture.getSize().y / float(imageCount.y);
	std::cout << uvRect.width << " " << uvRect.height << std::endl;
	player.setTexture(&characterTexture);
	sf::Vector2u backSize = characterTexture.getSize();
	float xScale = imageSize.x / backSize.x * characterTexture.getSize().x;
	float yScale = imageSize.y / backSize.y * characterTexture.getSize().y;
	player.setSize(sf::Vector2f(xScale, yScale));
}

void Character::update(int row, float deltaTime) {
	currentImage.y = row;
	totalTime += deltaTime;
	
	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= imageCount.x) {
			currentImage.x = 0;
		}
	}

	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;
}

Character::~Character()
{
}

void Character::Show(sf::RenderWindow & window) {
	player.setTextureRect(uvRect);
	player.setPosition(sf::Vector2f(200, 200));
	
	window.draw(player);
}

//void Character::ShowMonster(sf::RenderWindow & window) {
//	std::cout << name << std::endl;
//	//std::cout << currentAnimation << " " << currentAnimation % idleAnimationNames.size()<< std::endl;
//	characterTexture.loadFromFile(idleAnimationNames[currentAnimation%idleAnimationNames.size()]);
//	currentAnimation++;
//	//std::cout << idleAnimationNames.size() << std::endl;
//	characterSprite.setTexture(characterTexture);
//	sf::Vector2u backSize = characterTexture.getSize();
//	float xScale = 200.0 / backSize.x;
//	float yScale = 200.0 / backSize.y;
//	characterSprite.setScale(sf::Vector2f(xScale, yScale));
//	characterSprite.setOrigin({ characterSprite.getLocalBounds().width, 0 });
//	characterSprite.scale({ -1, 1 });
//	characterSprite.setPosition(position);
//	window.draw(characterSprite);
//}

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
	} else if (modifier > maxHealth) {
		std::cout << "INSTAKILL!\n";
		currentHealth = 0;
	} else {
		currentHealth -= modifier;
	}
}

void Character::increaseHealth(const int & modifier) {
	if (modifier <= 0) {
		std::cout << "Je probeert de health te verhogen met een negatief getal\n";
	}else if (modifier > maxHealth) {
		std::cout << "INSTAHEAL!!\n";
		currentHealth = maxHealth;
	} else {
		currentHealth += maxHealth;
	}
}

void Character::decreaseMana(const int & modifier) {
	if (modifier < 0) {
		std::cout << "Je probeert de mana te verminderen met een negatief getal\n";
	} else if (modifier > maxMana) {
		std::cout << "INSTAKILL!\n";
		currentMana = 0;
	} else {
		currentMana -= modifier;
	}
}

void Character::increaseMana(const int & modifier) {
	if (modifier <= 0) {
		std::cout << "Je probeert de mana te verhogen met een negatief getal\n";
	} else if (modifier > maxMana) {
		std::cout << "INSTAREGEN!!\n";
		currentMana = maxMana;
	} else {
		currentMana += maxMana;
	}
}