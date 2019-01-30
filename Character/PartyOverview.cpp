#include "partyOverview.hpp"
#include <stdexcept>
#include <string>
#include "../Core/KeyboardHandler.hpp"
#include "Character.hpp"

PartyOverview::PartyOverview(Party & newParty, BackGround & backGround, const std::string & surrounding) :
	backGround(backGround),
	surrounding(surrounding),
	party(newParty),
	leftScreen(500, 1040),
	rightScreen(900, 1040),
	partyLeaderTexture(std::make_shared<sf::Texture>()),
	nonPartyLeaderTexture(std::make_shared<sf::Texture>()),
	partyIconSprite(std::make_shared<sf::Sprite>())
{
	if (party.size() < 1) {
		throw std::out_of_range("DE PARTY IS LEEG!");
	} else {
		selected = party.getPartyLeader();
		leftScreen.setLocation(sf::Vector2f(50, 10));
		rightScreen.setLocation(sf::Vector2f(static_cast<float>(100 + leftScreenSize.x), static_cast<float>(15)));
		if (!font.loadFromFile("Assets/arial.ttf")) {
			throw std::out_of_range("FONT FILE NOT FOUND!");
		}
	}

}

void PartyOverview::drawAllPlayerCharacters(sf::RenderWindow & window) {
	if (party.size() == leftScreens.size()) {
		//leftScreen.drawSurfaceClear(sf::Color(100, 100, 100, 200));
		leftScreen.drawSurfaceClear(sf::Color::Transparent);

		for (unsigned int i = 0; i < party.size(); i++) {
			//Pre-draw
			leftScreens[i]->drawSurfaceClear(sf::Color::Transparent);


			sf::RectangleShape background;
			sf::RectangleShape backgroundBorder;
			if (selected == &party[i]) {
				backgroundBorder.setFillColor(sf::Color(72, 114, 59));
				background.setFillColor(sf::Color(123, 249, 84));
			} else {
				backgroundBorder.setFillColor(sf::Color(102, 51, 0));
				background.setFillColor(sf::Color(124, 79, 33));
			}


			partyIconSprite->setPosition(sf::Vector2f(25.0f, 40.0f));
			if (party.getPartyLeader() == &party[i]) {
				partyIconSprite->setTexture(*partyLeaderTexture);
				partyIconSprite->setScale(
					(50.0f / partyLeaderTexture->getSize().x), 
					(50.0f / partyLeaderTexture->getSize().y)
				);
			} else {
				partyIconSprite->setTexture(*nonPartyLeaderTexture);
				partyIconSprite->setScale(
					(50.0f / nonPartyLeaderTexture->getSize().x),
					(50.0f / nonPartyLeaderTexture->getSize().y)
				);
			}
			

			backgroundBorder.setPosition(sf::Vector2f(0.0f, 0.0f));
			backgroundBorder.setSize(characterScreenSize + sf::Vector2f(2.0f, 2.0f));
			background.setPosition(sf::Vector2f(0.0f, 0.0f) + sf::Vector2f(5.0f, 5.0f));
			background.setSize(characterScreenSize - sf::Vector2f(10.0f, 10.0f));


			// healthbar
			std::shared_ptr<ResourceBar> healthBar = party[i]->getHealthBar();
			healthBar->setPosition(sf::Vector2f(120, 120), false);

			sf::RectangleShape healthBackground;
			healthBackground.setPosition(healthBar->getPosition() - sf::Vector2f(1,1));
			healthBackground.setSize(healthBar->getSize() + sf::Vector2f(2, 2));
			healthBackground.setFillColor(sf::Color(124, 0, 0));
			

			sf::Text healthText;
			healthText.setFont(font);
			healthText.setPosition(healthBar->getPosition().x, healthBar->getPosition().y - 20);
			healthText.setCharacterSize(14);
			healthText.setFillColor(sf::Color::White);
			healthText.setOutlineColor(sf::Color::Black);
			healthText.setOutlineThickness(1.0f);
			healthText.setString("Hp: " + std::to_string(healthBar->getCurrentResource()) + "/" + std::to_string(healthBar->getMaxResource()));

			// expbar
			std::shared_ptr<ResourceBar> expBar = std::make_shared<ResourceBar>(sf::Vector2f(0.0f, 0.0f), 100, 50);
			expBar->setPosition(sf::Vector2f(
				healthBar->getPosition().x + healthBar->getSize().x + 15,
				healthBar->getPosition().y), false);
			expBar->setSize(healthBar->getSize());
			expBar->setBarColor(sf::Color::Green);
			expBar->setMaxResource(party[i]->getMaxExperience());
			expBar->setCurrentResource(party[i]->getCurrentExperience());

			sf::Text expText;
			expText.setFont(font);
			expText.setPosition(expBar->getPosition().x, expBar->getPosition().y - 20);
			expText.setCharacterSize(14);
			expText.setFillColor(sf::Color::White);
			expText.setOutlineColor(sf::Color::Black);
			expText.setOutlineThickness(1.0f);
			expText.setString("Exp: " + std::to_string(expBar->getCurrentResource()) + "/" + std::to_string(expBar->getMaxResource()));

			sf::RectangleShape expBackground;
			expBackground.setPosition(expBar->getPosition() - sf::Vector2f(1, 1));
			expBackground.setSize(expBar->getSize() + sf::Vector2f(2, 2));
			expBackground.setFillColor(sf::Color(5, 68, 0));


			//Char name
			sf::Text charName;
			charName.setFont(font);
			charName.setString(party[i]->getName());
			charName.setCharacterSize(24);
			charName.setFillColor(sf::Color::White);
			charName.setOutlineColor(sf::Color::Black);
			charName.setOutlineThickness(1.0f);
			charName.setPosition(sf::Vector2f(10.0f, 10.0f));

			//Char level
			sf::Text charLevel;
			charLevel.setFont(font);
			charLevel.setString("Level: " + std::to_string(party[i]->getCharlevel()));
			charName.setCharacterSize(24);
			charLevel.setFillColor(sf::Color::White);
			charLevel.setOutlineColor(sf::Color::Black);
			charLevel.setOutlineThickness(1.0f);
			charLevel.setPosition(sf::Vector2f(healthText.getPosition().x, healthText.getPosition().y - 35));



			//Draw-stuff
			leftScreens[i]->drawSurfaceDraw(backgroundBorder);
			leftScreens[i]->drawSurfaceDraw(background);
			leftScreens[i]->drawSurfaceDraw(healthBackground);
			leftScreens[i]->drawSurfaceDraw(expBackground);
			leftScreens[i]->drawSurfaceDraw(healthText);
			leftScreens[i]->drawSurfaceDraw(expText);
			leftScreens[i]->drawSurfaceDraw(charLevel);
			healthBar->draw(*leftScreens[i]);
			expBar->draw(*leftScreens[i]);

			playerPortraitTiles[i]->draw(*leftScreens[i]);
			leftScreens[i]->drawSurfaceDraw(charName);

			leftScreens[i]->drawSurfaceDraw(*partyIconSprite);
			//Post-draw
			leftScreens[i]->drawSurfaceDisplay();


			//draw to leftscreen
			leftScreen.drawSurfaceDraw(*leftScreens[i]);
		}

		leftScreen.drawSurfaceDisplay();


		window.draw(leftScreen);
	} else {
		isOpen = false;
	}
}

