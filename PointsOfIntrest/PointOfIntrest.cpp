#include "PointOfIntrest.hpp"



PointOfIntrest::PointOfIntrest(const sf::Vector2f &position, const float &size, const sf::Color & color, const std::string &locationType, const std::function<void(std::string)> & function) :
	size(size),
	position(position),
	locationType(locationType),
	function(function)
{
	point.setPosition(position);
	point.setRadius(size / 2);
	point.setFillColor(color);
}


void PointOfIntrest::activate() {
	function(locationType);
}

void PointOfIntrest::draw(sf::RenderWindow &window) {
	window.draw(point);
}
