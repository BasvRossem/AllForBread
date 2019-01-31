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

	////Set backGround
	takatiki.loadFromFile("takatikimap.png");
	background.setTexture(takatiki);
	background.setTextureRect({ 0, 0, 1920, 1080 });

	////Initiate tiles
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
	
	////Initiate selectbox 
	selectBox.setPosition(pTile.first[0]->getSelectboxPosition());
	selectBox.setSize(sf::Vector2f{ 80,80 });
	selectBox.setFillColor(sf::Color(12, 85, 135));
	selectBox.setOutlineColor(sf::Color(5, 55, 89));

	////varable needed for de selection
	selected.first = 0;
	selected.second = 0;
	lastSelected.first = 0;
	lastSelected.second = 0;

	////text for navigation
	font.loadFromFile("Assets/arial.ttf");
	text.setFont(font);
	text.setPosition(sf::Vector2f{ 10  ,1080 - 22 });
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);
	text.setString("");
	text.setOutlineThickness(1);
	text.setOutlineColor(sf::Color::Black);

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

	reloadTiles();

	isOpen = true;
	sound.playSoundEffect(SoundEffect::bagOpen);
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
				text.setString("Navigation use W A S D			Unequip Item from player use Enter																										Exit inventory use ESC");
				keyHandler.addListener(sf::Keyboard::A, []() {});
				keyHandler.addListener(sf::Keyboard::D, [&]() {if (pTile.second.size() != 0) { state = InventoryMenu::right;  setZeroSelected(1); }});
				keyHandler.addListener(sf::Keyboard::W, [&]() { changeSelected(0, -1); });
				keyHandler.addListener(sf::Keyboard::S, [&]() { changeSelected(0, 1);  });

				keyHandler.addListener(sf::Keyboard::U, []() {});
				keyHandler.addListener(sf::Keyboard::Enter, [&]() {if (pTile.first[selected.second]->getWeaponTiles().size() != 0 || pTile.first[selected.second]->getArmorTiles().size() != 0) { state = InventoryMenu::unequipItem; select(selected.first, selected.second); lastSelected.first = selected.first;  lastSelected.second = selected.second; setZeroSelected(0, lastSelected.second); }});
				keyHandler.addListener(sf::Keyboard::Delete, [&]() {});
				keyHandler.addListener(sf::Keyboard::Escape, [&]() {isOpen = false;});
				break;
			case InventoryMenu::right:
				text.setString("Navigation use W A S D		Equip Item to player use Enter			Use a Consumeble use U			Delete Item from Party inventory									Exit inventory use ESC");
				keyHandler.addListener(sf::Keyboard::A, [&]() {state = InventoryMenu::left;  setZeroSelected(0); });
				keyHandler.addListener(sf::Keyboard::D, []() {});
				keyHandler.addListener(sf::Keyboard::W, [&]() {changeSelected(1, -1); });
				keyHandler.addListener(sf::Keyboard::S, [&]() {changeSelected(1, 1);  });

				keyHandler.addListener(sf::Keyboard::U, [&]() {useItem(selected.second); if (itemToUse != nullptr) { isOpen = false; } });
				keyHandler.addListener(sf::Keyboard::Delete, [&]() {if (pTile.second.size() != 0) { state = InventoryMenu::left; deleteItem(selected.second); changeSelected(0, 0);state = InventoryMenu::left; }});
				keyHandler.addListener(sf::Keyboard::Enter, [&]() {state = InventoryMenu::equipItem; select(selected.first, selected.second); lastSelected.first = selected.first;  lastSelected.second = selected.second; setZeroSelected(0); });
				keyHandler.addListener(sf::Keyboard::Escape, [&]() {isOpen = false;});
				break;
			case InventoryMenu::equipItem:
				text.setString("Navigation use W S			Equip Item to player use Enter																												Exit Equip a Item use ESC");
				keyHandler.addListener(sf::Keyboard::A, []() {});
				keyHandler.addListener(sf::Keyboard::D, []() {});
				keyHandler.addListener(sf::Keyboard::W, [&]() { changeSelected(0, -1); });
				keyHandler.addListener(sf::Keyboard::S, [&]() { changeSelected(0, 1);  });

				keyHandler.addListener(sf::Keyboard::U, []() {});
				keyHandler.addListener(sf::Keyboard::Delete, [&]() {});
				keyHandler.addListener(sf::Keyboard::Escape, [&]() {state = InventoryMenu::right; reloadTiles();  setZeroSelected(0); });
				keyHandler.addListener(sf::Keyboard::Enter, [&]() {state = InventoryMenu::left;  addItemToCharacter(selected.second, lastSelected.second);  setZeroSelected(0); });

				break;
			case InventoryMenu::unequipItem:
				switch (eState) {
					case equip::left:
						text.setString("Navigation use W A S D			Unequip Item from player use Enter																											Exit Unequip a Item use ESC");
						keyHandler.addListener(sf::Keyboard::A, []() {});
						keyHandler.addListener(sf::Keyboard::D, [&]() { eState = equip::right;  changeSelected(1, 0, lastSelected.second); });
						keyHandler.addListener(sf::Keyboard::W, [&]() { changeSelected(0, -1, lastSelected.second); });
						keyHandler.addListener(sf::Keyboard::S, [&]() { changeSelected(0, 1, lastSelected.second);  });

						keyHandler.addListener(sf::Keyboard::U, []() {});
						keyHandler.addListener(sf::Keyboard::Delete, []() {});
						keyHandler.addListener(sf::Keyboard::Enter, [&]() {state = InventoryMenu::left; removeItemFromCharacer(lastSelected.second, selected.first, selected.second); setZeroSelected(0); reloadTiles(); });
						keyHandler.addListener(sf::Keyboard::Escape, [&]() {state = InventoryMenu::left; eState = equip::left; reloadTiles();   setZeroSelected(0); });
						break;
					case equip::right:
						text.setString("Navigation use W A S D			Unequip Item from player use Enter																											Exit Unequip a Item use ESC");
						keyHandler.addListener(sf::Keyboard::A, [&]() { eState = equip::left; changeSelected(0, 0, lastSelected.second); });
						keyHandler.addListener(sf::Keyboard::D, []() {});
						keyHandler.addListener(sf::Keyboard::W, [&]() { changeSelected(1, -1, lastSelected.second); });
						keyHandler.addListener(sf::Keyboard::S, [&]() { changeSelected(1, 1, lastSelected.second);  });

						keyHandler.addListener(sf::Keyboard::U, []() {});
						keyHandler.addListener(sf::Keyboard::Delete, []() {});
						keyHandler.addListener(sf::Keyboard::Enter, [&]() {state = InventoryMenu::left; removeItemFromCharacer(lastSelected.second, selected.first, selected.second); setZeroSelected(0); });
						keyHandler.addListener(sf::Keyboard::Escape, [&]() {state = InventoryMenu::left; reloadTiles();  setZeroSelected(0); });
						break;
				}
				break;
		}
	}


	sound.playSoundEffect(SoundEffect::bagClose);
	sf::sleep(sf::milliseconds(650));
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
	drawLeftScreen();
	drawRightScreen();
	window.draw(selectBox);
	window.draw(text);
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
		pTile.first[row]->setColor(sf::Color(123, 249, 84));
		pTile.first[row]->setBorderColor(sf::Color(72, 114, 59));
	}
	else if (collom == 1) {
		pTile.second[row]->setColor(sf::Color(123, 249, 84));
		pTile.second[row]->setBorderColor(sf::Color(72, 114, 59));
	}
}


