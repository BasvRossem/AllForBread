a Database class

#include <SFML/Graphics.hpp>
#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>
#include "Database.hpp"

class special_class
{
public:
	void func(char *argv, char *azColName)
	{
		std::cout << azColName << " - " << argv << std::endl;
	}
};

int callback(void * frstargu, int argc, char **argv, char **azColName) {

	special_class * b = (special_class*)frstargu;

	for (int i = 0; i < argc; i++)
	{
		b->func(argv[i],azColName[i]);
	}
	return 0;
}

int Itemcallback(void * ignored, int argc, char **argv, char **azColName) {

	for (int i = 0; i < argc; i++)
	{
		std::cout << azColName[i] << ": " << argv[i] << std::endl;
	}
	std::cout << std::endl;
	return 0;
}


int main()
{
	

	//test SFML
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	special_class A;

	Database db("test.db");
	
	//sqlite3_exec(db, "INSERT INTO Test (name) VALUES ('jan');", callback, NULL, NULL);

	db.cmd("SELECT * FROM Test; ", callback, &A);
	std::cout << std::endl;
	//db.cmd("SELECT * FROM Items; ", Itemcallback);

	db.cmd("SELECT * FROM Items; ", [](void * ignored, int argc, char **argv, char **azColName)->int {

		for (int i = 0; i < argc; i++)
		{
			std::cout << azColName[i] << ": " << argv[i] << std::endl;
		}
		std::cout << std::endl;
		return 0;
	});



	db.close();



	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	} //END test SFML

	return 0;
}
