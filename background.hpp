#pragma once

#include <SFML/Graphics.hpp>
#include <utility> 
#include <string>
#include <vector>

class BackGround {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	std::vector<std::pair<std::string, std::string>> backGrounds;
public:
	void add(const std::string &name, std::string &fileName);
	std::string getPath(const std::string & backGroundName);
	void SetBackGround(const std::string & backGroundName);
	void draw(sf::RenderWindow &window);
};

