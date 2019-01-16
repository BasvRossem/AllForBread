#include "Combat.hpp"

Combat::Combat(sf::RenderWindow & window, std::vector<Character*> & player, std::vector<Character*> & monster, std::string & surrounding):
	State(window),
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


Combat::~Combat(){
}

void Combat::start() {
};

void Combat::update() {
	if (!CombatStarted) {
		CombatStarted = true;
	}
	
	Show();
};

void Combat::Show() {
	window.clear();
	deltaTime = clock.restart().asSeconds();
	window.draw(backgroundSprite);
	

	for (auto m : monsters) {
	}

	window.display();
}

void Combat::Stop() {
	CombatFinished = true;
}