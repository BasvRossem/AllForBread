#pragma once
#include <SFML/Graphics.hpp>
#include "../virtualScreen/virtualScreen.hpp"
#include <memory>
#include <iostream>
/// @file

/// Resourcebar class
/// Uses maximum value and currentvalue to calculate progress percentage
/// and display it in the shape of a bar
/// Default health bar config: 
/// size = (100.0f, 15.0f)
/// background color = white
/// inner meter color = red
class ResourceBar {
private:
	sf::RectangleShape barBackground;
	sf::RectangleShape barInnerMeter;

	sf::Vector2f position;
	sf::Vector2f size = sf::Vector2f(100.0f, 15.0f);

	sf::Color barColor;
	int maxValue;
	int currentValue;

public:
	// Resourcebar Constructor	(No color specified)
	ResourceBar(const sf::Vector2f & position, const sf::Vector2f & size, const int & maxValue, const int & currentValue, const sf::Color & barColor);

	// Healthbar constructor	(Default color red)
	ResourceBar(const sf::Vector2f & position, const int & maxValue, const int & currentValue);

	// Default constructor
	ResourceBar();

	/// \brief
	/// Repositions the resourcebar to given position
	void setPosition(const int & x, const int & y);

	/// \brief
	/// Repositions the resourcebar to given position
	void setPosition(const sf::Vector2f & newPosition);

	/// \brief
	/// Resizes the healthbar
	void resize(const int & x, const int & y);

	/// \brief
	/// Resizes the health bar
	void resize(const sf::Vector2f & newSize);

	/// \brief
	/// Updates the health bar
	void update();

	/// \brief
	/// Decreases the currentValue by given value
	void decreaseCurrentResource(const int & resourceModifier);

	/// \brief
	/// Increases the currentValue by given value
	void increaseCurrentResource(const int & resourceModifier);

	/// \brief
	/// Returns current resource value (currentValue)
	int getCurrentResource();

	/// \brief
	/// Returns max bar resource (maxValue)
	int getMaxResource();

	/// \brief 
	/// Returns sf::Vector2f position
	sf::Vector2f getPosition();

	/// \brief
	/// Sets max bar value to given value
	void setMaxResource(const int & newMaxResource);

	/// \brief
	/// Sets current resource to given value
	void setCurrentResource(const int & newCurrentResource);

	/// \brief
	/// Sets the resource bar color
	void setBarColor(const sf::Color & newColor);

	/// \brief
	/// Sets the background bar color
	void setBarBackgroundColor(const sf::Color & newColor);

	/// \brief
	/// Draws the bar on the screen
	void draw(sf::RenderWindow & window);

	/// brief
	/// Draws the bar on the virtual screen
	void draw(VirtualScreen & virtualWindow);
};