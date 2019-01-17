#include "Combat.hpp"

Combat::Combat(sf::RenderWindow & window, Party & party, CharacterContainer<Character> & monster, std::string surrounding):
	State(window),
	party(party),
	monsters(monster),
	surroundings(surrounding),
	animationScreen(animationScreenSize),
	menuScreen(menuScreenSize)
{
	sf::Vector2f animationScreenTopLeft(0.0, 0.0);
	sf::Vector2f menuScreenTopLeft(0.0, 680);
	animationScreen.setLocation(animationScreenTopLeft);
	menuScreen.setLocation(menuScreenTopLeft);

	//Load the background
	std::string backgr = ""; 
	backgr += surroundings;
	if (!backgroundTexture.loadFromFile(surroundings, sf::IntRect(0, 0, 1920, 1080))){
		std::cout << "Can't load background image: " << backgr << std::endl;
		if (!backgroundTexture.loadFromFile("error.JPG", sf::IntRect(0, 0, 1920, 1080))) {
			std::cout << "Can't load background image: " << backgr << std::endl;
		}
	}
	backgroundSprite.setTexture(backgroundTexture);
	sf::Vector2u backSize = backgroundTexture.getSize();
	float xScale = 1920.0 / backSize.x;
	float yScale = 680.0 / backSize.y;
	backgroundSprite.scale(sf::Vector2f(xScale, yScale));
}


Combat::~Combat(){
}

void Combat::start() {

};

State* Combat::update() {
	
	for(;;){
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		draw();
	}
	
	
	return nullptr;
};

void Combat::draw() {
	window.clear();
	animationScreen.drawSurfaceClear();
	menuScreen.drawSurfaceClear(sf::Color::Blue);

	animationScreen.drawSurfaceDraw(backgroundSprite);
	for (int i = 0; i < party.size(); i++) {
		party[i]->update();
		party[i]->draw(animationScreen);
	}
	for (int j = 0; j < monsters.size(); j++) {
		monsters[j].update();
		monsters[j].draw(animationScreen);
	}

	animationScreen.drawSurfaceDisplay();
	menuScreen.drawSurfaceDisplay();
	window.draw(animationScreen);
	window.draw(menuScreen);
	//window.draw(backgroundSprite);
	window.display();
}

void Combat::Stop() {
	CombatFinished = true;
}