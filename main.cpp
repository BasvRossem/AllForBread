#include <iostream>
#include <string>
#include <cstdlib>
#include <SFML/Graphics.hpp>

#include "Items/Weapon.hpp"
#include "Character/PlayerCharacter.hpp"
#include "Character/Monster.hpp"
#include "PointsOfInterest/PointOfInterest.hpp"
#include "PointsOfInterest/pointOfInterestContainer.hpp"
#include "core/background.hpp"
#include "TransformableMovement/TransformableMovement.hpp"
#include "Core/KeyboardHandler.hpp"
#include "Character/Party.hpp"
#include "states/Combat.hpp"
#include "Core/Menu.hpp"
#include "Inventory/InventoryDisplay.hpp"
#include "Character/Mob.hpp"



//=======================================================
// Dummy Functions (Ask Jens)
//=======================================================

std::string damageTypeText(const DamageTypes & type) {
	std::string toReturn;
	switch (type) {
	case DamageTypes::slashing:
		toReturn = "slashing";
		break;
	case DamageTypes::piercing:
		toReturn = "piercing";
		break;
	case DamageTypes::force:
		toReturn = "force";
		break;
	case DamageTypes::poison:
		toReturn = "poison";
		break;
	case DamageTypes::fire:
		toReturn = "fire";
		break;

	default:
		toReturn = "Generieke schade";
		break;
	}
	return toReturn;
}

std::string armorTypeText(const AbilityScores & slot) {
	std::string toReturn;
	switch (slot) {
	case AbilityScores::charisma:
		toReturn = "charisma";
		break;
	case AbilityScores::dexterity:
		toReturn = "dexterity";
		break;
	case AbilityScores::strength:
		toReturn = "dexterity";
		break;
	case AbilityScores::vitality:
		toReturn = "vitality";
		break;
	case AbilityScores::arcanism:
		toReturn = "arcanism";
		break;
	case AbilityScores::luck:
		toReturn = "luck";
		break;
	default:
		toReturn = "Generieke ability";
		break;
	}
	return toReturn;
}