void PartyOverview::drawSelectedPlayerStats(sf::RenderWindow & window) {
	if(selected != nullptr){
		// Pre-draw
		rightScreen.drawSurfaceClear(sf::Color::White);

		//Background
		sf::RectangleShape background;
		sf::RectangleShape backgroundBorder;
		backgroundBorder.setSize(sf::Vector2f(
			static_cast<float>(rightScreenSize.x), 
			static_cast<float>(rightScreenSize.y)
		));
		backgroundBorder.setPosition(sf::Vector2f(0.0f, 0.0f));
		backgroundBorder.setFillColor(sf::Color(102, 51, 0));
		background.setSize(backgroundBorder.getSize() - sf::Vector2f(10.0f, 10.0f));
		background.setPosition(sf::Vector2f(5.0f, 5.0f));
		background.setFillColor(sf::Color(124, 79, 33));


		// Draw
		rightScreen.drawSurfaceDraw(backgroundBorder);
		rightScreen.drawSurfaceDraw(background);

		drawModifierBox();
		drawProtectionStats();

		// Post-draw
		rightScreen.drawSurfaceDisplay();
		window.draw(rightScreen);
	} else {

	}
}

void PartyOverview::drawModifierBox() {
	//Modifier title
	sf::Text modifierTitle;
	modifierTitle.setFont(font);
	modifierTitle.setCharacterSize(30);
	modifierTitle.setPosition(125.0f, 75.0f);
	modifierTitle.setFillColor(sf::Color::White);
	modifierTitle.setOutlineColor(sf::Color::Black);
	modifierTitle.setString("Abilityscore modifiers");

	// ModifierBox
	sf::RectangleShape modifierBox;
	sf::Vector2f modifierBoxPosition = sf::Vector2f(50.0f, 125.0f);
	sf::Vector2f modifierBoxSize = sf::Vector2f(475.0f, 375.0f);
	modifierBox.setPosition(modifierBoxPosition);
	modifierBox.setSize(modifierBoxSize);
	modifierBox.setFillColor(sf::Color::White);
	modifierBox.setOutlineColor(sf::Color(102, 51, 0));
	modifierBox.setOutlineThickness(5.0f);


	int rowOffset = 50;
	int colOffset = 120;
	sf::Text ownScores;
	ownScores.setFont(font);
	ownScores.setCharacterSize(24);
	ownScores.setFillColor(sf::Color::Black);
	ownScores.setOutlineColor(sf::Color::White);
	ownScores.setPosition(modifierBoxPosition.x + colOffset, modifierBoxPosition.y + 5);
	ownScores.setString("Base");

	sf::Text modifierScores;
	modifierScores.setFont(font);
	modifierScores.setCharacterSize(24);
	modifierScores.setFillColor(sf::Color::Black);
	modifierScores.setOutlineColor(sf::Color::White);
	modifierScores.setPosition(modifierBoxPosition.x + (colOffset * 2), modifierBoxPosition.y + 5);
	modifierScores.setString("Modifiers");

	sf::Text totalScores;
	totalScores.setFont(font);
	totalScores.setCharacterSize(24);
	totalScores.setFillColor(sf::Color::Black);
	totalScores.setOutlineColor(sf::Color::White);
	totalScores.setPosition(modifierBoxPosition.x + (colOffset * 3), modifierBoxPosition.y + 5);
	totalScores.setString("Total");

	rightScreen.drawSurfaceDraw(modifierBox);
	rightScreen.drawSurfaceDraw(modifierTitle);
	rightScreen.drawSurfaceDraw(ownScores);
	rightScreen.drawSurfaceDraw(modifierScores);
	rightScreen.drawSurfaceDraw(totalScores);

	std::unordered_map<AbilityScores, int> armorMods = (*selected)->getArmorModifierTotal();
	//get playercharacter stuff and draw them
	unsigned int i = 0;
	for (auto abilityScore : (*selected)->getStats()) {
		sf::Text scoreName;
		scoreName.setFont(font);
		scoreName.setString(EnumMethods::getAbilityScoreName(abilityScore.first));
		scoreName.setCharacterSize(24);
		scoreName.setFillColor(sf::Color::Black);
		scoreName.setOutlineColor(sf::Color::White);
		scoreName.setPosition(modifierBoxPosition.x + 5, modifierBoxPosition.y + ((i + 1) * rowOffset) + 5);


		sf::Text scoreStat;
		scoreStat.setFont(font);
		scoreStat.setString(std::to_string(abilityScore.second));
		scoreStat.setCharacterSize(24);
		scoreStat.setFillColor(sf::Color::Black);
		scoreStat.setOutlineColor(sf::Color::White);
		scoreStat.setPosition(modifierBoxPosition.x + colOffset + (colOffset / 4) + 5, modifierBoxPosition.y + ((i + 1) * rowOffset) + 5);


		sf::Text modStat;
		modStat.setFont(font);
		modStat.setCharacterSize(24);
		if (armorMods[abilityScore.first] > 0) {
			modStat.setFillColor(sf::Color::Green);
			modStat.setString("+" + std::to_string(armorMods[abilityScore.first]));
		} else if (armorMods[abilityScore.first] < 0) {
			modStat.setFillColor(sf::Color::Red);
			modStat.setString(std::to_string(armorMods[abilityScore.first]));
		} else {
			modStat.setFillColor(sf::Color::Black);
			modStat.setString(std::to_string(armorMods[abilityScore.first]));
		}
		modStat.setOutlineColor(sf::Color::White);
		modStat.setPosition(modifierBoxPosition.x + (colOffset * 2) + (colOffset / 4) + 5, modifierBoxPosition.y + ((i + 1) * rowOffset) + 5);


		sf::Text totalStat;
		totalStat.setFont(font);
		totalStat.setCharacterSize(24);
		if (armorMods[abilityScore.first] + abilityScore.second > abilityScore.second) {
			totalStat.setFillColor(sf::Color::Green);
			totalStat.setString(std::to_string(armorMods[abilityScore.first] + abilityScore.second));
		} else if (armorMods[abilityScore.first] + abilityScore.second < abilityScore.second) {
			totalStat.setFillColor(sf::Color::Red);
			totalStat.setString(std::to_string(armorMods[abilityScore.first] + abilityScore.second));
		} else {
			totalStat.setFillColor(sf::Color::Black);
			totalStat.setString(std::to_string(armorMods[abilityScore.first] + abilityScore.second));
		}
		totalStat.setOutlineColor(sf::Color::White);
		totalStat.setPosition(modifierBoxPosition.x + (colOffset * 3) + (colOffset / 4) + 5, modifierBoxPosition.y + ((i + 1) * rowOffset) + 5);


		rightScreen.drawSurfaceDraw(scoreName);
		rightScreen.drawSurfaceDraw(scoreStat);
		rightScreen.drawSurfaceDraw(modStat);
		rightScreen.drawSurfaceDraw(totalStat);
		i++;
	}


}

