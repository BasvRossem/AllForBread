#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "virtualscreen/virtualScreen.hpp"
#include <cctype>
/// @file

/// \brief
/// A class that handles the dialog box and the way the text displays in it.
class DialogBox {

private:
	VirtualScreen diaBox;
	sf::RenderWindow& w;

	uint_fast16_t page;
	uint_fast16_t bufferWidth;
	uint_fast16_t maxLines;

	sf::Font font;
	sf::Text text;

public:
	DialogBox(sf::RenderWindow& window, uint_least16_t bufferWidth, uint_fast16_t maxLines, std::string fontFileLocation, sf::Vector2f& size, sf::vector2f& position);
	///\brief
	/// draws the screen part and the text
	void draw();

	///\brief
	/// Prints the given string in the dialog box.
	///\details
	/// When call print function pauses the game, converts the string and prints what needs to be printed.
	/// When all displayable rows have been drawn it waits for the input of the player to display the next rows.
	/// It keeps on doing this until all the text has been displayed.
	void print(std::string& str);
	
	///\brief
	/// A wordwrap function for the dialog boxes.
	///\details
	/// returns a vector of strings that contains all the text neatly wordwrapped to the defined max character width.
	/// this makes it that all the text given to the dialogbox is able to be displayed.
	std::vector<std::string> wordwrap(std::string& str);
};