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

	std::shared_ptr<PlayerCharacter> testCharacter1 = std::make_shared<PlayerCharacter>("Anubis, the distructor of hopes and dreams", "Assets/AnubisIdle.png");
	std::shared_ptr<PlayerCharacter> testCharacter2 = std::make_shared<PlayerCharacter>("Bnubis, the spoiler of fields", "Assets/AnubisIdle.png");
	std::shared_ptr<PlayerCharacter> testCharacter3 = std::make_shared<PlayerCharacter>("Cnubis, the poor sidekick", "Assets/AnubisIdle.png");
	std::shared_ptr<PlayerCharacter> testCharacter4 = std::make_shared<PlayerCharacter>("Dnubis, the second poor sidekick", "Assets/AnubisIdle.png");

	Armor wingedBoots;
	wingedBoots.setArmorSlot(ArmorSlots::boots);
	wingedBoots.setMagicalProtection(5);
	wingedBoots.setPhysicalProtection(3);
	wingedBoots.addPropertyModifier(std::pair<AbilityScores, int>(AbilityScores::dexterity, 5));
	testCharacter1->setArmor(ArmorSlots::boots, wingedBoots);

	Armor juggernaut;
	juggernaut.setArmorSlot(ArmorSlots::chestplate);
	juggernaut.setPhysicalProtection(12);
	juggernaut.addPropertyModifier(std::pair<AbilityScores, int>(AbilityScores::strength, 3));
	juggernaut.addPropertyModifier(std::pair<AbilityScores, int>(AbilityScores::dexterity, -3));
	testCharacter1->setArmor(ArmorSlots::chestplate, juggernaut);

	Armor poorlyFittedClothing;
	poorlyFittedClothing.setArmorSlot(ArmorSlots::helmet);
	poorlyFittedClothing.addPropertyModifier(std::pair<AbilityScores, int>(AbilityScores::charisma, -5));
	testCharacter2->setArmor(ArmorSlots::helmet, poorlyFittedClothing);


	testCharacter1->setWeakness(DamageTypes::frost, 2.0f);
	testCharacter1->setWeakness(DamageTypes::thunder, 1.5f);
	testCharacter1->setWeakness(DamageTypes::psychic, 1.1f);
	testCharacter1->setWeakness(DamageTypes::poison, 0.5f);
	testCharacter1->setWeakness(DamageTypes::acid, 0.75f);
	testCharacter1->setWeakness(DamageTypes::fire, 0.75f);


	testCharacter2->increaseExperience(15);
	testCharacter3->increaseExperience(55);
	testCharacter4->increaseExperience(95);

	testCharacter1->decreaseHealth(2);
	testCharacter2->decreaseHealth(5);
	testCharacter3->decreaseHealth(9);
	testCharacter4->decreaseHealth(1);

	testCharacter1->setPortraitFilename("Anubis_head.png");
	testCharacter2->setPortraitFilename("Barbarian_head.png");
	testCharacter3->setPortraitFilename("Black_Wizard_head.png");
	testCharacter4->setPortraitFilename("Blacksmith_head.png");

	std::vector<std::shared_ptr<PlayerCharacter>> heroVector = { testCharacter1, testCharacter2, testCharacter3, testCharacter4 };

	Party heroParty(heroVector);
	std::string takatikimap = "takatiki";
	std::string backgroundImage = "takatikimap.png";

	BackGround background;

	background.add(takatikimap, backgroundImage);


	background.setBackGround(takatikimap, window);

	KeyboardHandler keyHandl;

	keyHandl.addListener(sf::Keyboard::C, [&heroParty, &window]() {
		PartyOverview overview(heroParty);
		overview.open(window); 
	});
	
	heroParty[0]->decreaseHealth(1);

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
		window.clear();

		background.draw(window);
		window.display();

	}
	return 0;
}
