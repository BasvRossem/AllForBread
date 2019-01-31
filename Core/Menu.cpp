#include "Menu.hpp"



Menu::Menu(std::string & surroundings, BackGround & backGround):
	backGround(backGround),
	surroundings(surroundings),
	size(200,200)
{
	selectCircle.setFillColor(sf::Color(47, 108, 206));
	selectCircle.setPosition(850, 435);
	selectCircle.setRadius((size.x + 10)/2);
}

void Menu::addTile(std::string & imageName, std::function<void()> & f) {
	auto p = sf::Vector2f{ 435 + float(210 * tiles.size()), 440 };
	Tile(imageName, p, size, f);
	tiles.push_back(std::make_shared<Tile>(imageName, p, size, f));
	selectChangePosition(int(tiles.size() / 2));
}

void Menu::selectChangePosition(const unsigned int & id) {
	if (id >= 0 && id < tiles.size()) {
		selectedID = id;
		selectCircle.setPosition(sf::Vector2f{ 430 + float(210 * id), 435 });
	}
}

void Menu::select() {
	tiles[selectedID]->activate();
}

void Menu::draw(sf::RenderWindow & window) {
	window.clear();
	backGround.draw(window);
	if (tiles.size() != 0) {
		window.draw(selectCircle);
	}
	for (auto &t : tiles) {
		t->draw(window);
	}
	window.display();
}

void Menu::update(sf::RenderWindow & window) {
	bool menu = true;
	backGround.setBackGround(surroundings, sf::Vector2f{ 0,0 }, sf::Vector2f{ 1920,1080 });
	KeyboardHandler keyHandl;
	keyHandl.addListener(sf::Keyboard::Enter, [&]() {select(); });
	keyHandl.addListener(sf::Keyboard::Escape, [&menu]() {menu = false; });
	keyHandl.addListener(sf::Keyboard::A, [&]() {selectChangePosition(selectedID - 1); });
	keyHandl.addListener(sf::Keyboard::D, [&]() {selectChangePosition(selectedID + 1); });

	while (menu == true && window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
				keyHandl.processKey(event.key.code);
		}	
		draw(window);
	}
}

