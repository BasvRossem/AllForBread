#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "PointsOfInterest/PointOfInterest.hpp"
#include "PointsOfInterest/pointOfInterestContainer.hpp"
#include "core/background.hpp"
#include "TransformableMovement/TransformableMovement.hpp"
#include "Core/KeyboardHandler.hpp"
#include "Character/Party.hpp"
#include "states/Combat.hpp"
#include "dataManager/DataManager.hpp"
#include <map>
#include "Items/Weapon.hpp"

int main( int argc, char *argv[] ){ 
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "The Holy Bread of Takatiki");
	window.setFramerateLimit(60);
  
  Weapon sword;

	DataManager DM("dataManager/data.db");
	
	std::shared_ptr<Character> testMonster = std::make_shared<Character>("Big Nick Digga Jim", "Assets/RobotIdle.png", 12);
	testMonster->makeMonster();

	std::vector<std::shared_ptr<Character>> monsterVector = { testMonster };
	CharacterContainer<std::shared_ptr<Character>> monsters = (monsterVector);

	Party* hParty;
	BackGround background;

	DM.load(hParty, background);

	Party heroParty = *hParty;
	delete hParty;

	Combat testCombat(window, heroParty, monsters, "combatBackGround", background);

	std::map<std::string, std::function<void()>> functions;
	functions["function1"] = [&testCombat]() {testCombat.update(); };

	PointOfInterestContainer poiCont;

	std::pair< PointOfInterestContainer&, std::map<std::string, std::function<void()>>&> poibox(poiCont, functions);

	DM.load(poibox);

	background.setBackGround("takatiki", window);

	std::shared_ptr<sf::RectangleShape> partey(new sf::RectangleShape);
	sf::Vector2f abh(20, 20);
	sf::Vector2f newLocation;
	newLocation = poiCont.getCurrentPointLocation();
	partey->setSize(abh);
	partey->setPosition(newLocation);
	partey->setFillColor(sf::Color::Black);

	TransformableMovement POIMove(partey, newLocation, 0.0f);
	POIMove.blend();

	KeyboardHandler keyHandl;

	keyHandl.addListener(sf::Keyboard::Enter, [&poiCont]() {poiCont.activate(); });

	std::vector<sf::Vector2f> moveList;
	keyHandl.addListener(sf::Keyboard::D, [&moveList, &poiCont]()->void {
		if (moveList.size() == 0) {
			std::vector<sf::Vector2f> temp = poiCont.getForwardPath();
			poiCont.forward();
			if (temp.size() > 0) {
				for (size_t i = 0; i < temp.size(); i++) {
					moveList.insert(moveList.begin(), temp[i]);
				}
			}
		}
	});

	keyHandl.addListener(sf::Keyboard::A, [&moveList, &poiCont]()->void {
		if (moveList.size() == 0) {
			std::vector<sf::Vector2f> temp = poiCont.getBackPath();
			poiCont.back();
			if (temp.size() > 0) {
				for (size_t i = 0; i < temp.size(); i++) {
					moveList.insert(moveList.begin(), temp[i]);
				}
			}
		}
	});

	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed){

				keyHandl.processKey(event.key.code);
			}

		}
		
		if (moveList.size() > 0 && POIMove.isFinished()){
			POIMove = TransformableMovement(partey, moveList.back(), 1.0f);
			moveList.pop_back();
			POIMove.blend();
		}else if (moveList.size() == 0 && POIMove.isFinished()) {

		}
		if (!POIMove.isFinished()) {
			POIMove.update();
		}

		window.clear();
		background.draw(window);
		poiCont.draw(window);
		window.draw(*partey);
		window.display();

	}
	return 0;
}
