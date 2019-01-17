#include <SFML/Graphics.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include "Character/Party.hpp"
#include "states/Combat.hpp"

int main(){
	//test SFML
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "The Holy Bread of Takatiki", sf::Style::Fullscreen);
	window.setFramerateLimit(0);

	PlayerCharacter testCharacter = PlayerCharacter("Anubis, the distructor of hopes and dreams","Assets/AnubisIdle.png");
	Character testMonster= Character("Big Dick Nigga Jim", "Assets/RobotIdle.png", 12);
	testMonster.makeMonster();

	std::vector<std::shared_ptr<PlayerCharacter>> heroVector = {std::make_shared<PlayerCharacter>(testCharacter)};

	std::vector<Character> monsterVector = { testMonster };
	CharacterContainer<Character > monsters = ( monsterVector);
	Party heroParty(heroVector);

	std::string backgroundImage = "Assets/background680.png";
	Combat testCombat(window, heroParty, monsters, backgroundImage);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		
		testCombat.update();


		window.display();
	} //END test SFML
	return 0;
}