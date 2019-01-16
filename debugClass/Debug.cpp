#include "Debug.hpp"

void Debug::addItem(sf::Text & t) {
	if (debugItem().empty()) {
		debugItem().push_back(std::vector<sf::Text>());

	}
	else {
		auto p = (debugItem().end() - 1)->end() - 1;
		float y = p->getGlobalBounds().height + p->getGlobalBounds().top;
		float x;
		if (y > windowHeight) {
			y = 0;
			debugItem().push_back(std::vector<sf::Text>());
		}

		if (debugItem().size() == 1) {
			x = 0;
		}
		else {
			float max = 0;
			for (const auto & obj : *(debugItem().end() - 2)) {
				if ((obj.getGlobalBounds().left + obj.getGlobalBounds().width) > max) {
					max = (obj.getGlobalBounds().left + obj.getGlobalBounds().width + 30);
				}
			}
			x = max;
		}
		t.setPosition(sf::Vector2f(x, y));
	}
	(debugItem().end() - 1)->push_back(t);
}

void Debug::update() {
	window().display();
	debugItem().clear();
	window().clear();
	sf::Event e;
	while (window().pollEvent(e)) {
	}
}
