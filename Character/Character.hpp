#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>

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
	

	
public:
	Character(std::string & textureName, sf::Vector2u imageCount, float switchTime, sf::Vector2f imageSize);
	~Character();
	void update(int row, float deltaTime);
	void Show(sf::RenderWindow & window);
	//void ShowMonster(sf::RenderWindow & window);
	std::string GetName();
};

