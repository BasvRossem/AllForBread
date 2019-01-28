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
	selected.first = 0;
	selected.second = 0;
	lastSelected.first = 0;
	lastSelected.second = 0;
}


InventoryDisplay::~InventoryDisplay()
{
}





void InventoryDisplay::use() {
	enum class InventoryMenu { left, right , equipItem , unequipItem};
	enum class equip { left, right };
	InventoryMenu state = InventoryMenu::left;
	equip eState = equip::left;
	keyHandler.setOverride(true);


	isOpen = true;
	while (isOpen && window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
				keyHandler.processKey(event.key.code);
		}
		draw();

		switch (state) {
			case InventoryMenu::left:
				keyHandler.addListener(sf::Keyboard::A, []() {});
				keyHandler.addListener(sf::Keyboard::D, [&]() {if (pTile.second.size() != 0) { state = InventoryMenu::right;  setZeroSelected(1); }});
				keyHandler.addListener(sf::Keyboard::W, [&]() { changeSelected(0, -1); });
				keyHandler.addListener(sf::Keyboard::S, [&]() { changeSelected(0, 1);  });

				keyHandler.addListener(sf::Keyboard::Enter, [&]() {state = InventoryMenu::unequipItem; select(selected.first, selected.second); lastSelected.first = selected.first;  lastSelected.second = selected.second; setZeroSelected(0, lastSelected.second); });
				keyHandler.addListener(sf::Keyboard::Delete, [&]() {});
				keyHandler.addListener(sf::Keyboard::Escape, [&]() {isOpen = false; });
				break;
			case InventoryMenu::right:
				keyHandler.addListener(sf::Keyboard::A, [&]() {state = InventoryMenu::left;  setZeroSelected(0); });
				keyHandler.addListener(sf::Keyboard::D, []() {});
				keyHandler.addListener(sf::Keyboard::W, [&]() {changeSelected(1, -1); });
				keyHandler.addListener(sf::Keyboard::S, [&]() {changeSelected(1, 1);  });

				keyHandler.addListener(sf::Keyboard::Delete, [&]() {if (pTile.second.size() != 0) { state = InventoryMenu::left; deleteItem(selected.second); changeSelected(0, 0);state = InventoryMenu::left; }});
				keyHandler.addListener(sf::Keyboard::Enter, [&]() {state = InventoryMenu::equipItem; select(selected.first, selected.second); lastSelected.first = selected.first;  lastSelected.second = selected.second; setZeroSelected(0); });
				keyHandler.addListener(sf::Keyboard::Escape, [&]() {isOpen = false; });
				break;
			case InventoryMenu::equipItem:
				keyHandler.addListener(sf::Keyboard::A, []() {});
				keyHandler.addListener(sf::Keyboard::D, []() {});
				keyHandler.addListener(sf::Keyboard::W, [&]() { changeSelected(0, -1); });
				keyHandler.addListener(sf::Keyboard::S, [&]() { changeSelected(0, 1);  });

				keyHandler.addListener(sf::Keyboard::Delete, [&]() {});
				keyHandler.addListener(sf::Keyboard::Escape, [&]() {state = InventoryMenu::right; reloadTiles();  setZeroSelected(0); });
				keyHandler.addListener(sf::Keyboard::Enter, [&]() {state = InventoryMenu::left;  addItemToCharacter(selected.second, lastSelected.second);  setZeroSelected(0); });

				break;
			case InventoryMenu::unequipItem:
				switch (eState) {
					case equip::left:
						keyHandler.addListener(sf::Keyboard::A, []() {});
						keyHandler.addListener(sf::Keyboard::D, [&]() { eState = equip::right;  changeSelected(1, 0, lastSelected.second); });
						keyHandler.addListener(sf::Keyboard::W, [&]() { changeSelected(0, -1, lastSelected.second); });
						keyHandler.addListener(sf::Keyboard::S, [&]() { changeSelected(0, 1, lastSelected.second);  });

						keyHandler.addListener(sf::Keyboard::Delete, []() {});
						keyHandler.addListener(sf::Keyboard::Enter, [&]() {state = InventoryMenu::left; removeItemFromCharacer(lastSelected.second, selected.first, selected.second); setZeroSelected(0); reloadTiles(); });
						keyHandler.addListener(sf::Keyboard::Escape, [&]() {state = InventoryMenu::left; eState = equip::left; reloadTiles();   setZeroSelected(0); });
						break;
					case equip::right:
						keyHandler.addListener(sf::Keyboard::A, [&]() { eState = equip::left; changeSelected(0, 0, lastSelected.second); });
						keyHandler.addListener(sf::Keyboard::D, []() {});
						keyHandler.addListener(sf::Keyboard::W, [&]() { changeSelected(1, -1, lastSelected.second); });
						keyHandler.addListener(sf::Keyboard::S, [&]() { changeSelected(1, 1, lastSelected.second);  });

						keyHandler.addListener(sf::Keyboard::Delete, []() {});
						keyHandler.addListener(sf::Keyboard::Enter, [&]() {state = InventoryMenu::left; removeItemFromCharacer(lastSelected.second, selected.first, selected.second); setZeroSelected(0); });
						keyHandler.addListener(sf::Keyboard::Escape, [&]() {state = InventoryMenu::left; reloadTiles();  setZeroSelected(0); });
						break;
				}
				break;
		}
	}
}

