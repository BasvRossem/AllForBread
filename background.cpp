#include "background.hpp"


void BackGround::add(const std::string &name, std::string &fileName) {
	backGrounds.push_back(std::pair<std::string, std::string>(name, fileName));
}

std::string BackGround::getPath(const std::string & backGroundName) {
	for (auto const & background : backGrounds) {
		if (background.first == backGroundName) {
			return background.second;
		}
	}
	return 0;
}
void BackGround::SetBackGround(const std::string & backGroundName){
	if (texture.loadFromFile(getPath(backGroundName))) {
		sprite.setTexture(texture);
		sprite.setPosition(0,0);
	}
}

void BackGround::draw(sf::RenderWindow &window) {
	window.draw(sprite);
}
