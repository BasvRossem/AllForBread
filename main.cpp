#include <iostream>
#include <string>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <stdio.h>

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
#include "Core/Sounds.hpp"

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
	shop->addDialogOption(std::make_shared<DialogOption>("Back", returnPoint));
}

void constructBuyList(std::shared_ptr<DialogNode> shop, std::shared_ptr<DialogNode> returnPoint, Party & heroParty, std::vector<std::shared_ptr<Item>> items) {
	shop->removeAllOptions();
	std::stringstream currency;
	currency << "Current currency " << heroParty.getCurrency();
	std::cout << currency.str();
	shop->addDialogOption(std::make_shared<DialogOption>(currency.str(), shop));
	for (auto item : items) { 
		std::stringstream itemBuyName;
		itemBuyName << item->getName() << " (" << item->getBaseValue() << ")";
		shop->addDialogOption(std::make_shared<DialogOption>(itemBuyName.str(), returnPoint, [&, item]() {
			if (heroParty.getCurrency() >= item->getBaseValue()) {
				std::shared_ptr<Weapon> itemWeapon = std::dynamic_pointer_cast<Weapon>(item);
				std::shared_ptr<Armor> itemArmor = std::dynamic_pointer_cast<Armor>(item);
				std::shared_ptr<Consumable> itemConsumable = std::dynamic_pointer_cast<Consumable>(item);
				std::shared_ptr<Item> itemCopy;
				if (itemWeapon != nullptr) {
					std::cout << "\nJe bent niet vergeten dat je een wapen bent :D\n";
					//itemCopy = std::make_shared<Item>(*itemWeapon);
					heroParty.addToInventory(std::make_shared<Weapon>(*itemWeapon));
					heroParty.decreaseCurrency(item->getBaseValue());
				}else if (itemArmor != nullptr) {
					std::cout << "\nJe bent niet vergeten dat je een armor bent :D\n";
					//itemCopy = std::make_shared<Item>(*itemArmor);
					heroParty.addToInventory(std::make_shared<Armor>(*itemArmor));
					heroParty.decreaseCurrency(item->getBaseValue());
				}else if (itemConsumable != nullptr) {
					heroParty.addToInventory(std::make_shared<Consumable>(*itemConsumable));
					heroParty.decreaseCurrency(item->getBaseValue());
				}
				else {
					std::cout << "\nJe bent vergeten wie je bent :(\n";
				}

				// #mergefix good sound
			}else {
				// #mergefix bad sound
			}
		}));
	}
	shop->addDialogOption(std::make_shared<DialogOption>("Back", returnPoint));
}



