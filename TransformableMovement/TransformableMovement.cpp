#include "TransformableMovement.hpp"

TransformableMovement::TransformableMovement() {};

TransformableMovement::TransformableMovement(std::shared_ptr<sf::Transformable> target, sf::Vector2f position, float duration):
	target(target),
	position(position),
	duration(duration)
{
	startTime = startClock.restart().asSeconds();
}

TransformableMovement::~TransformableMovement(){
}

void TransformableMovement::blend(){
	
	if (TransformableMovementBlend == 0) {
		TransformableMovementBlend = 1;
	}
	else {
		sf::Vector2f targetPosition = target->getPosition();
		sf::Time elapsed = clock.restart();
		float currentTime = elapsed.asSeconds();
		double fps = 1.0 / currentTime;
		
		sf::Vector2f movement = position - targetPosition;
		std::cout << movement.x << ", " << movement.y << std::endl;
		if (duration < 0) {
			TransformableMovementBlend = 0;
			return;
		}
		duration -= startClock.restart().asSeconds();
		float framesLeft = static_cast<float>(duration * fps);
		movement.x = movement.x / framesLeft;
		movement.y = movement.y / framesLeft;
		target->move(movement);
	}

}

void TransformableMovement::update(){
	if (TransformableMovementBlend) { blend(); }
	if (checkForFinished()) {
		finished = 1;
	}
}

bool TransformableMovement::isFinished()
{
	return finished;
}

bool TransformableMovement::checkForFinished(){
	return !(TransformableMovementBlend);
}
