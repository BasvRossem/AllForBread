#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <sstream>

class Debug
{
private:
	static const unsigned int windowHeight = 500;
	static const unsigned int windowWidth = 1000;

	inline static std::vector<std::vector<sf::Text>>& debugItem() {
		static std::vector<std::vector<sf::Text>> t;
		return t;
	}

	inline static sf::RenderWindow& window() {
		static sf::RenderWindow w;
		return w;
	}

	inline static sf::Font& font() {
		static sf::Font f;
		return f;
	}

	inline static Debug& getInstance() {
		static Debug d;
		return d;
	}

	Debug() {
		window().create(sf::VideoMode({ windowWidth, windowHeight }), "Debug Window");
		font().loadFromFile("aliee13.ttf");
	}

	static void addItem(sf::Text& t);

	template <typename T, typename Y>
	static void unpackToScreen(std::ostringstream & s, T name, Y value) {
		s << name << ":    " << value << '\n' << '\n';
		sf::Text t(s.str(), font(), 12);
		t.setFillColor(sf::Color::White);
		addItem(t);
		window().draw(t);
	}

	template <typename T, typename Y, typename ... Attributes>
	static void unpackToScreen(std::ostringstream & s, T name, Y value, Attributes ... attributes) {
		s << name << ":    " << value << '\n';
		unpackToScreen(s,attributes...);
	}

public:

	//static debug function. needs to be used as following
	//Debug::debug(title, name_attr1, attr1, name_attr2, attr2, etc)
	template<typename T, typename ... Attributes>
	static void debug(T title, Attributes ... attributes) {
		getInstance();
		std::ostringstream s;
		s << title << '\n';
		unpackToScreen(s,attributes...);
	}

	//update function needs to be called everytime at the end of your game loop
	static void update();
};

