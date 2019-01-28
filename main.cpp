#include <iostream>
#include <string>
#include "Items/Weapon.hpp"
#include <SFML/Graphics.hpp>
#include "PointsOfInterest/PointOfInterest.hpp"
#include "PointsOfInterest/pointOfInterestContainer.hpp"
#include "core/background.hpp"
#include "TransformableMovement/TransformableMovement.hpp"
#include "Core/KeyboardHandler.hpp"
#include "Character/Party.hpp"
#include "states/Combat.hpp"
#include "Character/PartyOverview.hpp"


int main(int argc, char *argv[]) {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "The Holy Bread of Takatiki");
	window.setFramerateLimit(60);
	Weapon sword;


	sf::Vector2f POI1Pos = sf::Vector2f(600, 675);
	std::vector<sf::Vector2f> path = { sf::Vector2f(600, 675), sf::Vector2f(644, 713), sf::Vector2f(688, 747), sf::Vector2f(748, 775), sf::Vector2f(814, 793), sf::Vector2f(878, 790), sf::Vector2f(950, 772) };
	std::vector<sf::Vector2f> notPath = {};
	sf::Vector2f POI2Pos = sf::Vector2f(950, 772);
	float POI1Size = 15;
	sf::Color POI1Color = sf::Color::Black;
	std::string POI1LocationType = "Battle";

	std::shared_ptr<PlayerCharacter> testCharacter1 = std::make_shared<PlayerCharacter>("Anubis, the distructor of hopes and dreams", "Assets/AnubisIdle.png");
	std::shared_ptr<PlayerCharacter> testCharacter2 = std::make_shared<PlayerCharacter>("Bnubis, the spoiler of fields", "Assets/AnubisIdle.png");
	std::shared_ptr<PlayerCharacter> testCharacter3 = std::make_shared<PlayerCharacter>("Cnubis, the poor sidekick", "Assets/AnubisIdle.png");
	std::shared_ptr<PlayerCharacter> testCharacter4 = std::make_shared<PlayerCharacter>("Dnubis, the second poor sidekick", "Assets/AnubisIdle.png");

	testCharacter1->increaseExperience(5);
	testCharacter2->increaseExperience(15);
	testCharacter3->increaseExperience(55);
	testCharacter4->increaseExperience(95);

	testCharacter1->setPortraitFilename("Anubis_head.png");
	testCharacter2->setPortraitFilename("Barbarian_head.png");
	testCharacter3->setPortraitFilename("Black_Wizard_head.png");
	testCharacter4->setPortraitFilename("Blacksmith_head.png");

	std::shared_ptr<Character> testMonster = std::make_shared<Character>("Big Nick Digga Jim", "Assets/RobotIdle.png", 12);
	testMonster->makeMonster();
	std::vector<std::shared_ptr<PlayerCharacter>> heroVector = { testCharacter1, testCharacter2, testCharacter3, testCharacter4 };

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
	keyHandl.addListener(sf::Keyboard::C, [&heroParty, &window]() {
		PartyOverview overview(heroParty);
		overview.open(window); 
	});

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

	heroParty[0]->decreaseHealth(4);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				keyHandl.processKey(event.key.code);
			}

		}

		if (moveList.size() > 0 && POIMove.isFinished()) {
			POIMove = TransformableMovement(partey, moveList.back(), 1.0f);
			moveList.pop_back();
			POIMove.blend();
		}
		else if (moveList.size() == 0 && POIMove.isFinished()) {

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
