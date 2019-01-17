#pragma once
#include <SFML/Graphics.hpp>
#include <utility> 
#include <string>
#include <vector>


///@file

///\brief
/// A class that create and set the background.
class BackGround {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	std::vector<std::pair<std::string, std::string>> backGrounds;
public:
	///\brief
	///Add a  std::pair of image name and fileme to the vector.
	void add(const std::string &, const std::string &);
	
	///\brief
	///Gets the path of the image that you are searching for.
	std::string getPath(const std::string &);
	
	///\brief
	/// Sets a backgroud.
	void SetBackGround(const std::string &);
	
	///\brief
	///Draws the backgroud.
	void draw(sf::RenderWindow &);
};

