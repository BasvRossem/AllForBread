#pragma once

#include <string>
#include <functional>
#include "PointOfInterest.hpp"
#include "../states/State.hpp"
#include "../Character/Party.hpp"

class PointOfInterestContainer {
private:
	Party& party;
	std::vector<std::shared_ptr<PointOfInterest>> POIList;
	std::vector<std::shared_ptr<PointOfInterest>> visiblePoint;
public:
	PointOfInterestContainer(Party & party);
	void add(const sf::Vector2f &position, const float &size, const sf::Color & color, const std::string &locationType, const std::function<void()> & function, std::vector<sf::Vector2f> path);
	void activate();
	void nextVisblepoint();
	void forward();
	void back();
	void draw(sf::RenderWindow & window);
	sf::Vector2f getCurrentPointLocation();
	std::vector<sf::Vector2f> getForwardPath();
	std::vector<sf::Vector2f> getBackPath();
};

