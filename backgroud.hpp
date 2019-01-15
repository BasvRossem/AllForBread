#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SFML/Graphics.hpp>
#include <utility> 
#include <string>
#include <vector>

class BackGround {
private:
	std::vector<std::pair<std::string, std::string>> backGrounds;
public:
	void add(const std::string &name, std::string & fileName);
	std::string getPath(const std::string & backGroundName);
	void SetBackGround(const std::string & backGroundName, sf::RenderWindow & window);
	
};

#enfif //!BACKGROUND_HPP