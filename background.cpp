#include "background.hpp"
#include <SFML/Graphics.hpp>
#include <utility> 
#include <string>
#include <vector>

BackGround::add(const std::string &name, const std::string & fileName) {
	backGrounds.push_back(std::pair<std::string, std::string>(name, fileName);
}

BackGround::getPath(const std::string & backGroundName) {
	for (auto const & background : backGrounds) {
		if (background.first == backGroundName) {
			return background.second;
		}
	}
}
BackGround::SetBackGround(const std::string & backGroundName, sf::RenderWindow & window){
	sf::Texture texture;
	sf::Sprite sprite;
	if (texture.loadFromFile(getPath(backGroundName)) {
			sprite.setTexture(texture);
			sprite.setPosition(0,0);
		}
	window.draw(sprite);
}
