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
	PlayerCharacter testCharacter2 = PlayerCharacter("Anubis, the distructor of hopes and dreams","test1.png");

	testCharacter.increaseAbilityScore(AbilityScores::arcanism, 12);
	testCharacter.increaseAbilityScore(AbilityScores::endurance, 5);
	testCharacter.decreaseAbilityScore(AbilityScores::strength, 3);
	testCharacter.decreaseAbilityScore(AbilityScores::charisma, 1);

	testCharacter2.increaseAbilityScore(AbilityScores::strength, 33);
	testCharacter2.increaseAbilityScore(AbilityScores::endurance, 12);
	testCharacter2.decreaseAbilityScore(AbilityScores::arcanism, 4);
	testCharacter2.decreaseAbilityScore(AbilityScores::dexterity, 9);

	std::vector<std::shared_ptr<PlayerCharacter>> heroVector = {std::make_shared<PlayerCharacter>(testCharacter), std::make_shared<PlayerCharacter>(testCharacter2) };
	
	Party heroParty(heroVector);

	for (auto & c : heroVector) {
		c->printAbilityStats();
	}

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
		testCharacter.draw(window);
		testCharacter.update();
		
		window.display();
	} //END test SFML
	return 0;
}