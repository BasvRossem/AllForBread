#include "ResourceBar.hpp"

ResourceBar::ResourceBar(const sf::Vector2f & position, const sf::Vector2f & size, const int & maxValue, const int & currentValue, const sf::Color & barColor) :
	position(position),
	size(size),
	maxValue(maxValue),
	currentValue(currentValue),
	barColor(barColor)
{
	barBackground.setSize(size);
	barBackground.setPosition(position);
	barInnerMeter.setPosition(position);
	barBackground.setFillColor(sf::Color::White);
	barInnerMeter.setFillColor(barColor);
};

ResourceBar::ResourceBar(const sf::Vector2f & position, const int & maxValue, const int & currentValue) :
	position(position),
	maxValue(maxValue),
	currentValue(currentValue)
{
	barBackground.setSize(size);
	barBackground.setPosition(position);
	barInnerMeter.setPosition(position);
	barBackground.setFillColor(sf::Color::White);
	barInnerMeter.setFillColor(sf::Color::Red);
}

ResourceBar::ResourceBar() {};


void ResourceBar::setPosition(const int & x, const int & y) {
	setPosition(sf::Vector2f(
		static_cast<float>(x),
		static_cast<float>(y)
	));
}


void ResourceBar::setPosition(const sf::Vector2f & newPosition) {
	position = sf::Vector2f(
		newPosition.x - (size.x / 2),
		newPosition.y - (size.y / 2)
	);

	barBackground.setPosition(position);
	barInnerMeter.setPosition(position);
}


void ResourceBar::resize(const int & x, const int & y) {
	size = sf::Vector2f(
		static_cast<float>(x),
		static_cast<float>(y)
	);
}


void ResourceBar::resize(const sf::Vector2f & newSize) {
	size = newSize;
}


void ResourceBar::update() {
	int unitsPerPixel = static_cast<int> (size.x / maxValue);
	barInnerMeter.setSize(sf::Vector2f(static_cast<float>(currentValue * unitsPerPixel), size.y));
}


void ResourceBar::decreaseCurrentResource(const int & resourceModifier) {
	if (resourceModifier < 0) {
		std::cout << "Parameter: 'resourceModifier' is smaller than 0";
		return;
	}

	if (currentValue - resourceModifier < 0) {
		currentValue = 0;
	} else {
		currentValue -= resourceModifier;
	}
}

void ResourceBar::increaseCurrentResource(const int & resourceModifier) {
	if (resourceModifier < 0) {
		std::cout << "Parameter: 'resourceModifier' is smaller than 0";
		return;
	}

	if (currentValue + resourceModifier > maxValue) {
		currentValue = maxValue;
	} else {
		currentValue += resourceModifier;
	}
}

int ResourceBar::getCurrentResource() {
	return currentValue;
}

int ResourceBar::getMaxResource() {
	return maxValue;
}

sf::Vector2f ResourceBar::getPosition() {
	return position;
}

void ResourceBar::setMaxResource(const int & newMaxResource) {
	maxValue = newMaxResource;
}

void ResourceBar::setCurrentResource(const int & newCurrentResource) {
	currentValue = newCurrentResource;
}

void ResourceBar::setBarColor(const sf::Color & newColor) {
	barColor = newColor;
	barInnerMeter.setFillColor(barColor);
}

void ResourceBar::setBarBackgroundColor(const sf::Color & newColor) {
	barBackground.setFillColor(newColor);
}

void ResourceBar::draw(sf::RenderWindow & window) {
	update();
	window.draw(barBackground);
	window.draw(barInnerMeter);
} 

void ResourceBar::draw(VirtualScreen & virtualWindow) {
	update();
	virtualWindow.drawSurfaceDraw(barBackground);
	virtualWindow.drawSurfaceDraw(barInnerMeter);
}