void InventoryDisplay::addItemToCharacter(const int & character, const int & item) {
	// DONT TOUCH THIS FUNCTION WITH A 10FT POLE

	std::shared_ptr<Weapon> a = std::dynamic_pointer_cast<Weapon>(pTile.second[item]->getItem());
	std::shared_ptr<Armor> b = std::dynamic_pointer_cast<Armor>(pTile.second[item]->getItem());
	if (a != nullptr) {
		std::vector<int> itemsToRemove;
		switch (a->getWeaponSlot()) {
			case WeaponSlots::twohanded:
				for (unsigned int i = 0; i < pTile.first[character]->getWeaponTiles().size(); i++) {
					std::shared_ptr<Weapon> tmp = std::dynamic_pointer_cast<Weapon>(pTile.first[character]->getItem(0, i));
					if (tmp != nullptr) {
						itemsToRemove.push_back(i);
					}
				}
				for (unsigned int i = 0; i < itemsToRemove.size(); i++) {
					removeItemFromCharacer(character, 0, itemsToRemove[i] - i);
				}
				party.addWeapontoPartyMember(pTile.first[character]->getCharacter(), a);
				deleteItem(item);
				sound.playSoundEffect(SoundEffect::weaponEquip);
				break;
				
			case WeaponSlots::mainhand:
				for (unsigned int i = 0; i < pTile.first[character]->getWeaponTiles().size(); i++) {
					std::shared_ptr<Weapon> tmp = std::dynamic_pointer_cast<Weapon>(pTile.first[character]->getItem(0, i));
					if (tmp != nullptr) {
						if (tmp->getWeaponSlot() == WeaponSlots::mainhand || tmp->getWeaponSlot() == WeaponSlots::twohanded) {
							removeItemFromCharacer(character, 0, i);
						}
					}
				}
				party.addWeapontoPartyMember(pTile.first[character]->getCharacter(), a);
				deleteItem(item);
				break;

			case WeaponSlots::offhand:
				for (unsigned int i = 0; i < pTile.first[character]->getWeaponTiles().size(); i++) {
					std::shared_ptr<Weapon> tmp = std::dynamic_pointer_cast<Weapon>(pTile.first[character]->getItem(0, i));
					if (tmp != nullptr) {
						if (tmp->getWeaponSlot() == WeaponSlots::offhand || tmp->getWeaponSlot() == WeaponSlots::twohanded) {
							removeItemFromCharacer(character, 0, i);
						}
					}
				}
				party.addWeapontoPartyMember(pTile.first[character]->getCharacter(), a);
				deleteItem(item);
				break;

			default:
				break;
		}
	}
	else if (b != nullptr) {
		auto map = pTile.first[character]->getCharacter()->getArmorMap();
		std::vector<ArmorSlots> slots;
		for (auto m : map) {
			slots.push_back(m.first);
		}
		auto alreadyUquipt = std::find(slots.begin(), slots.end(), b->getArmorSlot());
		if (alreadyUquipt == slots.end()) {
			party.addArmortoPartyMember(pTile.first[character]->getCharacter(), b);
			deleteItem(item);
		} else {
			std::cout << "else van armor item equip\n";
			for (unsigned int i = 0; i < pTile.first[character]->getArmorTiles().size(); i++) {
				std::shared_ptr<Armor> tmp = std::dynamic_pointer_cast<Armor>(pTile.first[character]->getItem(1, i));
				if (tmp != nullptr) {
					if (tmp->getArmorSlot() == b->getArmorSlot()) {
						removeItemFromCharacer(character, 1, i);
						party.addArmortoPartyMember(pTile.first[character]->getCharacter(), b);
						deleteItem(item);
						sound.playSoundEffect(SoundEffect::armorEquip);
					}
				}
			}
		}
	}
	reloadTiles();
}


void InventoryDisplay::removeItemFromCharacer(const int & character, const int & collom, const int & row) {
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

void InventoryDisplay::useItem(const unsigned int & row) {
	itemToUse = std::dynamic_pointer_cast<Consumable>(pTile.second[row]->getItem());
	if (itemToUse != nullptr) {	
		itemToUse->activate();
		itemToUse->setQuantityUses(itemToUse->getQuantityUses() - 1);
		if (itemToUse->getQuantityUses() <= 0) {
			deleteItem(row);
		}
	}
}

std::shared_ptr<Consumable> InventoryDisplay::getUsedItem() {
	std::shared_ptr<Consumable> temp = itemToUse;
	itemToUse = nullptr;
	return temp;
}