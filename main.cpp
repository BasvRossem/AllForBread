#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "PointsOfIntrest/PointOfInterest.hpp"
#include "PointsOfIntrest/pointOfInterestContainer.hpp"
#include "core/background.hpp"
#include "TransformableMovement/TransformableMovement.hpp"
#include "Core/KeyboardHandler.hpp"
#include "Character/Party.hpp"
#include "states/Combat.hpp"
#include "dataManager/DataManager.hpp"
#include <map>

int main( int argc, char *argv[] ){
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "The Holy Bread of Takatiki");
	window.setFramerateLimit(60);

	DataManager DM("dataManager/data.db");

	/*std::shared_ptr<PlayerCharacter> testCharacter = std::make_shared<PlayerCharacter>("Anubis, the distructor of hopes and dreams", "Assets/AnubisIdle.png");
	testCharacter->addCombatAction(std::make_shared<Attack>("Zwaardslag", 12));*/
	
	std::shared_ptr<Character> testMonster = std::make_shared<Character>("Big Nick Digga Jim", "Assets/RobotIdle.png", 12);
	testMonster->makeMonster();
	/*std::vector<std::shared_ptr<PlayerCharacter>> heroVector = { testCharacter };*/

	std::vector<std::shared_ptr<Character>> monsterVector = { testMonster };
	CharacterContainer<std::shared_ptr<Character>> monsters = (monsterVector);
	/*Party heroParty(heroVector);*/

	Party* hParty;


	DM.load(hParty);

	Party heroParty = *hParty;
	delete hParty;
	

	std::string combatBackground = "combatBackGround";
	std::string combatBackgroundImage = "Assets/background680.png";

	std::string takatikimap = "takatiki";
	std::string backgroundImage = "takatikimap.png";

	BackGround background;

	background.add(takatikimap, backgroundImage);
	background.add(combatBackground, combatBackgroundImage);

	Combat testCombat(window, heroParty, monsters, combatBackground, background);

	std::function<void()> cout1 = [&testCombat]() {testCombat.update(); };



	std::map<std::string, std::function<void()>> functions;
	functions["function1"] = [&testCombat]() {testCombat.update(); };

	PointOfInterestContainer poiCont;

	std::pair< PointOfInterestContainer&, std::map<std::string, std::function<void()>>&> poibox(poiCont, functions);

	DM.load(poibox);
	//poiCont.add(POI1Pos, POI1Size, POI1Color, POI1LocationType, cout1, path);
	//poiCont.add(POI2Pos, POI1Size, POI1Color, POI1LocationType, cout1, notPath);


	background.setBackGround(takatikimap, window);

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
