#pragma once
#include <SFML/Graphics.hpp>
#include <utility> 
#include <string>
#include <vector>
#include "virtualScreen/virtualScreen.hpp"


///@file

///\brief
/// A class that create and set the background.
class BackGround {
private:
	sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;
	std::vector<std::pair<std::string, std::string>> backGrounds;
public:
	///\brief
	///Add a  std::pair of image name and fileme to the vector.
	void add(const std::string &, const std::string &);
	
	///\brief
	///Gets the path of the image that you are searching for.
	std::string getPath(const std::string &);
	
	///\brief
	/// Sets a backgroud from window.
	void SetBackGround(const std::string &, sf::RenderWindow &);

	///\brief
	/// Sets a backgroud from a size vector.
	void SetBackGround(const std::string &, sf::Vector2f &);


	///\brief
	///Draws the backgroud to window.
	void draw(sf::RenderWindow &);

	///\brief
	///Draws the backgroud to virtualscreen.
	void draw(VirtualScreen &);


};