int main( int argc, char *argv[] ){
	srand(static_cast<unsigned int>(time(NULL)));
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "The Holy Bread of Takatiki", sf::Style::Fullscreen);
	window.setFramerateLimit(60);

	//=======================================================
	// Datamanager init
	//=======================================================
	std::map<std::string, std::function<void()>> functions;
	DataManager DM("dataManager/data.db", functions);


	//=======================================================
	// Loading screen
	//=======================================================
	sf::Font font;
	font.loadFromFile("Assets/PIXEARG_.ttf");
	sf::Text loadingText;
	loadingText.setFont(font);
	loadingText.setString("Loading... Please wait");
	loadingText.setCharacterSize(24);
	loadingText.setFillColor(sf::Color::White);
	loadingText.setOutlineColor(sf::Color::Black);
	loadingText.setPosition(sf::Vector2f(5.0f, 5.0f));
	
	window.clear();
	window.draw(loadingText);
	window.display();
	//=======================================================
	// Creating BackGround
	//=======================================================

	BackGround background;

	DM.load(background);

	//=======================================================
	// OverWorld dialog box
	//=======================================================

	DialogBox overWorldDialog(window, 75, 10, "Assets/arial.ttf", sf::Vector2i{ 900, 400 }, sf::Vector2f{ 510, 680 }, background, sf::Color::Black);
	overWorldDialog.setSound("SoundEffects/key.wav");


	//=======================================================
	// Sound and Music
	//=======================================================
	Sounds sound;
	bool playMenuTheme = true;
	sound.setMusicLoop(true);





	//=======================================================
	// Creating Character
	//=======================================================


	Party *hParty;
	DM.load(hParty);
	Party heroParty = *hParty;
	delete hParty;

	//=======================================================
	// Creating items
	//=======================================================

	std::map<std::string, Weapon> weapons;
	std::map<std::string, Item> items;
	std::map<std::string, Armor> armor;

	functions["heal1"] = [&heroParty]() {
		auto lowest = heroParty[0];
		for (unsigned int i = 0; i < heroParty.size(); i++) {
			if (heroParty[i]->getHealth() < lowest->getHealth()) {
				lowest = heroParty[i];
			}
		}
		lowest->increaseHealth(2);
	};

	DM.load(items, armor, weapons, heroParty);

	Item stick = items["Stick of Truth"];
	
	Weapon pointyStick = weapons["Slightly pointy stick"];

	Armor boots = armor["Normal boots"];



	//=======================================================
	// Creating Combat
	//=======================================================
	std::pair< std::string, std::string> anubisPair1;
	anubisPair1.first = "Assets/Anubis/Idle_all.png";
	anubisPair1.second = "Assets/Anubis/Idle_000.png";
	std::shared_ptr<Monster> testMonster1 = std::make_shared<Monster>("Jim", anubisPair1);
	testMonster1->setDeathAnimation("Assets/Anubis/Dying_all.png");
	std::vector<std::shared_ptr<Monster>> monsterVector1 = { testMonster1 };
	Mob monsters1 = (monsterVector1);

	Combat testCombat1(window, heroParty, monsters1, "combatBackGround", background);

	std::pair< std::string, std::string> anubisPair2;
	anubisPair2.first = "Assets/Anubis/Idle_all.png";
	anubisPair2.second = "Assets/Anubis/Idle_000.png";
	std::shared_ptr<Monster> testMonster2 = std::make_shared<Monster>("Jim", anubisPair2);
	testMonster2->setDeathAnimation("Assets/Anubis/Dying_all.png");
	std::vector<std::shared_ptr<Monster>> monsterVector2 = { testMonster2 };
	Mob monsters2 = (monsterVector2);

	Combat testCombat2(window, heroParty, monsters2, "combatBackGround", background);

	std::pair< std::string, std::string> anubisPair3;
	anubisPair3.first = "Assets/Anubis/Idle_all.png";
	anubisPair3.second = "Assets/Anubis/Idle_000.png";
	std::shared_ptr<Monster> testMonster3 = std::make_shared<Monster>("Jim", anubisPair3);
	testMonster3->setDeathAnimation("Assets/Anubis/Dying_all.png");
	std::vector<std::shared_ptr<Monster>> monsterVector3 = { testMonster3 };
	Mob monsters3 = (monsterVector3);

	Combat testCombat3(window, heroParty, monsters3, "combatBackGround", background);

	std::pair< std::string, std::string> anubisPair4;
	anubisPair4.first = "Assets/Anubis/Idle_all.png";
	anubisPair4.second = "Assets/Anubis/Idle_000.png";
	std::shared_ptr<Monster> testMonster4 = std::make_shared<Monster>("Jim", anubisPair4);
	testMonster4->setDeathAnimation("Assets/Anubis/Dying_all.png");
	std::vector<std::shared_ptr<Monster>> monsterVector4 = { testMonster4 };
	Mob monsters4 = (monsterVector4);

	Combat testCombat4(window, heroParty, monsters4, "combatBackGround", background);

	std::pair< std::string, std::string> anubisPair5;
	anubisPair5.first = "Assets/Anubis/Idle_all.png";
	anubisPair5.second = "Assets/Anubis/Idle_000.png";
	std::shared_ptr<Monster> testMonster5 = std::make_shared<Monster>("Jim", anubisPair5);
	testMonster5->setDeathAnimation("Assets/Anubis/Dying_all.png");
	std::vector<std::shared_ptr<Monster>> monsterVector5 = { testMonster5 };
	Mob monsters5 = (monsterVector5);

	Combat testCombat5(window, heroParty, monsters5, "combatBackGround", background);

	//=======================================================
	// Creating Menu
	//=======================================================

	Menu menu("menu", background);


	std::function<void()> inventoryFunctie = [&heroParty, &window]() {InventoryDisplay InventoryD(heroParty, window); InventoryD.use(); };
	std::function<void()> partyFunctie = [&heroParty, &window, &background]() {PartyOverview overview(heroParty, background, "takatiki");overview.open(window);};
	std::function<void()> saveFunctie = [&heroParty, &DM]() {DM.save(heroParty); };
	std::function<void()> loadFunctie = [&heroParty, &DM]() {DM.load(heroParty); };
	std::function<void()> closeFunctie = [&window]() {window.close(); };


	std::string inventoryImage = ("Assets/inventory.png");
	std::string partyImage = ("Assets/partyOverview.png");
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
	
	

	std::shared_ptr<DialogNode> shopDialogNode0(new DialogNode("Do you wish to buy or sell items?", "town"));
	std::shared_ptr<DialogNode> shopDialogBuyNode0(new DialogNode("What item do you wish to buy?", "town"));
	std::shared_ptr<DialogNode> shopDialogSellNode0(new DialogNode("What item do you wish to sell?", "town"));

	std::shared_ptr<DialogNode> smithDialogNode0(new DialogNode("Do you wish to buy or sell weapons and armor?", "town"));
	std::shared_ptr<DialogNode> smithDialogBuyNode0(new DialogNode("What item do you wish to buy?", "town"));
	std::shared_ptr<DialogNode> smithDialogSellNode0(new DialogNode("What item do you wish to sell?", "town"));

	std::shared_ptr<DialogNode> shopDialogNode1(new DialogNode("Do you wish to buy or sell items?", "town"));
	std::shared_ptr<DialogNode> shopDialogBuyNode1(new DialogNode("What item do you wish to buy?", "town"));
	std::shared_ptr<DialogNode> shopDialogSellNode1(new DialogNode("What item do you wish to sell?", "town"));

	std::shared_ptr<DialogNode> smithDialogNode1(new DialogNode("Do you wish to buy or sell weapons and armor?", "town"));
	std::shared_ptr<DialogNode> smithDialogBuyNode1(new DialogNode("What item do you wish to buy?", "town"));
	std::shared_ptr<DialogNode> smithDialogSellNode1(new DialogNode("What item do you wish to sell?", "town"));

	std::map<std::string, Armor> inventoryArmor;
	std::map<std::string, Weapon> inventoryWeapon;
	std::map<std::string, Consumable> inventoryConsumable;

	DM.load(inventoryWeapon, inventoryArmor, inventoryConsumable);

	std::vector<std::shared_ptr<Item>> blackSmithInventoryVector;
	std::vector<std::shared_ptr<Item>> shopInventoryVector;

	for (auto &item : inventoryArmor) {
		blackSmithInventoryVector.push_back(std::make_shared<Armor>(item.second));
	}

	for (auto &item : inventoryWeapon) {
		blackSmithInventoryVector.push_back(std::make_shared<Weapon>(item.second));
	}

	for (auto &item : inventoryConsumable) {
		shopInventoryVector.push_back(std::make_shared<Consumable>(item.second));
	}

	// town 1
	//shop
	std::function<void()> shopBuyFunc = [&] {constructBuyList(shopDialogBuyNode0, shopDialogNode0, heroParty, shopInventoryVector); };
	shopDialogNode0->addDialogOption(std::make_shared<DialogOption>("Buy", shopDialogBuyNode0, shopBuyFunc));
	std::function<void()> shopSellFunc = [&] {constructSellList(shopDialogSellNode0, shopDialogNode0, heroParty); };
	shopDialogNode0->addDialogOption(std::make_shared<DialogOption>("Sell", shopDialogSellNode0, shopSellFunc));
	//smith
	std::function<void()> smithBuyFunc = [&] {constructBuyList(smithDialogBuyNode0, smithDialogNode0, heroParty, blackSmithInventoryVector); };
	smithDialogNode0->addDialogOption(std::make_shared<DialogOption>("Buy", smithDialogBuyNode0, smithBuyFunc));
	std::function<void()> smithSellFunc = [&] {constructSellList(smithDialogSellNode0, smithDialogNode0, heroParty); };
	smithDialogNode0->addDialogOption(std::make_shared<DialogOption>("Sell", smithDialogSellNode0, smithSellFunc));
	// town 2
		//shop
	std::function<void()> shopBuyFunc1 = [&] {constructBuyList(shopDialogBuyNode1, shopDialogNode1, heroParty, shopInventoryVector); };
	shopDialogNode1->addDialogOption(std::make_shared<DialogOption>("Buy", shopDialogBuyNode1, shopBuyFunc1));
	std::function<void()> shopSellFunc1 = [&] {constructSellList(shopDialogSellNode1, shopDialogNode1, heroParty); };
	shopDialogNode1->addDialogOption(std::make_shared<DialogOption>("Sell", shopDialogSellNode1, shopSellFunc1));
	//smith
	std::function<void()> smithBuyFunc1 = [&] {constructBuyList(smithDialogBuyNode1, smithDialogNode1, heroParty, blackSmithInventoryVector); };
	smithDialogNode1->addDialogOption(std::make_shared<DialogOption>("Buy", smithDialogBuyNode1, smithBuyFunc1));
	std::function<void()> smithSellFunc1 = [&] {constructSellList(smithDialogSellNode1, smithDialogNode0, heroParty); };
	smithDialogNode1->addDialogOption(std::make_shared<DialogOption>("Sell", smithDialogSellNode1, smithSellFunc1));
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
	
	functions["combat1"] = [&]() { playMenuTheme = true; sound.stopMusic(); testCombat1.update(); };
	functions["combat2"] = [&]() { playMenuTheme = true; sound.stopMusic(); testCombat2.update(); };
	functions["combat3"] = [&]() { playMenuTheme = true; sound.stopMusic(); testCombat3.update(); };
	functions["combat4"] = [&]() { playMenuTheme = true; sound.stopMusic(); testCombat4.update(); };
	functions["combat5"] = [&]() { playMenuTheme = true; sound.stopMusic(); testCombat5.update(); };


	PointOfInterestContainer poiCont(heroParty);
	std::pair< PointOfInterestContainer&, std::map<std::string, std::function<void()>>&> poibox(poiCont, functions);



	//city dialog
	DialogTree cityDialogPoint1;
	DialogTree cityDialogPoint2;
	functions["cityDialogPoint1"] = [&cityDialogPoint1, &overWorldDialog]() {cityDialogPoint1.performDialogue(overWorldDialog); };
	functions["cityDialogPoint2"] = [&cityDialogPoint2, &overWorldDialog]() {cityDialogPoint2.performDialogue(overWorldDialog); };
	
	DM.load(poibox);

	///start town 1
	std::shared_ptr<DialogNode> cityDialogPoint1Node0(new DialogNode("Do you wish to enter Villageville?"));
	std::shared_ptr<DialogNode> cityDialogPoint1Node1(new DialogNode("What do you want to visit in Villageville?", "town"));
	std::shared_ptr<DialogNode> cityDialogPoint1BankNode(new DialogNode("We are sorry the bank is under construction", "town"));
	std::shared_ptr<DialogNode> cityDialogPoint1SmithNode(new DialogNode("We are sorry the smith is under construction", "town"));
	std::shared_ptr<DialogNode> cityDialogPoint1ChurchNode0(new DialogNode("You enter the church, do you wish to respec your ability points", "church"));
	std::shared_ptr<DialogNode> cityDialogPoint1ChurchNode1(new DialogNode("Which character do you wish to respec?", "church"));
	std::shared_ptr<DialogNode> cityDialogPoint1RandomHouseNode(new DialogNode("The houses look generic and boring, like they have been copied and pasted.", "town"));

	cityDialogPoint1Node0->addDialogOption(std::make_shared<DialogOption>("Yes", cityDialogPoint1Node1));
	cityDialogPoint1Node0->addDialogOption(std::make_shared<DialogOption>("No", std::shared_ptr<DialogNode>(nullptr)));

	cityDialogPoint1ChurchNode0->addDialogOption(std::make_shared<DialogOption>("yes", cityDialogPoint1ChurchNode1));
	cityDialogPoint1ChurchNode0->addDialogOption(std::make_shared<DialogOption>("no", cityDialogPoint1Node1));

	for (size_t i = 0; i < heroParty.size(); i++){
		cityDialogPoint1ChurchNode1->addDialogOption(std::make_shared<DialogOption>(heroParty[i]->getName(), cityDialogPoint1Node1, [&heroParty, i, &window, &background]() {AbilitySpeccing a(heroParty[i], window, background, "church"); a.resetAbilits(); a.use(window); window.clear(sf::Color::Transparent); }));
	}



	cityDialogPoint1Node1->addDialogOption(std::make_shared<DialogOption>("Bank", cityDialogPoint1BankNode));
	cityDialogPoint1Node1->addDialogOption(std::make_shared<DialogOption>("Shop", shopDialogNode0));
	cityDialogPoint1Node1->addDialogOption(std::make_shared<DialogOption>("Smith", smithDialogNode0));
	cityDialogPoint1Node1->addDialogOption(std::make_shared<DialogOption>("Church", cityDialogPoint1ChurchNode0));
	cityDialogPoint1Node1->addDialogOption(std::make_shared<DialogOption>("Houses", cityDialogPoint1RandomHouseNode));
	cityDialogPoint1Node1->addDialogOption(std::make_shared<DialogOption>("Leave VillageVille", std::shared_ptr<DialogNode>(nullptr)));

	cityDialogPoint1BankNode->addDialogOption(std::make_shared<DialogOption>("Back", cityDialogPoint1Node1));


	cityDialogPoint1RandomHouseNode->addDialogOption(std::make_shared<DialogOption>("Back", cityDialogPoint1Node1));

	cityDialogPoint1.addNode(cityDialogPoint1Node0);
	cityDialogPoint1.addNode(cityDialogPoint1Node1);
	cityDialogPoint1.addNode(cityDialogPoint1BankNode);
	cityDialogPoint1.addNode(cityDialogPoint1RandomHouseNode);


	shopDialogNode0->addDialogOption(std::make_shared<DialogOption>("Back", cityDialogPoint1Node1));
	smithDialogNode0->addDialogOption(std::make_shared<DialogOption>("Back", cityDialogPoint1Node1));
	//end town 1

	//start town 2
	std::shared_ptr<DialogNode> cityDialogPoint2Node0(new DialogNode("Do you wish to enter [insert bread-related town name]?"));
	std::shared_ptr<DialogNode> cityDialogPoint2Node1(new DialogNode("What do you want to visit in [insert bread-related town name]?", "town"));
	std::shared_ptr<DialogNode> cityDialogPoint2BankNode(new DialogNode("We are sorry the bank is under construction", "town"));
	std::shared_ptr<DialogNode> cityDialogPoint2SmithNode(new DialogNode("We are sorry the smith is under construction", "town"));
	std::shared_ptr<DialogNode> cityDialogPoint2ChurchNode0(new DialogNode("You enter the church, do you wish to respec your ability points", "church"));
	std::shared_ptr<DialogNode> cityDialogPoint2ChurchNode1(new DialogNode("Which character do you wish to respec?", "church"));
	std::shared_ptr<DialogNode> cityDialogPoint2RandomHouseNode(new DialogNode("The houses look generic and boring, like they have been copied and pasted.", "town"));

	cityDialogPoint2Node0->addDialogOption(std::make_shared<DialogOption>("Yes", cityDialogPoint2Node1));
	cityDialogPoint2Node0->addDialogOption(std::make_shared<DialogOption>("No", std::shared_ptr<DialogNode>(nullptr)));

	cityDialogPoint2ChurchNode0->addDialogOption(std::make_shared<DialogOption>("yes", cityDialogPoint2ChurchNode1));
	cityDialogPoint2ChurchNode0->addDialogOption(std::make_shared<DialogOption>("no", cityDialogPoint2Node1));

	for (size_t i = 0; i < heroParty.size(); i++) {
		cityDialogPoint2ChurchNode1->addDialogOption(std::make_shared<DialogOption>(heroParty[i]->getName(), cityDialogPoint2Node1, [&heroParty, i, &window, &background]() {AbilitySpeccing a(heroParty[i], window, background, "church"); a.resetAbilits(); a.use(window); window.clear(sf::Color::Transparent); }));
	}



	cityDialogPoint2Node1->addDialogOption(std::make_shared<DialogOption>("Bank", cityDialogPoint2BankNode));
	cityDialogPoint2Node1->addDialogOption(std::make_shared<DialogOption>("Grocery", shopDialogNode0));
	cityDialogPoint2Node1->addDialogOption(std::make_shared<DialogOption>("Metal shop", smithDialogNode0));
	cityDialogPoint2Node1->addDialogOption(std::make_shared<DialogOption>("Church", cityDialogPoint2ChurchNode0));
	cityDialogPoint2Node1->addDialogOption(std::make_shared<DialogOption>("Houses", cityDialogPoint2RandomHouseNode));
	cityDialogPoint2Node1->addDialogOption(std::make_shared<DialogOption>("Leave VillageVille", std::shared_ptr<DialogNode>(nullptr)));

	cityDialogPoint2BankNode->addDialogOption(std::make_shared<DialogOption>("Back", cityDialogPoint2Node1));


	cityDialogPoint2RandomHouseNode->addDialogOption(std::make_shared<DialogOption>("Back", cityDialogPoint2Node1));

	cityDialogPoint2.addNode(cityDialogPoint2Node0);
	cityDialogPoint2.addNode(cityDialogPoint2Node1);
	cityDialogPoint2.addNode(cityDialogPoint2BankNode);
	cityDialogPoint2.addNode(cityDialogPoint2RandomHouseNode);


	shopDialogNode1->addDialogOption(std::make_shared<DialogOption>("Back", cityDialogPoint2Node1));
	smithDialogNode1->addDialogOption(std::make_shared<DialogOption>("Back", cityDialogPoint2Node1));
	/// end town 2


	background.setBackGround("takatiki", window);

	std::shared_ptr<sf::RectangleShape> partyOverWorldIcon(new sf::RectangleShape);
	sf::Texture partyOverWorldIconTexture;
	sf::Vector2f partyIconSize(50, 50);
	partyOverWorldIconTexture.create(50, 50);
	partyOverWorldIconTexture.loadFromFile("PartyBanner.png");
	sf::Vector2f newLocation;
	newLocation = poiCont.getCurrentPointLocation();
	partyOverWorldIcon->setSize(partyIconSize);
	partyOverWorldIcon->setTexture(&partyOverWorldIconTexture);
	partyOverWorldIcon->setOrigin(25.0f, 50.0f);
	partyOverWorldIcon->setPosition(newLocation);

	TransformableMovement POIMove(partyOverWorldIcon, newLocation, 0.0f);
	POIMove.blend();
	std::vector<sf::Vector2f> moveList;

	//=======================================================
	// Creating KeyBoard Handler
	//=======================================================

	KeyboardHandler keyHandl;


	keyHandl.addListener(sf::Keyboard::Enter, [&]() { if (moveList.size() == 0 && POIMove.isFinished()) { poiCont.activate(); background.setBackGround("takatiki", window);};  });
	
	keyHandl.addListener(sf::Keyboard::Escape, [&]() {menu.update(window); background.setBackGround("takatiki", window); });



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
	// Home screen
	//=======================================================
	bool startGame = false;
	KeyboardHandler homeMenuKeyHandler;
	homeMenuKeyHandler.addListener(sf::Keyboard::Enter, [&]() { 
		startGame = true;
		sound.playSoundEffect(SoundEffect::gameStart);
		sf::sleep(sf::seconds(1));
		sound.stopMusic();
	});

	sf::Texture homeImage;
	homeImage.loadFromFile("Assets/BeginscreenWithUnicorn.png");
	sf::Sprite homeBackground;
	homeBackground.setTexture(homeImage);

	if ((rand() % 101 + 0) < 11) {
		sound.playMusicType(MusicType::unicorns);
	} else {
		sound.playMusicType(MusicType::menu);
	}

	while (!startGame) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				homeMenuKeyHandler.processKey(event.key.code);
			}
		}
		window.clear();
		window.draw(homeBackground);
		window.display();
	}

	
	heroParty.addCurrency(2000000);
	while (window.isOpen()) {
		if (playMenuTheme) {
			sound.playMusicType(MusicType::overworld);
			playMenuTheme = false;
		}

		if (moveList.size() > 0 && POIMove.isFinished()) {
			// calc random encounter
			int encounterChange = rand() % 100 + 1;

			if (encounterChange > 90 && encounterChange < 95){

				std::pair< std::string, std::string> anubisPair;
				anubisPair.first = "Assets/Anubis/Idle_all.png";
				anubisPair.second = "Assets/Anubis/Idle_000.png";
				std::shared_ptr<Monster> testMonster = std::make_shared<Monster>("Jim", anubisPair);
				testMonster->setDeathAnimation("Assets/Anubis/Dying_all.png");
				std::vector<std::shared_ptr<Monster>> monsterVector = { testMonster };
				Mob monsters = (monsterVector);
				Combat testCombat(window, heroParty, monsters, "combatBackGround", background);

				//Stop music
				playMenuTheme = true;
				sound.stopMusic();
				testCombat.update();

			}else if (encounterChange > 0 && encounterChange < 5) {
				randomEncounter.performDialogue(overWorldDialog);
			}
			else if (encounterChange > 5 && encounterChange < 10) {
				waterWellTree.performDialogue(overWorldDialog, true, 20);
			}
			else if (encounterChange > 10 && encounterChange < 15) {
				windmillTree.performDialogue(overWorldDialog, true , 20);
			}
			POIMove = TransformableMovement(partyOverWorldIcon, moveList.back(), 1.0f);
			moveList.pop_back();
			POIMove.blend();
		} else if (moveList.size() == 0 && POIMove.isFinished()) {
			//doe niks
		}
		if (!POIMove.isFinished()) {
			POIMove.update();
		}

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				keyHandl.processKey(event.key.code);
			}
		}

		window.clear();
		background.draw(window);
		poiCont.draw(window);
		window.draw(*partyOverWorldIcon);
		window.display();

	}
	return 0;
}