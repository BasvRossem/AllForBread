#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class Animation{
private:
	std::shared_ptr<sf::Sprite> playerSprite;
	sf::Clock clock;
	std::shared_ptr<sf::Texture> texture;
	sf::IntRect textureRect;

	int currentImage;
	int imageCount;

	float totalTime = 0.0;
	float switchTime;
public:
	Animation(std::shared_ptr<sf::Sprite> playerSprite, std::shared_ptr<sf::Texture> texture, float totalTime);
	Animation();
	~Animation();
	void update();
};