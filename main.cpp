#include <SFML/Graphics.hpp>

class state {
public:
	virtual state * update() = 0;
protected:
	sf::RenderWindow & window;
	state(sf::RenderWindow&w) : window(w) {}
};

class overworld : public state {
public:
	overworld(sf::RenderWindow&w) : state(w) {};


	// Inherited via state
	virtual state * update() override
	{
		sf::Event event;
		while (window.pollEvent(event)) {

		}

		window.clear();

		window.display();

		return events();

	}

};

class cave : public state {
private:
	state * current;
public:
	cave(sf::RenderWindow&w) : state(w) {  };


	// Inherited via state
	virtual state * update() override
	{

		sf::Event event;
		while (window.pollEvent(event)) {

		}

		window.clear();

		window.display();

		if (exit_cave) return nullptr;

		

		while (current != nullptr)
		{
			current = current->update();
		}

		return this;

	}

};

class combat : public state {
public:
	overworld(sf::RenderWindow&w) : state(w) {};


	// Inherited via state
	virtual state * update() override
	{
		sf::Event event;
		while (window.pollEvent(event)) {

		}

		window.clear();

		window.display();

	}

};


int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

	overworld base(window);
	state * current;

	while (window.isOpen())
	{
		event = base.update();

		switch (event)
		{
		case cave:
			current = new cave(window);
			break;
		default:
			break;
		}


		while current != nullptr {
			current = current->update();

		}

	}

	return 0;
}