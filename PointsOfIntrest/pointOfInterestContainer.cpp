#include "pointOfInterestContainer.hpp"



void PointOfInterestContainer::add(const sf::Vector2f &position, const float &size, const sf::Color & color, const std::string &locationType, const std::function<void()> & function, std::vector<sf::Vector2f> path) {
	POIList.push_back(std::make_shared<PointOfInterest>(position, size, color, locationType, function, path));
}

void PointOfInterestContainer::activate() {
	POIList[currentPoint]->activate();
}

void PointOfInterestContainer::nextVisblepoint() {
	visiblePoint.push_back(std::shared_ptr<PointOfInterest>(POIList[visiblePoint.size()]));
}

void PointOfInterestContainer::forward() {
	std::cout << currentPoint << '\n';
	if (currentPoint < POIList.size() - 1) {
		currentPoint++;
	}
}

void PointOfInterestContainer::back() {
	if (currentPoint > 0) {
		currentPoint--;
	}
}

sf::Vector2f PointOfInterestContainer::getCurrentPointLocation() {
	return POIList[currentPoint]->getPosition();
}

void PointOfInterestContainer::draw(sf::RenderWindow & window) {
	for (const auto &p : POIList) {
		p->draw(window);
	}
}

std::vector<sf::Vector2f> PointOfInterestContainer::getForwardPath() {
	return POIList[currentPoint]->getPath();
}

std::vector<sf::Vector2f> PointOfInterestContainer::getBackPath() {
	std::cout << currentPoint << '\n';
	if(currentPoint > 0){
		std::vector<sf::Vector2f> temp = POIList[currentPoint-1]->getPath();
		std::reverse(temp.begin(), temp.end());
		return temp;
	}
	return std::vector<sf::Vector2f> {};
}