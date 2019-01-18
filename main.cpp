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

	std::shared_ptr<PlayerCharacter> pcAnubis = std::make_shared<PlayerCharacter>("Anubis, the distructor of hopes and dreams","test1.png");
	std::shared_ptr<PlayerCharacter> pcJoop = std::make_shared<PlayerCharacter>("Joop","test1.png");
	std::shared_ptr<Character> mDracula = std::make_shared<PlayerCharacter>("Dracula","test1.png");
	std::shared_ptr<Character> mVlad = std::make_shared<PlayerCharacter>("Vlad","test1.png");
	std::shared_ptr<Character> mStrahd = std::make_shared<PlayerCharacter>("Strahd","test1.png");

	pcAnubis->increaseAbilityScore(AbilityScores::arcanism, 12);
	pcAnubis->increaseAbilityScore(AbilityScores::endurance, 5);
	pcAnubis->decreaseAbilityScore(AbilityScores::strength, 3);
	pcAnubis->decreaseAbilityScore(AbilityScores::charisma, 1);

	pcJoop->increaseAbilityScore(AbilityScores::strength, 33);
	pcJoop->increaseAbilityScore(AbilityScores::endurance, 12);
	pcJoop->decreaseAbilityScore(AbilityScores::arcanism, 4);
	pcJoop->decreaseAbilityScore(AbilityScores::dexterity, 9);


	std::cout << pcJoop->getHealth() << '\n';

	pcAnubis->addCombatAction(std::make_shared<Attack>("Zwaardslag", 12));
	pcAnubis->activateCombatAction(0, pcJoop);

	std::cout << pcJoop->getHealth() << '\n';

	CharacterContainer<std::shared_ptr<Character>> monsters(std::vector<std::shared_ptr<Character>>{
		mDracula, 
		mVlad, 
		mStrahd
	});
	


	std::vector<std::shared_ptr<PlayerCharacter>> heroVector = {pcAnubis, pcJoop};
	
	Party heroParty(heroVector);

	CharacterContainer<std::shared_ptr<Character>, 8> totalCombatants;
	totalCombatants.add(monsters);
	totalCombatants.add(heroParty);

	for (unsigned int i = 0; i < totalCombatants.size(); i++) {
		totalCombatants[i]->printAbilityStats();
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
		pcAnubis->draw(window);
		pcAnubis->update();
		
		window.display();
	} //END test SFML
	return 0;
}