int main( int argc, char *argv[] ){

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "The Holy Bread of Takatiki");
	window.setFramerateLimit(60);

	//=======================================================
	// Weapon testing
	//=======================================================
	
	Weapon zweihander(WeaponSlots::twohanded, std::pair<DamageTypes, int>(DamageTypes::slashing, 6));
	zweihander.addSecondaryDamageEffect(std::pair<DamageTypes, int>(DamageTypes::force, 3));
	zweihander.addSecondaryDamageEffect(std::pair<DamageTypes, int>(DamageTypes::fire, 3));
	zweihander.setName("Zweihander");
	
	Weapon dagger(WeaponSlots::twohanded, std::pair<DamageTypes, int>(DamageTypes::piercing, 2));
	dagger.addSecondaryDamageEffect(std::pair<DamageTypes, int>(DamageTypes::force, 4));
	dagger.addSecondaryDamageEffect(std::pair<DamageTypes, int>(DamageTypes::poison, 3));
	dagger.setName("Dagger");

	//=======================================================
	// Creating Character
	//=======================================================

	std::shared_ptr<PlayerCharacter> testCharacter = std::make_shared<PlayerCharacter>("Anubis", "Assets/AnubisIdle.png");
	std::shared_ptr<PlayerCharacter> testCharacter2 = std::make_shared<PlayerCharacter>("Bnubis", "Assets/AnubisIdle.png");
	std::shared_ptr<PlayerCharacter> testCharacter3 = std::make_shared<PlayerCharacter>("Cnubis", "Assets/AnubisIdle.png");
	std::shared_ptr<PlayerCharacter> testCharacter4 = std::make_shared<PlayerCharacter>("Dnubis", "Assets/AnubisIdle.png");

	std::shared_ptr<Monster> testMonster = std::make_shared<Monster>("Big Nick Digga Jim", "Assets/RobotIdle.png", 12);
	testMonster->makeMonster();
	std::vector<std::shared_ptr<PlayerCharacter>> heroVector = { testCharacter, testCharacter2, testCharacter3, testCharacter4 };

	std::vector<std::shared_ptr<Monster>> monsterVector = { testMonster };
	Mob monsters = (monsterVector);
	Party heroParty(heroVector);


	//=======================================================
	// Creating items
	//=======================================================

	Item stick;
	stick.setName("Stick of Truth");
	
	Weapon pointyStick;
	pointyStick.setName("Slightly pointy stick");

	Armor boots;
	boots.setName("Normal boots");

	heroParty.addToInventory(std::make_shared<Item>(stick));
	heroParty.addToInventory(std::make_shared<Weapon>(pointyStick));
	heroParty.addToInventory(std::make_shared<Armor>(boots));


	//=======================================================
	// Creating BackGround
	//=======================================================

	std::string combatBackground = "combatBackGround";
	std::string combatBackgroundImage = "Assets/background680.png";

	std::string takatikimap = "takatiki";
	std::string backgroundImage = "takatikimap.png";

	std::string menuBackGround = "menu";
	std::string menuBackGroundImage = "Assets/menu.jpg";

	BackGround background;

	background.add(takatikimap, backgroundImage);
	background.add(combatBackground, combatBackgroundImage);
	background.add(menuBackGround, menuBackGroundImage);

	//=======================================================
	// Creating Combat
	//=======================================================

	Combat testCombat(window, heroParty, monsters, combatBackground, background);
	
	//=======================================================
	// Creating Menu
	//=======================================================

	Menu testMenu(menuBackGround, background);

	std::function<void()> inventoryOpen = [&heroParty, &window]() {InventoryDisplay InventoryD(heroParty, window); InventoryD.use(); };
	std::function<void()> close = [&window]() {window.close(); };
	std::function<void()> niksFunctie = [](){};

	std::string inventoryImage = ("Assets/inventory.png");
	std::string saveImage = ("Assets/save.png");
	std::string loadImage = ("Assets/load.png");
	std::string closeImage = ("Assets/close.png");

	testMenu.addTile(inventoryImage, inventoryOpen);
	testMenu.addTile(saveImage, niksFunctie);
	testMenu.addTile(loadImage, niksFunctie);
	testMenu.addTile(closeImage, close);

	//=======================================================
	// Creating Point Of Interest
	//=======================================================

	sf::Vector2f POI1Pos = sf::Vector2f(600, 675);
	std::vector<sf::Vector2f> path = { sf::Vector2f(600, 675), sf::Vector2f(644, 713), sf::Vector2f(688, 747), sf::Vector2f(748, 775), sf::Vector2f(814, 793), sf::Vector2f(878, 790), sf::Vector2f(950, 772) };
	std::vector<sf::Vector2f> notPath = {};
	sf::Vector2f POI2Pos = sf::Vector2f(950, 772);
	float POI1Size = 15;
	sf::Color POI1Color = sf::Color::Black;
	std::string POI1LocationType = "Battle";

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
	std::vector<sf::Vector2f> moveList;

	//=======================================================
	// Creating KeyBoard Handler
	//=======================================================

	KeyboardHandler keyHandl;

	keyHandl.addListener(sf::Keyboard::Enter, [&]() { if (moveList.size() == 0 && POIMove.isFinished()) { poiCont.activate(); }; });
	
	keyHandl.addListener(sf::Keyboard::Escape, [&testMenu, &window]() {testMenu.update(window); });

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

	//=======================================================
	// Armor testing
	//=======================================================

	auto differences = zweihander.compareTo(dagger);
	std::cout << "Als je dagger equipped, volgen er de volgende verschillen.\n";

	for (auto & difference : differences) {
		if (std::get<2>(difference) == &zweihander) {
			std::cout << "Je verliest ";
		} else {
			std::cout << "Je krijgt ";
		}
		std::cout
			<< std::get<1>(difference)
			<< ' '
			<< damageTypeText(std::get<0>(difference))
			<< " schade!"
			<< '\n';
	}
	
	Armor chainmail(ArmorSlots::chestplate);
	chainmail.setName("Chainmail");
	chainmail.addPropertyModifier({ AbilityScores::charisma,	2 });
	chainmail.addPropertyModifier({ AbilityScores::strength,	4 });
	chainmail.addPropertyModifier({ AbilityScores::dexterity,	-2 });
	chainmail.addPropertyModifier({ AbilityScores::luck,		1 });
	chainmail.addPropertyModifier({ AbilityScores::vitality,	3 });
	Armor leather(ArmorSlots::chestplate);
	leather.setName("Leather chest armor +2");
	leather.addPropertyModifier({ AbilityScores::charisma,		1 });
	leather.addPropertyModifier({ AbilityScores::strength,		1 });
	leather.addPropertyModifier({ AbilityScores::dexterity,		5 });
	leather.addPropertyModifier({ AbilityScores::arcanism,		-1 });

	auto armorDifferences = chainmail.compareTo(leather);
	std::cout << "De volgende modifiers veranderen door het equippen van " << leather.getName() << '\n';
	for (auto & difference : armorDifferences) {
		if (std::get<1>(difference) < 0 ) {
			std::get<1>(difference) *= -1;
			if (std::get<2>(difference) == &chainmail) {
				std::cout << "Je krijgt ";
			} else {
				std::cout << "Je verliest ";
			}
		}
		else if (std::get<1>(difference) > 0) {
			if (std::get<2>(difference) == &chainmail) {
				std::cout << "Je verliest ";
			}
			else {
				std::cout << "Je krijgt ";
			}
		}
		else {
			std::cout << "Er gebeurt iets?:";
		}
		
		std::cout << std::get<1>(difference)
		<< ' '
		<< armorTypeText(std::get<0>(difference))
		<< " ability!"
		<< '\n';

	}
	//=======================================================
	// While Loop
	//=======================================================

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
			// calc random encounter
			int encounterChange = rand() % 100 + 1;
			if (encounterChange > 90){
				testMonster = std::make_shared<Monster>("U snap it is u", "Assets/AnubisIdle.png");
				testMonster->makeMonster();
				std::vector<std::shared_ptr<Monster>> monsterVector = { testMonster };
				Mob monsterParty(monsterVector);
				Combat testCombat(window, heroParty, monsterParty, combatBackground, background);
				std::cout << "QUEUEUEUE battle music" << '\n';
				std::cout << encounterChange << '\n';
				testCombat.update();
				
			}
			POIMove = TransformableMovement(partey, moveList.back(), 1.0f);
			moveList.pop_back();
			POIMove.blend();
		}
		else if (moveList.size() == 0 && POIMove.isFinished()) {
			//doe niks
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

