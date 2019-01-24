#include "InventoryDisplay.hpp"
#include <SFML/Graphics/Color.hpp>

InventoryDisplay::InventoryDisplay(Party & party, sf::RenderWindow & window) :
	party(party),
	window(window),
	leftScreen(leftScreenSize.x, leftScreenSize.y),
	rightScreen(rightScreenSize.x, rightScreenSize.y)
{
	////Make virtualscreens
	sf::Vector2f leftScreenTopLeft(20.0, 20.0);
	sf::Vector2f rightScreenTopLeft(970.0, 20.0);
	leftScreen.setLocation(leftScreenTopLeft);
	rightScreen.setLocation(rightScreenTopLeft);

	takatiki.loadFromFile("takatikimap.png");
	background.setTexture(takatiki);
	background.setTextureRect({ 0, 0, 1920, 1080 });

	for (unsigned int i = 0; i < party.size(); i++) {
		pTile.first.push_back(
			std::make_shared<PlayerInventoryTile>(
				party[i], 
				sf::Vector2f(0.0f, static_cast<float>(i * leftScreenSize.y / 4)),
				sf::Vector2f(static_cast<float>(leftScreenSize.x), static_cast<float>(leftScreenSize.y / 4))
			)
		);
	}

	auto partyInventory = party.getInventory();
	for (unsigned int i = 0; i < partyInventory.size(); i++) {
		pTile.second.push_back(
			std::make_shared<InventoryTile>(
				partyInventory[i],
				sf::Vector2f( 0.0f , static_cast<float>(i * 100) ),
				sf::Vector2f(static_cast<float>(rightScreenSize.x), 100.0f )
			)
		);
	}
	/*book.loadFromFile("Assets/OpenBook.png");
	bookSprite.setTexture(book);
	bookSprite.setScale(static_cast<float>(1920 / book.getSize().x * 1.1), static_cast<float>(1080 / book.getSize().y * 1.1));
	bookSprite.setPosition(30, 0);*/

	////Recieve all items
	//for (unsigned int i = 0; i < party.size(); i++) {
	//	//playerItems[i] = party[i]->getInventory;
	//}
	////partyItems = party.getItems();

	////Initiate tiles
	selectBox.setPosition(pTile.first[0]->getSelectboxPosition());
	selectBox.setSize(sf::Vector2f{ 80,80 });
	selectBox.setFillColor(sf::Color::Blue);

	keyHandler.addListener(sf::Keyboard::Up, [&]() {switchRowSelectbox(i- 1); });
	keyHandler.addListener(sf::Keyboard::Down, [&]() {switchRowSelectbox(i + 1); });
	keyHandler.addListener(sf::Keyboard::Left, [&]() {switchCollumSelectbox(); });
	keyHandler.addListener(sf::Keyboard::Right, [&]() {switchCollumSelectbox(); });
	keyHandler.addListener(sf::Keyboard::Delete, [&]() {deleteItem(); });
	keyHandler.addListener(sf::Keyboard::Escape, [&]() {isOpen = false; });
}


InventoryDisplay::~InventoryDisplay()
{
}


void InventoryDisplay::use() {
	isOpen = true;
	while (isOpen ) {
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
				keyHandler.processKey(event.key.code);
		}
		draw();

		//Ooit wordt op een manier een iten gekozen om te gebruiken
		//In dat geval wordt itemToUse = chosenItem
	}
}

void InventoryDisplay::draw() {
	window.clear();
	window.draw(background);
	//window.draw(bookSprite);
	drawLeftScreen();
	drawRightScreen();
	window.draw(selectBox);
	window.display();
}

void InventoryDisplay::drawLeftScreen() {
	leftScreen.drawSurfaceClear(halfTransparent);
	for (auto tile : pTile.first) {
		tile->draw(leftScreen);
	}
	leftScreen.drawSurfaceDisplay();
	window.draw(leftScreen);
}

void InventoryDisplay::drawRightScreen() {
	rightScreen.drawSurfaceClear(halfTransparent);

	for (auto item : pTile.second) {
		item->draw(rightScreen);
	}
	rightScreen.drawSurfaceDisplay();
	window.draw(rightScreen);

}

void InventoryDisplay::switchCollumSelectbox() {
	if (pTile.second.size() > 0) {
		firstCollum = !firstCollum;
		i = 0;
	}
	if (firstCollum) {
		selectBox.setPosition(pTile.first[i]->getSelectboxPosition());
	}
	else if (firstCollum == false && pTile.second.size() > 0) {
		selectBox.setPosition(pTile.second[i]->getSelectboxPosition());
	}
}

void InventoryDisplay::switchRowSelectbox(unsigned int index) {
	if (firstCollum) {
		if (index < pTile.first.size() && index >= 0) {
			i = index;
			selectBox.setPosition(pTile.first[i]->getSelectboxPosition());
		}
	}
	else {
		if (index < pTile.second.size() && index >= 0) {
			i = index;
			selectBox.setPosition(pTile.second[i]->getSelectboxPosition());
		}
	}
}

void InventoryDisplay::deleteItem() {
	if (firstCollum == false) {
		party.eraseItem(pTile.second[i]->getItem());
		pTile.second.erase(std::remove(pTile.second.begin(), pTile.second.end(), pTile.second[i]), pTile.second.end());
		firstCollum = true;
		switchRowSelectbox(0);

		pTile.second.clear();
		auto partyInventory = party.getInventory();
		for (unsigned int i = 0; i < partyInventory.size(); i++) {
			pTile.second.push_back(
				std::make_shared<InventoryTile>(
					partyInventory[i],
					sf::Vector2f(0.0f, static_cast<float>(i * 100)),
					sf::Vector2f(static_cast<float>(rightScreenSize.x), 100.0f)
					)
			);
		}
	}
}