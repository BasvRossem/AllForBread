#include "partyOverview.hpp"
#include <stdexcept>
#include "../Core/KeyboardHandler.hpp"
#include "Character.hpp"

PartyOverview::PartyOverview(Party & party) :
	party(party),
	leftScreen(500, 1040),
	rightScreen(1300, 1040)
{
	if (party.size() < 1) {
		throw std::out_of_range("DE PARTY IS LEEG!");
	} else {
		selected = party[0];
		leftScreen.setLocation(sf::Vector2f(50, 10));
		rightScreen.setLocation(sf::Vector2f(static_cast<float>(100 + leftScreenSize.x), static_cast<float>(10)));
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
			sf::RectangleShape background;
			sf::RectangleShape backgroundBorder;
			if (party[i] == selected) {
				backgroundBorder.setFillColor(sf::Color(72, 114, 59));
				background.setFillColor(sf::Color(123, 249, 84));

			} else {
				backgroundBorder.setFillColor(sf::Color(102, 51, 0));
				background.setFillColor(sf::Color(124, 79, 33));

			}

			backgroundBorder.setPosition(sf::Vector2f(0.0f, 0.0f));
			backgroundBorder.setSize(characterScreenSize + sf::Vector2f(2.0f, 2.0f));
			background.setPosition(sf::Vector2f(0.0f, 0.0f) + sf::Vector2f(5.0f, 5.0f));
			background.setSize(characterScreenSize - sf::Vector2f(10.0f, 10.0f));


			// healthbar
			std::shared_ptr<ResourceBar> healthBar = party[i]->getHealthBar();
			healthBar->setPosition(sf::Vector2f(200, 60));

			sf::RectangleShape healthBackground;
			healthBackground.setPosition(healthBar->getPosition() - sf::Vector2f(1,1));
			healthBackground.setSize(healthBar->getSize() + sf::Vector2f(2, 2));
			healthBackground.setFillColor(sf::Color(124, 0, 0));


			// expbar
			std::shared_ptr<ResourceBar> expBar = std::make_shared<ResourceBar>(sf::Vector2f(200, 80), 100, 50);
			expBar->setSize(sf::Vector2f(100, 5));
			expBar->setBarColor(sf::Color::Green);
			expBar->setMaxResource(party[i]->getMaxExperience());
			expBar->setCurrentResource(party[i]->getCurrentExperience());

			sf::RectangleShape expBackground;
			expBackground.setPosition(expBar->getPosition() - sf::Vector2f(1, 1));
			expBackground.setSize(expBar->getSize() + sf::Vector2f(2, 2));
			expBackground.setFillColor(sf::Color(5, 68, 0));


			//Char name
			sf::Text charName;
			charName.setFont(font);
			charName.setString(party[i]->getName());
			charName.setCharacterSize(24);
			charName.setFillColor(sf::Color::Black);
			charName.setOutlineColor(sf::Color::White);
			charName.setPosition(sf::Vector2f(
				10.0f,
				10.0f
			));
			charName.setOutlineThickness(0.50f);


			//Pre-draw
			//leftScreens[i]->drawSurfaceClear(sf::Color(186, 234, 255));
			leftScreens[i]->drawSurfaceClear(sf::Color::Transparent);


			//Draw-stuff
			leftScreens[i]->drawSurfaceDraw(backgroundBorder);
			leftScreens[i]->drawSurfaceDraw(background);
			leftScreens[i]->drawSurfaceDraw(healthBackground);
			leftScreens[i]->drawSurfaceDraw(expBackground);
			healthBar->draw(*leftScreens[i]);
			expBar->draw(*leftScreens[i]);

			playerPortraitTiles[i]->draw(*leftScreens[i]);
			leftScreens[i]->drawSurfaceDraw(charName);

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
		background.setSize(backgroundBorder.getSize() - sf::Vector2f(5.0f, 5.0f));
		background.setPosition(sf::Vector2f(5.0f, 5.0f));
		background.setFillColor(sf::Color(124, 79, 33));


		// ModifierBox
		sf::RectangleShape modifierBox;
		modifierBox.setPosition(sf::Vector2f(20.0f, 50.0f));
		modifierBox.setSize(sf::Vector2f(800.0f, 500.0f));
		modifierBox.setFillColor(sf::Color::White);
		modifierBox.setOutlineColor(sf::Color(102, 51, 0));
		modifierBox.setOutlineThickness(5.0f);

		//get playercharacter stoef


		// Draw
		rightScreen.drawSurfaceDraw(backgroundBorder);
		rightScreen.drawSurfaceDraw(background);
		rightScreen.drawSurfaceDraw(modifierBox);


		// Post-draw
		rightScreen.drawSurfaceDisplay();
		window.draw(rightScreen);
	} else {

	}
}

void PartyOverview::open(sf::RenderWindow & window) {
	isOpen = true;

	KeyboardHandler keyHandle;
	keyHandle.addListener(sf::Keyboard::Escape, [&isOpen = isOpen]() {isOpen = false; });
	keyHandle.addListener(sf::Keyboard::C, [&isOpen = isOpen]() {isOpen = false; });
	keyHandle.addListener(sf::Keyboard::Up, [&selected = selected, &party = party]() {
		for (unsigned int i = 0; i < party.size(); i++) {
			if (selected == party[i]) {
				if (i == 0) {
					selected = party[party.size() - 1];
				} else {
					selected = party[i - 1];
				}
				break;
			}
		}
	});
	keyHandle.addListener(sf::Keyboard::Down, [&selected = selected, &party = party]() {
		for (unsigned int i = 0; i < party.size(); i++) {
			if (selected == party[i]) {
				if (i == party.size()-1) {
					selected = party[0];
				} else {
					selected = party[i + 1];
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
		sf::Vector2f position(10, 40);
		sf::Vector2f size(100, 100);
		std::shared_ptr<Tile> playerPortraitTile = std::make_shared<Tile>(
			filename,
			position,
			size
			);
		playerPortraitTiles.push_back(playerPortraitTile);
	}

	while (isOpen) {

		window.clear();
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

