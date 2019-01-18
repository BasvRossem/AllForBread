#include "Points.hpp"



void Points::add(const sf::Vector2f &position, const float &size, const sf::Color & color, const std::string &locationType, const std::function<void(std::string)> & function) {
	POIList.push_back(std::make_unique<PointOfIntrest>(position, size, color, locationType, function));
}
void Points::activate() {
	visiblePoint[currentPoint]->activate();
}

void Points::nextVisblepoint() {
	visiblePoint.push_back(std::shared_ptr<PointOfIntrest>(POIList[visiblePoint.size()]));
}

void Points::next() {
	if (currentPoint < visiblePoint.size() - 1) {
		currentPoint++;
	}
}

void Points::back() {
	if (currentPoint > 0) {
		currentPoint--;
	}
}

void Points::draw(sf::RenderWindow & window) {
	for (auto &p : visiblePoint) {
		p->draw(window);
	}
}