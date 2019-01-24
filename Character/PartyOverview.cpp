#include "partyOverview.hpp"
#include <stdexcept>
#include "../Core/KeyboardHandler.hpp"
#include "Character.hpp"

PartyOverview::PartyOverview(Party & party) :
	party(party),
	leftScreen(500, 1040) {
	if (party.size() < 0) {
		throw std::out_of_range("DE PARTY IS LEEG!");
	} else {
		selected = party[0];
		leftScreen.setLocation(sf::Vector2f(50, 10));
	}

}

void PartyOverview::drawAllPlayerCharacters(sf::RenderWindow & window) {
	if (party.size() == leftScreens.size()) {
		window.clear();
		leftScreen.drawSurfaceClear(sf::Color(100, 100, 100, 200));

		for (unsigned int i = 0; i < party.size(); i++) {
			// healthbar

			std::shared_ptr<ResourceBar> healthBar = party[i]->getHealthBar();
			healthBar->setPosition(sf::Vector2f(200,60));

			std::shared_ptr<ResourceBar> expBar = std::make_shared<ResourceBar>(
				sf::Vector2f(200, 80), 100, 50);
			expBar->setSize(sf::Vector2f(100, 5));
			/*expBar->setBarBackgroundColor(sf::Color(29, 214, 19));
			expBar->setBarColor(sf::Color(16, 112, 11));*/
			expBar->setBarBackgroundColor(sf::Color::White);
			expBar->setBarColor(sf::Color::Green);

			expBar->setMaxResource(100);
			expBar->setCurrentResource(50);

			//Pre-draw
			leftScreens[i]->drawSurfaceClear(sf::Color(100, 100, 100, 200));

			//Draw-stuff
			healthBar->draw(*leftScreens[i]);
			expBar->draw(*leftScreens[i]);

			//leftScreens[i]->drawSurfaceDraw(playerPortraitTiles[i]);
			playerPortraitTiles[i]->draw(*leftScreens[i]);

			//Post-draw
			leftScreens[i]->drawSurfaceDisplay();
			//draw to leftscreen
			leftScreen.drawSurfaceDraw(*leftScreens[i]);
		}

		leftScreen.drawSurfaceDisplay();


		window.draw(leftScreen);
		window.display();
	} else {
		isOpen = false;
	}
}

void PartyOverview::drawSelectedPlayerStats() {

}

void PartyOverview::open(sf::RenderWindow & window) {
	isOpen = true;

	KeyboardHandler keyHandle;
	keyHandle.addListener(sf::Keyboard::Escape, [&isOpen = isOpen]() {isOpen = false; });

	for (unsigned int i = 0; i < party.size(); i++) {

		std::shared_ptr<VirtualScreen> playerCharacterScreen = std::make_shared<VirtualScreen>(leftScreenSize.x, (leftScreenSize.y - 140) / 4);
		playerCharacterScreen->setLocation(sf::Vector2f(
			static_cast<float>(0),
			static_cast<float>((i * characterWindowSize.y))
		));
		leftScreens.push_back(playerCharacterScreen);


		std::string filename = "Character/Anubis_portrait.png";
		sf::Vector2f position(10, 10);
		sf::Vector2f size(100, 100);
		std::shared_ptr<Tile> playerPortraitTile = std::make_shared<Tile>(
			filename,
			position,
			size
			);
		playerPortraitTiles.push_back(playerPortraitTile);
	}

	while (isOpen) {
		//dostuff
		drawAllPlayerCharacters(window);
		//drawSelectedPlayerStats(window);



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

void PartyOverview::close() {
}
