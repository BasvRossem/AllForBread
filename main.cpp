#include <SFML/Graphics.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include "Character/Party.hpp"
#include "states/Combat.hpp"
#include "Character/Monster.hpp"

int main(){

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "The Holy Bread of Takatiki", sf::Style::Fullscreen);
	window.setFramerateLimit(0);

	PlayerCharacter testCharacter = PlayerCharacter("Anubis, the distructor of hopes and dreams","Assets/AnubisIdle.png");
	Character testMonster= Character("Rupert, the Poopert Robot", "Assets/RobotIdle.png", 12);
	testMonster.makeMonster();

	std::vector<std::shared_ptr<PlayerCharacter>> heroVector = {std::make_shared<PlayerCharacter>(testCharacter)};

	std::vector< std::shared_ptr<Character>> monsterVector = { std::make_shared <Character>(testMonster) };
	CharacterContainer< std::shared_ptr<Character >> monsters = (monsterVector);
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
	}
	return 0;
}