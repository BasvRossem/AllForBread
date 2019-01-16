#include <iostream>

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "virtualscreen/virtualScreen.hpp"
#include "dialogBox.h"

int main(int argc, char *argv[]) {
	sf::RenderWindow window{ sf::VideoMode{640, 480}, "SFML window" };
	sf::Vector2f dialogBoxSize(500, 500);
	DialogBox diaBox(window, 20, 4, "arial.ttf", dialogBoxSize);
	int count = 0;
	while (true) {
		window.display();
		sf::sleep(sf::milliseconds(1000));
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		std::cout << "start zooi" << '\n';
		std::string str = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
		str += std::to_string(count);
		std::cout << "outside game: " << '\n';
		diaBox.print(str);
		count++;
		std::cout << "eind zooi" << '\n';

		window.display();

		sf::sleep(sf::milliseconds(1000 / 60));
	}

}