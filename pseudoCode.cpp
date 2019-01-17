#include <SFML/Graphics.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include "Character/Party.hpp"

int main(){
	//test SFML
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
	window.setFramerateLimit(60);

	std::shared_ptr<sf::CircleShape> myCircle(new sf::CircleShape);
	myCircle->setRadius(100);
	myCircle->setFillColor(sf::Color::Green);
	myCircle->setPosition(sf::Vector2f(300, 300));

	PlayerCharacter testCharacter = PlayerCharacter("Anubis, the distructor of hopes and dreams","test1.png");
	std::vector<std::shared_ptr<PlayerCharacter>> heroVector = {std::make_shared<PlayerCharacter>(testCharacter)};
	
	Party heroParty(heroVector);

	std::cout << heroParty[0]->getHealth() << '\n';
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		
		window.draw(*myCircle);
		testCharacter.Show(window);
		testCharacter.update();
		
		window.display();

	return 0;
}