void PartyOverview::drawProtectionStats() {
	//Modifier title
	sf::Text modifierTitle;
	modifierTitle.setFont(font);
	modifierTitle.setCharacterSize(30);
	modifierTitle.setPosition(625.0f, 75.0f);
	modifierTitle.setFillColor(sf::Color::White);
	modifierTitle.setOutlineColor(sf::Color::Black);
	modifierTitle.setString("Resistances");

	// ModifierBox
	sf::RectangleShape modifierBox;
	sf::Vector2f modifierBoxPosition = sf::Vector2f(550.0f, 125.0f);
	sf::Vector2f modifierBoxSize = sf::Vector2f(300.0f, 725.0f);
	modifierBox.setPosition(modifierBoxPosition);
	modifierBox.setSize(modifierBoxSize);
	modifierBox.setFillColor(sf::Color::White);
	modifierBox.setOutlineColor(sf::Color(102, 51, 0));
	modifierBox.setOutlineThickness(5.0f);


	int colOffset = 150;
	int rowOffset = 50;
	sf::Text resistanceTypeTitle;
	resistanceTypeTitle.setFont(font);
	resistanceTypeTitle.setPosition(modifierBoxPosition.x + 25.0f, modifierBoxPosition.y + 15.0f);
	resistanceTypeTitle.setCharacterSize(24);
	resistanceTypeTitle.setFillColor(sf::Color::Black);
	resistanceTypeTitle.setString("Type");

	sf::Text resistanceValueTitle;
	resistanceValueTitle.setFont(font);
	resistanceValueTitle.setPosition(modifierBoxPosition.x + colOffset + 25.0f, modifierBoxPosition.y + 15.0f);
	resistanceValueTitle.setCharacterSize(24);
	resistanceValueTitle.setFillColor(sf::Color::Black);
	resistanceValueTitle.setString("Value %");

	rightScreen.drawSurfaceDraw(modifierBox);
	rightScreen.drawSurfaceDraw(modifierTitle);
	rightScreen.drawSurfaceDraw(resistanceTypeTitle);
	rightScreen.drawSurfaceDraw(resistanceValueTitle);

	unsigned int i = 0;
	auto weaknesses = (*selected)->getWeaknesses();
	for (auto & weakness : weaknesses ) {
		sf::Text weaknessText;
		weaknessText.setFont(font);
		weaknessText.setPosition(modifierBoxPosition.x + 5.0f, modifierBoxPosition.y + ((i+1) * rowOffset));
		weaknessText.setFillColor(sf::Color::Black);
		weaknessText.setCharacterSize(24);
		weaknessText.setString(EnumMethods::getDamageTypeName(weakness.first));

		sf::Text weaknessValue;
		weaknessValue.setFont(font);
		weaknessValue.setPosition(modifierBoxPosition.x + colOffset + 50.0f, modifierBoxPosition.y + ((i + 1) * rowOffset));
		weaknessValue.setCharacterSize(24);
		
		int percentage = static_cast<int>((1 - weakness.second) * 100);
		if (percentage > 0) {
			weaknessValue.setFillColor(sf::Color::Green);
		} else if (percentage < 0) {
			weaknessValue.setFillColor(sf::Color::Red);
		} else {
			weaknessValue.setFillColor(sf::Color::Black);
		}
		weaknessValue.setString(std::to_string(percentage));

		rightScreen.drawSurfaceDraw(weaknessText);
		rightScreen.drawSurfaceDraw(weaknessValue);
		i++;
	}
}

