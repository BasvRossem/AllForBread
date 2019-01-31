#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include "../virtualScreen/virtualScreen.hpp"
#include <cctype>
#include <cstdlib>
#include <functional>
#include "KeyboardHandler.hpp"
#include <sstream>
#include <iostream>
#include "background.hpp"

/// @file

/// \brief
/// A class that handles the dialog box and the way the text displays in it.
class DialogBox {

private:
	VirtualScreen diaBox;
	sf::RenderWindow& w;
	uint_fast16_t bufferWidth;
	uint_fast16_t maxLines;

	sf::Font font;
	sf::Text text;
	sf::SoundBuffer soundBuffer;
	sf::Sound feedbackSound;
	sf::Color backgroundColor;

	sf::RectangleShape backgroundSquare;

public:
	DialogBox(sf::RenderWindow& window, uint_least16_t bufferWidth, uint_fast16_t maxLines, std::string fontFileLocation, sf::Vector2i size, sf::Vector2f position, sf::Color backgroundColor = sf::Color::Black, sf::Color edgeColor = sf::Color(102, 51, 0));
	///\brief
	/// draws the screen part and the text
	void draw();


	void setSound(std::string soundFileName);

	void setBackgroundColor(sf::Color color);

	void setTextFillColor(sf::Color color);

	void setTextOutlineColor(sf::Color color);

	void setTextCharacterSize(int size);

	void setTextLetterSpacing(float spacingFactor);

	void setTextLineSpacing(float spacingFactor);

	void setTextPosition(sf::Vector2f position);

	void clearText();
	
	///\brief
	/// Prints the given string in the dialog box.
	///\details
	/// When call print function pauses the game, converts the string and prints what needs to be printed.
	/// When all displayable rows have been drawn it waits for the input of the player to display the next rows.
	/// It keeps on doing this until all the text has been displayed.
	void print(std::string str, std::string background = std::string("takatikimap.png"), bool sound = true, int speed = 0);

	///\brief
	/// A wordwrap function for the dialog boxes.
	///\details
	/// returns a vector of strings that contains all the text neatly wordwrapped to the defined max character width.
	/// this makes it that all the text given to the dialogbox is able to be displayed.
	std::vector<std::string> wordwrap(std::string& str);

	///\brief
	/// user controlled print function
	///\details
	/// When given a vector of strings it displays the vector on screen until it is cleared or it is overwritten with new text.
	void printPerm(std::vector<std::string>&);

	///\brief
	/// clears the dialoguebox
	void clear();

	///\brief
	/// when given a vector of pairs, the first is a name, the second an std::function
	int printChoices(std::vector<std::pair<std::string, std::function<void()>>>& choices, std::string background = std::string("takatikimap.png"));
};