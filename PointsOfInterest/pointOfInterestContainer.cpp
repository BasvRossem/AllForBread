#include "pointOfInterestContainer.hpp"



PointOfInterestContainer::PointOfInterestContainer(Party & party):
	party(party)
{}

void PointOfInterestContainer::add(const sf::Vector2f &position, const float &size, const sf::Color & color, const std::string &locationType, const std::function<void()> & function, std::vector<sf::Vector2f> path) {
	POIList.push_back(std::make_shared<PointOfInterest>(position, size, color, locationType, function, path));
}

void PointOfInterestContainer::activate() {
	POIList[party.getOverworldPosition()]->activate();
}

void PointOfInterestContainer::nextVisblepoint() {
	visiblePoint.push_back(std::shared_ptr<PointOfInterest>(POIList[visiblePoint.size()]));
}

void PointOfInterestContainer::forward() {
	std::cout << party.getOverworldPosition() << '\n';
	if (party.getOverworldPosition() < POIList.size() - 1) {
		party.setOverworldPosition(party.getOverworldPosition() + 1);
	}
}

void PointOfInterestContainer::back() {
	if (party.getOverworldPosition() > 0) {
		party.setOverworldPosition(party.getOverworldPosition() - 1);
	}
}

sf::Vector2f PointOfInterestContainer::getCurrentPointLocation() {
	return POIList[party.getOverworldPosition()]->getPosition();
}

void PointOfInterestContainer::draw(sf::RenderWindow & window) {
	for (const auto &p : POIList) {
		p->draw(window);
	}
}

std::vector<sf::Vector2f> PointOfInterestContainer::getForwardPath() {
	return POIList[party.getOverworldPosition()]->getPath();
}

std::vector<sf::Vector2f> PointOfInterestContainer::getBackPath() {
	std::cout << party.getOverworldPosition() << '\n';
	if(party.getOverworldPosition() > 0){
		std::vector<sf::Vector2f> temp = POIList[party.getOverworldPosition() -1]->getPath();
		std::reverse(temp.begin(), temp.end());
		return temp;
	}
	return std::vector<sf::Vector2f> {};
}