void PartyOverview::open(sf::RenderWindow & window) {
	isOpen = true;

	KeyboardHandler keyHandle;
	keyHandle.addListener(sf::Keyboard::Escape, [&isOpen = isOpen]() {isOpen = false; });
	keyHandle.addListener(sf::Keyboard::C, [&isOpen = isOpen]() {isOpen = false; });
	keyHandle.addListener(sf::Keyboard::Enter, [&party = party, &selected = selected]() {party.setPartyLeader(selected); });
	
	keyHandle.addListener(sf::Keyboard::Up, [&selected = selected, &party = party]() {
		for (unsigned int i = 0; i < party.size(); i++) {
			if (selected == &party[i]) {
				if (i == 0) {
					selected = &party[party.size() - 1];
				} else {
					selected = &party[i - 1];
				}
				break;
			}
		}
	});
	keyHandle.addListener(sf::Keyboard::Down, [&selected = selected, &party = party]() {
		for (unsigned int i = 0; i < party.size(); i++) {
			if (selected == &party[i]) {
				if (i == party.size()-1) {
					selected = &party[0];
				} else {
					selected = &party[i + 1];
				}
				break;
			}
		}
	});

	for (unsigned int i = 0; i < party.size(); i++) {

		std::shared_ptr<VirtualScreen> playerCharacterScreen = std::make_shared<VirtualScreen>(static_cast<int>(characterScreenSize.x), static_cast<int>(characterScreenSize.y));
		playerCharacterScreen->setLocation(sf::Vector2f(
			static_cast<float>(0),
			static_cast<float>((((leftScreenSize.y) / 4) * i)+5)
		));
		leftScreens.push_back(playerCharacterScreen);


		std::string filename = "Assets/" + party[i]->getFilename();
		sf::Vector2f position(10, 80);
		sf::Vector2f size(100, 100);
		std::shared_ptr<Tile> playerPortraitTile = std::make_shared<Tile>(
			filename,
			position,
			size
			);
		playerPortraitTiles.push_back(playerPortraitTile);
	}

	if (!nonPartyLeaderTexture->loadFromFile("Assets/crown_grey.png")) {
		throw std::out_of_range("File shield_grey.png niet gevonden");
	}

	if (!partyLeaderTexture->loadFromFile("Assets/crown_gold.png")) {
		throw std::out_of_range("File shield_grey.png niet gevonden");
	}

	backGround.setBackGround(surrounding, sf::Vector2f{ 0,0 }, window);

	while (isOpen) {
		
		window.clear(sf::Color::Transparent);
		backGround.draw(window);
		//dostuff
		drawAllPlayerCharacters(window);
		drawSelectedPlayerStats(window);


		window.display();

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				keyHandle.processKey(event.key.code);
			}
		}
	}
}

