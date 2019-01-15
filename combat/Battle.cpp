#include "Battle.hpp"

Battle::Battle(sf::RenderWindow & window, std::vector<Character*> & player, std::vector<Character*> & monster, std::string & surrounding):
	window(window),
	players(player),
	monsters(monster),
	surroundings(surrounding)
{
	//Load the background
	std::string backgr = ""; 
	backgr += surroundings;
	
	if (!backgroundTexture.loadFromFile(backgr, sf::IntRect(0, 0, 1920, 1080))){
		std::cout << "Can't load background image: " << backgr << std::endl;
		if (!backgroundTexture.loadFromFile("error.JPG", sf::IntRect(0, 0, 1920, 1080))) {
			std::cout << "Can't load background image: " << backgr << std::endl;
		}
	}
	backgroundSprite.setTexture(backgroundTexture);
	sf::Vector2u backSize = backgroundTexture.getSize();
	float xScale = 1920.0 / backSize.x;
	float yScale = 800 / backSize.y;
	backgroundSprite.scale(sf::Vector2f(xScale, yScale));
}


Battle::~Battle(){
}

void Battle::start() {
};

void Battle::update() {
	if (!battleStarted) {
		battleStarted = true;
	}
	Show();
};

void Battle::Show() {
	window.clear();
	deltaTime = clock.restart().asSeconds();
	window.draw(backgroundSprite);
	//for (auto p : players) {
	//	p->Show(window);
	//}
	for (auto m : monsters) {
		m->update(0, deltaTime);
		m->Show(window);
	}

	window.display();
}

void Battle::Stop() {
	battleFinished = true;
}