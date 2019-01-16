#pragma once

#include <string>
#include <functional>
#include "PointOfIntrest.hpp"

class Points {
private:
	unsigned int currentPoint = 0;
	std::vector<std::shared_ptr<PointOfIntrest>> POIList;
	std::vector<std::shared_ptr<PointOfIntrest>> visiblePoint;
public:
	void add(const sf::Vector2f &position, const float &size, const sf::Color & color, const std::string &locationType, const std::function<void(std::string)> & function);
	void activate();
	void nextVisblepoint();
	void next();
	void back();
	void draw(sf::RenderWindow & window);
};

