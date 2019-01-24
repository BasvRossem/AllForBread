#include "Menu.hpp"



Menu::Menu(std::string & surroundings, BackGround & backGround):
	backGround(backGround),
	surroundings(surroundings),
	size(200,200)
{
	selectRectangle.setFillColor(sf::Color::Blue);
	selectRectangle.setPosition(850, 435);
	selectRectangle.setSize(sf::Vector2f{ size.x + 10 , size.y + 10 });
}

void Menu::addTile(std::string & imageName, std::function<void()> & f) {
	auto p = sf::Vector2f{ 435 + float(210 * tiles.size()), 440 };
	Tile(imageName, p, size, f);
	tiles.push_back(std::make_shared<Tile>(imageName, p, size, f));
}

void Menu::selectChangePosition(const int & id) {
	if (id >= 0 && id < tiles.size()) {
		selectedID = id;
		selectRectangle.setPosition(sf::Vector2f{ 430 + float(210 * id), 435 });
	}
}

void Menu::select() {
	tiles[selectedID]->activate();
}

void Menu::update(sf::RenderWindow & window) {
	bool menu = true;
	backGround.setBackGround(surroundings, sf::Vector2f{ 1920,1080 });
	KeyboardHandler keyHandl;
	sf::Vector2f mousePosition = sf::Vector2f{ sf::Mouse::getPosition(window) };
	keyHandl.addListener(sf::Keyboard::Enter, [&]() {select(); });
	keyHandl.addListener(sf::Keyboard::Escape, [&menu]() {menu = false; });
	keyHandl.addListener(sf::Keyboard::A, [&]() {selectChangePosition(selectedID - 1); });
	keyHandl.addListener(sf::Keyboard::D, [&]() {selectChangePosition(selectedID + 1); });

	while (menu == true) {
		sf::Event event;
		mousePosition = sf::Vector2f{ sf::Mouse::getPosition(window) };
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
				keyHandl.processKey(event.key.code);
			if (event.type == sf::Event::MouseButtonPressed) {
				for (unsigned int i = 0; i < tiles.size(); i++) {
					if (tiles[i]->getGlobalBound().contains(mousePosition)) {
						select();
					}
				}
			}
		}	

		for (unsigned int i = 0; i < tiles.size(); i++) {
			if (tiles[i]->getGlobalBound().contains(mousePosition)) {
				selectChangePosition(i);
			}
		}

		///draw menu
		window.clear();
		backGround.draw(window);
		if (tiles.size() != 0) {
			window.draw(selectRectangle);
		}
		for (auto &t : tiles) {
			t->draw(window);
		}
		window.display();
	}
}