void InventoryDisplay::changeSelected(const int x, const int y, const int &character) {
	if (character == 4) {
		if (x == 0) {
			if (y + selected.second < signed int(pTile.first.size()) && y + selected.second >= 0) { selected.first = x; selected.second = y + selected.second; selectBox.setPosition(pTile.first[selected.second]->getSelectboxPosition()); }
		}
		else if (x == 1) {
			if (y + selected.second < signed int(pTile.second.size()) && y + selected.second >= 0) { selected.first = x; selected.second = y + selected.second; selectBox.setPosition(pTile.second[selected.second]->getSelectboxPosition()); }
		}
	}
	else {
		if (x == 0) {
			if (y + selected.second < signed int(pTile.first[character]->getWeaponTiles().size()) && y + selected.second >= 0){ selected.first = x; selected.second = y + selected.second; selectBox.setPosition(pTile.first[character]->getWeaponTiles()[y]->getSelectboxPositionMini()); selectBox.setSize(sf::Vector2f{ 40,40 });}
		}
		else if (x == 1) 
		{
			if (y + selected.second < signed int (pTile.first[character]->getArmorTiles().size()) && y + selected.second >= 0) { selected.first = x; selected.second = y + selected.second; selectBox.setPosition(pTile.first[character]->getArmorTiles()[y]->getSelectboxPositionMini()); selectBox.setSize(sf::Vector2f{ 20,20 });}
		}
	}
}

void InventoryDisplay::setZeroSelected(const int & collum, const int &character) {
	if (collum == 0 && character == 4) {
		selected.first = collum;
		selected.second = 0;
		selectBox.setPosition(pTile.first[selected.second]->getSelectboxPosition());
		selectBox.setSize(sf::Vector2f{ 80,80 });
	}
	else if (collum == 1 && character == 4) {
		selected.first = collum;
		selected.second = 0;
		selectBox.setPosition(pTile.second[selected.second]->getSelectboxPosition());
		selectBox.setSize(sf::Vector2f{ 80,80 });
	}
	else if (character < 4) {
		if (pTile.first[character]->getWeaponTiles().size() != 0) { 
			selected.first = collum;
			selected.second = 0;
			selectBox.setPosition(pTile.first[character]->getWeaponTiles()[0]->getSelectboxPositionMini()); 
			selectBox.setSize(sf::Vector2f{ 40,40 }); 
		}
		else if (pTile.first[character]->getArmorTiles().size() != 0) {
			selected.first = 1;
			selected.second = 0;
			selectBox.setPosition(pTile.first[character]->getArmorTiles()[0]->getSelectboxPositionMini());
			selectBox.setSize(sf::Vector2f{ 20,20 });
		}
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


void InventoryDisplay::deleteItem(const int & i) {
	party.eraseItem(pTile.second[i]->getItem());
	pTile.second.erase(std::remove(pTile.second.begin(), pTile.second.end(), pTile.second[i]), pTile.second.end());

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

void InventoryDisplay::select(const int & collom, const int & row) {
	if (collom == 0) {
		pTile.first[row]->setColor(sf::Color::Green);
	}
	else if (collom == 1) {
		pTile.second[row]->setColor(sf::Color::Green);
	}
}


void InventoryDisplay::deselect(const int & collom, const int & row) {
	if (collom == 0) {
		pTile.first[row]->setColor(sf::Color::Black);
	}
	else if (collom == 1) {
		pTile.second[row]->setColor(sf::Color::Black);
	}
}


void InventoryDisplay::addItemToCharacter(const int & character, const int & item) {
	std::shared_ptr<Weapon> a = std::dynamic_pointer_cast<Weapon>(pTile.second[item]->getItem());
	std::shared_ptr<Armor> b = std::dynamic_pointer_cast<Armor>(pTile.second[item]->getItem());
	if (a != nullptr) {
		party.addWeapontoPartyMember(pTile.first[character]->getCharacter(), a);
		deleteItem(item);
	}
	else if (b != nullptr) {
		party.addArmortoPartyMember(pTile.first[character]->getCharacter(), b);
		deleteItem(item);
	}
	else {
		pTile.second[item]->setColor(sf::Color::Black);
	}
	pTile.first.clear();
	for (unsigned int i = 0; i < party.size(); i++) {
		pTile.first.push_back(
			std::make_shared<PlayerInventoryTile>(
				party[i],
				sf::Vector2f(0.0f, static_cast<float>(i * leftScreenSize.y / 4)),
				sf::Vector2f(static_cast<float>(leftScreenSize.x), static_cast<float>(leftScreenSize.y / 4))
				)
		);
	}
}


void InventoryDisplay::removeItemFromCharacer(const int & character, int & collom, const int & row) {
	if (pTile.first[character]->getWeaponTiles().size() !=0 || pTile.first[character]->getArmorTiles().size() !=0 ) {
		if (collom == 0) {
			std::shared_ptr<Weapon> a = std::dynamic_pointer_cast<Weapon>(pTile.first[character]->getItem(collom, row));
			if (a != nullptr) {
				party.addToInventory(pTile.first[character]->getItem(collom, row));
				pTile.first[character]->getCharacter()->removeWeapon(a->getWeaponSlot());
			}
			reloadTiles();
		}
		else if (collom == 1) {
			std::shared_ptr<Armor> b = std::dynamic_pointer_cast<Armor>(pTile.first[character]->getItem(collom, row));
			if (b != nullptr) {
				party.addToInventory(pTile.first[character]->getItem(collom, row));
				pTile.first[character]->getCharacter()->removeArmor(b->getArmorSlot());
			}
			reloadTiles();
		}
	}
}

void InventoryDisplay::reloadTiles(){
	pTile.first.clear();
	for (unsigned int i = 0; i < party.size(); i++) {
		pTile.first.push_back(
			std::make_shared<PlayerInventoryTile>(
				party[i],
				sf::Vector2f(0.0f, static_cast<float>(i * leftScreenSize.y / 4)),
				sf::Vector2f(static_cast<float>(leftScreenSize.x), static_cast<float>(leftScreenSize.y / 4))
				)
		);
	}
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