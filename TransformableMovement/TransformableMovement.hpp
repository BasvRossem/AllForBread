#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class TransformableMovement{
private:
	bool finished = 0;
	bool TransformableMovementBlend = 0;

	std::shared_ptr<sf::Transformable> target;
	sf::Vector2f position;
	sf::Clock clock;
	sf::Clock startClock;
	float startTime;
	float duration;
public:
	TransformableMovement();
	TransformableMovement(std::shared_ptr<sf::Transformable> target, sf::Vector2f position, float duration);
	~TransformableMovement();

	void blend();
	void update();
	bool isFinished();
	bool checkForFinished();
};

