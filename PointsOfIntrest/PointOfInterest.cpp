#include "PointOfInterest.hpp"



PointOfInterest::PointOfInterest(const sf::Vector2f &position, const float &size, const sf::Color & color, const std::string &locationType, const std::function<void(std::string)> & function, std::vector<sf::Vector2f> path) :
	size(size),
	position(position),
	locationType(locationType),
	function(function),
	path(path)
{
	point.setPosition(position);
	point.setRadius(size / 2);
	point.setFillColor(color);
}


void PointOfInterest::activate() {
	function(locationType);
}

void PointOfInterest::draw(sf::RenderWindow &window) {
	window.draw(point);
}

sf::Vector2f PointOfInterest::getPosition() {
	return position;
}

std::vector<sf::Vector2f> PointOfInterest::getPath() {
	return path;
}
