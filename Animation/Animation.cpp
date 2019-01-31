#include "Animation.hpp"
#include <iostream>
Animation::Animation(std::shared_ptr<sf::Sprite> playerSprite, std::shared_ptr<sf::Texture> texture, float animationDuration):
	playerSprite(playerSprite),
	texture(texture)
{
	
	currentImage = 0;

	textureRect.width = static_cast<int>(texture->getSize().y);
	textureRect.height = static_cast<int>(texture->getSize().y);
	imageCount = static_cast<int>(texture->getSize().x / float(textureRect.width));
	switchTime = animationDuration / imageCount;
	playerSprite->setTexture(*texture);
}

Animation::Animation(std::shared_ptr<sf::Sprite> playerSprite, std::shared_ptr<sf::Texture> texture, float animationDuration, int frameAmount):
	playerSprite(playerSprite),
	texture(texture)
{
	currentImage = 0;

	textureRect.width = static_cast<int>(texture->getSize().y);
	textureRect.height = static_cast<int>(texture->getSize().y);
	imageCount = frameAmount;
	switchTime = animationDuration / imageCount;
	playerSprite->setTexture(*texture);
}

Animation::Animation(){
	totalTime = 0.0f;
	currentImage = 0;
}

Animation::~Animation(){
}

void Animation::update(){
	if (animate) {
		totalTime += clock.restart().asSeconds();
		if (totalTime >= switchTime * imageCount) {
			totalTime = 0;
		}
		if (totalTime >= switchTime) {
			totalTime -= switchTime;
			currentImage++;
			if (currentImage >= imageCount - 1) {
				oneToLastFinished = true;
			}
			if (currentImage >= imageCount) {
				currentImage = 0;
				oneLoopFinished = true;
			}
		}
		textureRect.left = currentImage * (texture->getSize().x / imageCount);
		playerSprite->setTexture(*texture);
		playerSprite->setTextureRect(textureRect);
	}
}

void Animation::start() {
	animate = true;
}

void Animation::stop() {
	animate = false;
}

std::shared_ptr<sf::Texture> Animation::getTexture() {
	return texture;
}

bool Animation::getLoopFinished() {
	return oneLoopFinished;
}

bool Animation::getOneToLastFinished() {
	return oneToLastFinished;
}

void Animation::makeOneToLast() {
	currentImage = static_cast<int>(texture->getSize().x / float(textureRect.width)) - 1;
	textureRect.left = currentImage * (texture->getSize().x / imageCount);
	playerSprite->setTexture(*texture);
	playerSprite->setTextureRect(textureRect);
}