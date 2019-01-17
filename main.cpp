#include <iostream>

#include <string>

#include <SFML/Graphics.hpp>
#include "PointsOfIntrest/PointOfInterest.hpp"
#include "PointsOfIntrest/pointOfInterestContainer.hpp"
#include "background.hpp"
#include "TransformableMovement/TransformableMovement.hpp"

int main( int argc, char *argv[] ){
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "The Holy Bread of Takatiki");
	window.setFramerateLimit(0);

	sf::Vector2f POI1Pos = sf::Vector2f(600, 675);
	std::vector<sf::Vector2f> path = { sf::Vector2f(600, 675), sf::Vector2f(644, 713), sf::Vector2f(688, 747), sf::Vector2f(748, 775), sf::Vector2f(814, 793), sf::Vector2f(878, 790), sf::Vector2f(950, 772) };
	std::vector<sf::Vector2f> notPath = {};
	sf::Vector2f POI2Pos = sf::Vector2f(950, 772);
	float POI1Size = 15;
	sf::Color POI1Color = sf::Color::Black;
	std::string POI1LocationType = "Battle";
	std::function<void(std::string)> cout1;

	PointOfInterestContainer poiCont;
	poiCont.add(POI1Pos, POI1Size, POI1Color, POI1LocationType, cout1, path);
	poiCont.add(POI2Pos, POI1Size, POI1Color, POI1LocationType, cout1, notPath);
	std::string takatikimap = "takatiki";
	std::string backgroundImage = "takatikimap.png";
	BackGround background;

	background.add(takatikimap, backgroundImage);
	background.SetBackGround(takatikimap, window);

	std::shared_ptr<sf::RectangleShape> partey(new sf::RectangleShape);
	sf::Vector2f abh(20, 20);
	sf::Vector2f newLocation;
	newLocation = poiCont.getCurrentPointLocation();
	partey->setSize(abh);
	partey->setPosition(newLocation);
	partey->setFillColor(sf::Color::Black);

	TransformableMovement POIMove(partey, newLocation, 0.0f);
	POIMove.blend();



	std::vector<sf::Vector2f> moveList;
	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed){
				if (event.key.code == sf::Keyboard::D && moveList.size() == 0) {
					std::vector<sf::Vector2f> temp = poiCont.getForwardPath();
					poiCont.forward();
					if (temp.size() > 0){
						for (size_t i = 0; i < temp.size(); i++){
							moveList.insert(moveList.begin(), temp[i]);
						}
					}
					
				}
				if (event.key.code == sf::Keyboard::A && moveList.size() == 0) {
					std::vector<sf::Vector2f> temp = poiCont.getBackPath();
					poiCont.back();
					if (temp.size() > 0) {
						for (size_t i = 0; i < temp.size(); i++) {
							moveList.insert(moveList.begin(), temp[i]);
						}
					}

				}
			}

		}
		
		if (moveList.size() > 0 && POIMove.isFinished()){
			POIMove = TransformableMovement(partey, moveList.back(), 1.0f);
			moveList.pop_back();
			POIMove.blend();
		}
		if (!POIMove.isFinished()) {
			POIMove.update();
		}
		/*if (!POIMove.isFinished()){
			POIMove.update();
		}else if (partey->getPosition() != newLocation) {
			POIMove = TransformableMovement(partey, newLocation, 4.0f);
			POIMove.blend();
		}else {
			poiCont.next();
			newLocation = poiCont.getCurrentPointLocation();
		}*/
		window.clear();
		background.draw(window);
		poiCont.draw(window);
		window.draw(*partey);
		window.display();
	}

	return 0;
}

