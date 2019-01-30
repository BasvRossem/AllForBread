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
#include "dataManager/DataManager.hpp"
#include "Character/AbilitySpeccing.hpp"
#include "Core/dialogTree.hpp"
#include "Character/PartyOverview.hpp"

int main(int argc, char *argv[]) {



void constructSellList(std::shared_ptr<DialogNode> shop, std::shared_ptr<DialogNode> returnPoint, Party & heroParty) {
	shop->removeAllOptions();
	std::stringstream currency;
	currency << "Current currency " << heroParty.getCurrency();
	shop->addDialogOption(std::make_shared<DialogOption>(currency.str(), shop));
	for (auto item : heroParty.getInventory()) {
		std::stringstream itemSellName;
		itemSellName << item->getName() << " (" << item->getBaseValue() << ")";
		shop->addDialogOption(std::make_shared<DialogOption>(itemSellName.str(), returnPoint, [&, item]() { heroParty.eraseItem(item); heroParty.addCurrency(item->getBaseValue()); /* good sound */}));
	}
	shop->addDialogOption(std::make_shared<DialogOption>("back", returnPoint));
}

void constructBuyList(std::shared_ptr<DialogNode> shop, std::shared_ptr<DialogNode> returnPoint, Party & heroParty, std::vector<std::shared_ptr<Item>> items) {
	shop->removeAllOptions();
	std::stringstream currency;
	currency << "Current currency " << heroParty.getCurrency();
	shop->addDialogOption(std::make_shared<DialogOption>(currency.str(), shop));
	for (auto item : items) { 
		std::stringstream itemBuyName;
		itemBuyName << item->getName() << " (" << item->getBaseValue() << ")";
		shop->addDialogOption(std::make_shared<DialogOption>(itemBuyName.str(), returnPoint, [&, item]() {
			if (heroParty.getCurrency() >= item->getBaseValue()) {
				heroParty.addToInventory(item);
				heroParty.decreaseCurrency(item->getBaseValue());
				// #mergefix good sound
			}else {
				// #mergefix bad sound
			}
		}));
	}
	shop->addDialogOption(std::make_shared<DialogOption>("back", returnPoint));
}

int main( int argc, char *argv[] ){

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "The Holy Bread of Takatiki");
	window.setFramerateLimit(60);
	//=======================================================
	// OverWorld dialog box
	//=======================================================

	DialogBox overWorldDialog(window, 75, 10, "Assets/arial.ttf", sf::Vector2i{ 900, 400 }, sf::Vector2f{ 510, 680 }, sf::Color::Black);
	overWorldDialog.setSound("Assets/key.wav");

	DataManager DM("dataManager/data.db");

	//=======================================================
	// Weapon testing
	//=======================================================

	std::map<std::string, Weapon> weapons;

	DM.load(weapons);

	Weapon zweihander = weapons["zweihander"];
	Weapon dagger = weapons["dagger"];


	//=======================================================
	// Creating Character
	//=======================================================


	std::shared_ptr<Monster> testMonster = std::make_shared<Monster>("Big Nick Digga Jim", "Assets/RobotIdle.png", 12);
	testMonster->makeMonster();
	std::vector<std::shared_ptr<Monster>> monsterVector = { testMonster };
	Mob monsters = (monsterVector);

	Party *hParty;
	DM.load(hParty);
	Party heroParty = *hParty;
	delete hParty;

	heroParty.clearInventory();

	DM.load(heroParty);


	DM.save(heroParty);

	heroParty[0]->setPortraitFilename("Anubis_head.png");
	testCharacter2->setPortraitFilename("Barbarian_head.png");
	testCharacter3->setPortraitFilename("Black_Wizard_head.png");
	testCharacter4->setPortraitFilename("Blacksmith_head.png");

	//=======================================================
	// Creating items
	//=======================================================

	std::map<std::string, Item> items;
	std::map<std::string, Armor> armor;

	DM.load(items, armor);

	Item stick = items["Stick of Truth"];
	
	Weapon pointyStick = weapons["Slightly pointy stick"];

	Armor boots = armor["Normal boots"];

	Armor wingedBoots;
	wingedBoots.setName("Winged boots");
	wingedBoots.setArmorSlot(ArmorSlots::boots);
	wingedBoots.setMagicalProtection(5);
	wingedBoots.setPhysicalProtection(3);
	wingedBoots.addPropertyModifier(std::pair<AbilityScores, int>(AbilityScores::dexterity, 5));

	Armor juggernaut;
	juggernaut.setName("The Juggernaut");
	juggernaut.setArmorSlot(ArmorSlots::chestplate);
	juggernaut.setPhysicalProtection(12);
	juggernaut.addPropertyModifier(std::pair<AbilityScores, int>(AbilityScores::strength, 3));
	juggernaut.addPropertyModifier(std::pair<AbilityScores, int>(AbilityScores::dexterity, -3));

	Armor poorlyFittedClothing;
	poorlyFittedClothing.setName("Poorly fitting clothes");
	poorlyFittedClothing.setArmorSlot(ArmorSlots::helmet);
	poorlyFittedClothing.addPropertyModifier(std::pair<AbilityScores, int>(AbilityScores::charisma, -5));

	Weapon thunderfury;
	thunderfury.setName("Thunderfury, Blessed blade of the Windseeker");
	thunderfury.setPrimaryDamageEffect(std::pair<DamageTypes, int>(DamageTypes::lightning, 5));
	thunderfury.addSecondaryDamageEffect(std::pair<DamageTypes, int>(DamageTypes::thunder, 2));
	thunderfury.setWeaponSlot(WeaponSlots::twohanded);

	Weapon sting;
	sting.setName("Sting");
	sting.setPrimaryDamageEffect(std::pair<DamageTypes, int>(DamageTypes::piercing, 5));
	sting.setWeaponSlot(WeaponSlots::mainhand);

	Weapon defender;
	defender.setName("Dragon defender");
	defender.setPrimaryDamageEffect(std::pair<DamageTypes, int>(DamageTypes::lightning, 5));
	defender.setWeaponSlot(WeaponSlots::offhand);


	Consumable apple;
	apple.setName("Appel");
	apple.setQuantityUses(2);
	apple.setAction(std::function<void()>([&heroParty]() {
		auto lowest = heroParty[0];
		for (unsigned int i = 0; i < heroParty.size(); i++) {
			if (heroParty[i]->getHealth() < lowest->getHealth()) {
				lowest = heroParty[i];
			}
		}
		lowest->increaseHealth(2);
	}));

	heroParty.addToInventory(std::make_shared<Item>(stick));
	heroParty.addToInventory(std::make_shared<Weapon>(pointyStick));
	heroParty.addToInventory(std::make_shared<Weapon>(thunderfury));
	heroParty.addToInventory(std::make_shared<Weapon>(sting));
	heroParty.addToInventory(std::make_shared<Weapon>(defender));
	heroParty.addToInventory(std::make_shared<Armor>(boots));
	heroParty.addToInventory(std::make_shared<Armor>(wingedBoots));
	heroParty.addToInventory(std::make_shared<Armor>(juggernaut));
	heroParty.addToInventory(std::make_shared<Armor>(poorlyFittedClothing));
	heroParty.addToInventory(std::make_shared<Consumable>(apple));


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

	Menu menu(menuBackGround, background);


	std::function<void()> inventoryFunctie = [&heroParty, &window]() {InventoryDisplay InventoryD(heroParty, window); InventoryD.use(); };
	std::function<void()> partyFunctie = []() {};
	std::function<void()> saveFunctie = []() {};
	std::function<void()> loadFunctie = []() {};
	std::function<void()> closeFunctie = [&window]() {window.close(); };


	std::string inventoryImage = ("Assets/inventory.png");
	std::string partyImage = ("");
	std::string saveImage = ("Assets/save.png");
	std::string loadImage = ("Assets/load.png");
	std::string closeImage = ("Assets/close.png");
	

	menu.addTile(inventoryImage, inventoryFunctie);
	menu.addTile(partyImage, partyFunctie);
	menu.addTile(saveImage, saveFunctie);
	menu.addTile(loadImage, loadFunctie);
	menu.addTile(closeImage, closeFunctie);

	//=======================================================
	// shops
	//=======================================================
	
	

	std::shared_ptr<DialogNode> shopDialogNode0(new DialogNode("Do you wish to buy or sell items?"));
	std::shared_ptr<DialogNode> shopDialogBuyNode(new DialogNode("What item do you wish to buy?"));
	std::shared_ptr<DialogNode> shopDialogSellNode(new DialogNode("What item do you wish to sell?"));

	std::function<void()> buyFunc = [&] {constructBuyList(shopDialogBuyNode, shopDialogNode0, heroParty, heroParty.getInventory() ); };// #mergefix get all  items
	shopDialogNode0->addDialogOption(std::make_shared<DialogOption>("Buy", shopDialogBuyNode, buyFunc));
	std::function<void()> sellFunc = [&] {constructSellList(shopDialogSellNode, shopDialogNode0, heroParty); };
	shopDialogNode0->addDialogOption(std::make_shared<DialogOption>("Sell", shopDialogSellNode, sellFunc));
	


	//=======================================================
	// Functional Buildings
	//=======================================================
	
	// Windmill
	std::shared_ptr<DialogNode> windmillDialog0(new DialogNode("You come across a lonely windmill. The blades turn in the wind. Do you want to get closer to the windmill?"));
	std::shared_ptr<DialogNode> windmillDialog1(new DialogNode("You get closer to the windmill and notice that the door is open. Do you want to go into the windmill?"));
	std::shared_ptr<DialogNode> windmillDialog2(new DialogNode("You enter the windmill and see the millstones used to mill the grain. Do you wish to mill you breadcrumbs?"));
	std::shared_ptr<DialogNode> windmillDialog3(new DialogNode("You mill all your crumbs. Well done. All your crumbs are gone."));
	std::shared_ptr<DialogNode> windmillDialog4(new DialogNode("You walk away from the windmill."));
	std::shared_ptr<DialogNode> windmillDialog5(new DialogNode("You walk away from the windmill. Without your crumbs."));

	std::function<void()> removeAllCrumbs = [&] { int partyCurrenyAmount = heroParty.getCurrency(); heroParty.decreaseCurrency(partyCurrenyAmount); };

	windmillDialog0->addDialogOption(std::make_shared<DialogOption>("Yes", windmillDialog1));
	windmillDialog0->addDialogOption(std::make_shared<DialogOption>("No, walk away", windmillDialog4));

	windmillDialog1->addDialogOption(std::make_shared<DialogOption>("Yes", windmillDialog2));
	windmillDialog1->addDialogOption(std::make_shared<DialogOption>("No, walk away", windmillDialog4));

	windmillDialog2->addDialogOption(std::make_shared<DialogOption>("Yes", windmillDialog3, removeAllCrumbs));
	windmillDialog2->addDialogOption(std::make_shared<DialogOption>("No, I know what's going to happen. Walk away.", windmillDialog4));
	
	windmillDialog3->addDialogOption(std::make_shared<DialogOption>("Wait, what? Screw this I'm gone", windmillDialog5));
	
	DialogTree windmillTree;
	windmillTree.addNode(windmillDialog0);
	windmillTree.addNode(windmillDialog1);
	windmillTree.addNode(windmillDialog2);
	windmillTree.addNode(windmillDialog3);
	windmillTree.addNode(windmillDialog4);
	windmillTree.addNode(windmillDialog5);

	// Water well
	std::shared_ptr<DialogNode> waterWellDialog0(new DialogNode("You come across a well full of water. Would you like a drink?"));
	std::shared_ptr<DialogNode> waterWellDialog1(new DialogNode("You take a drink. The water feels refreshing. Maybe a little bit too refreshing. Your mind clears it's so refreshing. You realise that this isn't real. You are in a game! You quickly look for a way out. While running around you bump you head. That looks painful. Are you okay?"));
	std::shared_ptr<DialogNode> waterWellDialog2(new DialogNode("You stand up and feel a bit dizzy. You stand next to a well. Would you like a drink?"));
	std::shared_ptr<DialogNode> waterWellDialog3(new DialogNode("That looks awful as well. Maybe you should take a little rest."));
	std::shared_ptr<DialogNode> waterWellDialog4(new DialogNode("You wake up, witout the well in sight. It's probably nothing. You walk away."));
	std::shared_ptr<DialogNode> waterWellDialog5(new DialogNode("After a little rest, you walk away. Leaving the well behind"));
	std::shared_ptr<DialogNode> waterWellDialog6(new DialogNode("You take a drink and feel better. This was a good drink. You walk away."));
	std::shared_ptr<DialogNode> waterWellDialog7(new DialogNode("You walk away."));
	std::shared_ptr<DialogNode> waterWellDialog8(new DialogNode("Your head still hurts, but you still walk away."));

	waterWellDialog0->addDialogOption(std::make_shared<DialogOption>("Yes", waterWellDialog1));
	waterWellDialog0->addDialogOption(std::make_shared<DialogOption>("No", waterWellDialog7));
	waterWellDialog1->addDialogOption(std::make_shared<DialogOption>("I'm fine", waterWellDialog2));
	waterWellDialog1->addDialogOption(std::make_shared<DialogOption>("I feel awful", waterWellDialog3));
	waterWellDialog2->addDialogOption(std::make_shared<DialogOption>("Yes, it looks refreshing", waterWellDialog6));
	waterWellDialog2->addDialogOption(std::make_shared<DialogOption>("No, thank you", waterWellDialog8));
	waterWellDialog3->addDialogOption(std::make_shared<DialogOption>("Zzz", waterWellDialog4));
	waterWellDialog3->addDialogOption(std::make_shared<DialogOption>("I'm fine, I'm fine", waterWellDialog8));

	DialogTree waterWellTree;
	waterWellTree.addNode(waterWellDialog0);
	waterWellTree.addNode(waterWellDialog1);
	waterWellTree.addNode(waterWellDialog2);
	waterWellTree.addNode(waterWellDialog3);
	waterWellTree.addNode(waterWellDialog4);
	waterWellTree.addNode(waterWellDialog5);
	waterWellTree.addNode(waterWellDialog6);
	waterWellTree.addNode(waterWellDialog7);
	waterWellTree.addNode(waterWellDialog8);
	//=======================================================
	// Creating Point Of Interest
	//=======================================================
	std::map<std::string, std::function<void()>> functions;
	functions["function1"] = [&testCombat]() {testCombat.update(); };


	PointOfInterestContainer poiCont;

	std::pair< PointOfInterestContainer&, std::map<std::string, std::function<void()>>&> poibox(poiCont, functions);



	//city dialog
	DialogTree cityDialogPoint1;
	functions["cityDialogPoint1"] = [&cityDialogPoint1, &overWorldDialog]() {cityDialogPoint1.performDialogue(overWorldDialog); };
	DM.load(poibox);

	std::shared_ptr<DialogNode> cityDialogPoint1Node0(new DialogNode("Do you wish to enter Villageville?"));
	std::shared_ptr<DialogNode> cityDialogPoint1Node1(new DialogNode("What do you want to visit in Villageville?"));
	std::shared_ptr<DialogNode> cityDialogPoint1BankNode(new DialogNode("We are sorry the bank is under construction"));
	std::shared_ptr<DialogNode> cityDialogPoint1SmithNode(new DialogNode("We are sorry the smith is under construction"));
	std::shared_ptr<DialogNode> cityDialogPoint1RandomHouseNode(new DialogNode("The houses look generic and boring, like they have been copied and pasted."));

	cityDialogPoint1Node0->addDialogOption(std::make_shared<DialogOption>("Yes", cityDialogPoint1Node1));
	cityDialogPoint1Node0->addDialogOption(std::make_shared<DialogOption>("No", std::shared_ptr<DialogNode>(nullptr)));

	cityDialogPoint1Node1->addDialogOption(std::make_shared<DialogOption>("Bank", cityDialogPoint1BankNode));
	cityDialogPoint1Node1->addDialogOption(std::make_shared<DialogOption>("Shop", shopDialogNode0));
	cityDialogPoint1Node1->addDialogOption(std::make_shared<DialogOption>("Smith", cityDialogPoint1SmithNode));
	cityDialogPoint1Node1->addDialogOption(std::make_shared<DialogOption>("Houses", cityDialogPoint1RandomHouseNode));
	cityDialogPoint1Node1->addDialogOption(std::make_shared<DialogOption>("Leave VillageVille", std::shared_ptr<DialogNode>(nullptr)));

	cityDialogPoint1BankNode->addDialogOption(std::make_shared<DialogOption>("back", cityDialogPoint1Node1));

	cityDialogPoint1SmithNode->addDialogOption(std::make_shared<DialogOption>("back", cityDialogPoint1Node1));

	cityDialogPoint1RandomHouseNode->addDialogOption(std::make_shared<DialogOption>("back", cityDialogPoint1Node1));

	cityDialogPoint1.addNode(cityDialogPoint1Node0);
	cityDialogPoint1.addNode(cityDialogPoint1Node1);
	cityDialogPoint1.addNode(cityDialogPoint1BankNode);
	cityDialogPoint1.addNode(cityDialogPoint1SmithNode);
	cityDialogPoint1.addNode(cityDialogPoint1RandomHouseNode);

	// we need to fix dis
	shopDialogNode0->addDialogOption(std::make_shared<DialogOption>("back", cityDialogPoint1Node1));
	//

	//end city dialog
	sf::Vector2f POI1Pos = sf::Vector2f(600, 675);
	std::vector<sf::Vector2f> path = { sf::Vector2f(600, 675), sf::Vector2f(644, 713), sf::Vector2f(688, 747), sf::Vector2f(748, 775), sf::Vector2f(814, 793), sf::Vector2f(878, 790), sf::Vector2f(950, 772) };
	std::vector<sf::Vector2f> notPath = {};
	sf::Vector2f POI2Pos = sf::Vector2f(950, 772);
	float POI1Size = 15;
	sf::Color POI1Color = sf::Color::Black;
	std::string POI1LocationType = "Battle";

	std::function<void()> combatPoint2 = [&testCombat]() {testCombat.update(); };

	std::function<void()> cityPoint1 = [&]() {cityDialogPoint1.performDialogue(overWorldDialog); };

	poiCont.add(POI1Pos, POI1Size, POI1Color, POI1LocationType, cityPoint1, path);
	poiCont.add(POI2Pos, POI1Size, POI1Color, POI1LocationType, combatPoint2, notPath);


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

	//keyHandl.addListener(sf::Keyboard::I, [&]() { AbilitySpeccing a(testCharacter, window); a.resetAbilits(); a.use(window); });

	keyHandl.addListener(sf::Keyboard::Enter, [&]() { if (moveList.size() == 0 && POIMove.isFinished()) { poiCont.activate(); }; });
	
	keyHandl.addListener(sf::Keyboard::Escape, [&menu, &window]() {menu.update(window); });

	keyHandl.addListener(sf::Keyboard::C, [&heroParty, &window, &background, &takatikimap]() {
		PartyOverview overview(heroParty, background, takatikimap);
		overview.open(window);
	});


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
			<< EnumMethods::getDamageTypeName(std::get<0>(difference))
			<< " schade!"
			<< '\n';
	}
	
	Armor chainmail = armor["Chainmail"];

	Armor leather = armor["Leather chest armor +2"];

	auto armorDifferences = chainmail.compareTo(leather);
	std::cout << "De volgende modifiers veranderen door het equippen van " << leather.getName() << '\n';
	for (auto & difference : armorDifferences) {
		if (std::get<1>(difference) < 0) {
			std::get<1>(difference) *= -1;
			if (std::get<2>(difference) == &chainmail) {
				std::cout << "Je krijgt ";
			} else {
				std::cout << "Je verliest ";
			}
		} else if (std::get<1>(difference) > 0) {
			if (std::get<2>(difference) == &chainmail) {
				std::cout << "Je verliest ";
			} else {
				std::cout << "Je krijgt ";
			}
		} else {
			std::cout << "Er gebeurt iets?:";
		}

		std::cout << std::get<1>(difference)
			<< ' '
			<< EnumMethods::getAbilityScoreName(std::get<0>(difference))
			<< " ability!"
			<< '\n';

	}

	//=======================================================
	// NPC DIEalogue
	//=======================================================

	
	DialogTree randomEncounter;
	std::shared_ptr<DialogNode> randomEncounterNode0(new DialogNode("Good day Sir..."));
	std::shared_ptr<DialogNode> randomEncounterNode1(new DialogNode("I can't believe you've done this!"));

	randomEncounterNode0->addDialogOption(std::make_shared<DialogOption>("Good day", std::shared_ptr<DialogNode>(nullptr), [&]() {heroParty.addCurrency(4); }));
	randomEncounterNode0->addDialogOption(std::make_shared<DialogOption>("Fuck off", randomEncounterNode1));

	randomEncounter.addNode(randomEncounterNode0);
	randomEncounter.addNode(randomEncounterNode1);

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

			if (encounterChange > 90 && encounterChange < 95){
				testMonster = std::make_shared<Monster>("U snap it is u", "Assets/AnubisIdle.png");
				testMonster->makeMonster();
				std::vector<std::shared_ptr<Monster>> monsterVector = { testMonster };
				Mob monsterParty(monsterVector);
				Combat testCombat(window, heroParty, monsterParty, combatBackground, background);
				std::cout << "QUEUEUEUE battle music" << '\n';
				std::cout << encounterChange << '\n';
				testCombat.update();
			}else if (encounterChange > 0 && encounterChange < 5) {
				randomEncounter.performDialogue(overWorldDialog);
			}
			else if (encounterChange > 5 && encounterChange < 10) {
				waterWellTree.performDialogue(overWorldDialog, false, 0);
			}
			POIMove = TransformableMovement(partey, moveList.back(), 1.0f);
			moveList.pop_back();
			POIMove.blend();
		} else if (moveList.size() == 0 && POIMove.isFinished()) {
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
