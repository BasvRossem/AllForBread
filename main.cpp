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

	PlayerCharacter pcAnubis = PlayerCharacter("Anubis, the distructor of hopes and dreams","test1.png");
	PlayerCharacter pcJoop = PlayerCharacter("Joop","test1.png");
	Character mDracula = PlayerCharacter("Dracula","test1.png");
	Character mVlad = PlayerCharacter("Vlad","test1.png");
	Character mStrahd = PlayerCharacter("Strahd","test1.png");

	pcAnubis.increaseAbilityScore(AbilityScores::arcanism, 12);
	pcAnubis.increaseAbilityScore(AbilityScores::endurance, 5);
	pcAnubis.decreaseAbilityScore(AbilityScores::strength, 3);
	pcAnubis.decreaseAbilityScore(AbilityScores::charisma, 1);

	pcJoop.increaseAbilityScore(AbilityScores::strength, 33);
	pcJoop.increaseAbilityScore(AbilityScores::endurance, 12);
	pcJoop.decreaseAbilityScore(AbilityScores::arcanism, 4);
	pcJoop.decreaseAbilityScore(AbilityScores::dexterity, 9);


	pcAnubis.addCombatAction(std::make_shared<Attack>("Zwaardslag", 12));
	pcAnubis.activateCombatAction(0, std::make_shared<Character>(pcJoop));

	CharacterContainer<std::shared_ptr<Character>> monsters(std::vector<std::shared_ptr<Character>>{
		std::make_shared<Character>(mDracula), 
		std::make_shared<Character>(mVlad), 
		std::make_shared<Character>(mStrahd)
	});
	


	std::vector<std::shared_ptr<PlayerCharacter>> heroVector = {std::make_shared<PlayerCharacter>(pcAnubis), std::make_shared<PlayerCharacter>(pcJoop) };
	
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
		pcAnubis.draw(window);
		pcAnubis.update();
		
		window.display();
	} //END test SFML
	return 0;
}