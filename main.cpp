/*
#include <SFML/Graphics.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include "Character/Party.hpp"
#include "states/Combat.hpp"
#include "Character/Monster.hpp"

int main(){

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "The Holy Bread of Takatiki", sf::Style::Fullscreen);
	window.setFramerateLimit(0);

	PlayerCharacter testCharacter = PlayerCharacter("Anubis, the distructor of hopes and dreams","Assets/AnubisIdle.png");
	Character testMonster= Character("Rupert, the Poopert Robot", "Assets/RobotIdle.png", 12);
	testMonster.makeMonster();

	std::vector<std::shared_ptr<PlayerCharacter>> heroVector = {std::make_shared<PlayerCharacter>(testCharacter)};

	std::vector< std::shared_ptr<Character>> monsterVector = { std::make_shared <Character>(testMonster) };
	CharacterContainer< std::shared_ptr<Character >> monsters = (monsterVector);
	Party heroParty(heroVector);

	std::string backgroundImage = "Assets/background680.png";
	Combat testCombat(window, heroParty, monsters, backgroundImage);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		
		testCombat.update();

		window.display();
	}
	return 0;
}
*/
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

int main( int argc, char *argv[] ){
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "The Holy Bread of Takatiki");
	window.setFramerateLimit(60);

	sf::Vector2f POI1Pos = sf::Vector2f(600, 675);
	std::vector<sf::Vector2f> path = { sf::Vector2f(600, 675), sf::Vector2f(644, 713), sf::Vector2f(688, 747), sf::Vector2f(748, 775), sf::Vector2f(814, 793), sf::Vector2f(878, 790), sf::Vector2f(950, 772) };
	std::vector<sf::Vector2f> notPath = {};
	sf::Vector2f POI2Pos = sf::Vector2f(950, 772);
	float POI1Size = 15;
	sf::Color POI1Color = sf::Color::Black;
	std::string POI1LocationType = "Battle";

	std::shared_ptr<PlayerCharacter> testCharacter = std::make_shared<PlayerCharacter>("Anubis, the distructor of hopes and dreams", "Assets/AnubisIdle.png");
	testCharacter->addCombatAction(std::make_shared<Attack>("Zwaardslag", 12));
	
	std::shared_ptr<Character> testMonster = std::make_shared<Character>("Big Nick Digga Jim", "Assets/RobotIdle.png", 12);
	testMonster->makeMonster();
	std::vector<std::shared_ptr<PlayerCharacter>> heroVector = { testCharacter };

	std::vector<std::shared_ptr<Character>> monsterVector = { testMonster };
	CharacterContainer<std::shared_ptr<Character>> monsters = (monsterVector);
	Party heroParty(heroVector);
	std::string combatBackground = "combatBackGround";
	std::string combatBackgroundImage = "Assets/background680.png";

	std::string takatikimap = "takatiki";
	std::string backgroundImage = "takatikimap.png";

	BackGround background;

	background.add(takatikimap, backgroundImage);
	background.add(combatBackground, combatBackgroundImage);

	Combat testCombat(window, heroParty, monsters, combatBackground, background);

	std::function<void()> cout1 = [&testCombat]() {testCombat.update(); };

	PointOfInterestContainer poiCont;
	poiCont.add(POI1Pos, POI1Size, POI1Color, POI1LocationType, cout1, path);
	poiCont.add(POI2Pos, POI1Size, POI1Color, POI1LocationType, cout1, notPath);


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
				/*if (event.key.code == sf::Keyboard::D && moveList.size() == 0) {
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

				}*/

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
