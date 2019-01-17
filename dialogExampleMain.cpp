#include <iostream>

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "virtualScreen/virtualScreen.hpp"
#include "Core/dialogBox.h"

int main2(int argc, char *argv[]) {
	sf::RenderWindow window{ sf::VideoMode{640, 480}, "SFML window" };
	sf::Vector2i dialogBoxSize(500, 500);
	sf::Vector2f dialogBoxPos(0, 0);
	DialogBox diaBox(window, 20, 4, "arial.ttf", dialogBoxSize, dialogBoxPos);

	std::vector<std::string> test = { "aap", "aap2" };

	while (true) {
		window.display();
		sf::sleep(sf::milliseconds(1000));
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		diaBox.printPerm(test);
		diaBox.draw();
		window.display();

		sf::sleep(sf::milliseconds(1000 / 60));
	}

}
