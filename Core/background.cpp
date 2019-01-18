#include "background.hpp"


void BackGround::add(const std::string &name, const std::string &fileName) {
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
void BackGround::SetBackGround(const std::string & backGroundName, sf::RenderWindow & window){
	if (backgroundTexture.loadFromFile(getPath(backGroundName))){
		sf::Vector2f size = sf::Vector2f{ backgroundTexture.getSize() };
		backgroundSprite.setTexture(backgroundTexture);
		backgroundSprite.setPosition(0, 0);
		backgroundSprite.scale(sf::Vector2f{ window.getSize().x / size.x, window.getSize().y / size.y });
	}
}

void BackGround::SetBackGround(const std::string & backGroundName, sf::Vector2f & windowSize) {
	if (backgroundTexture.loadFromFile(getPath(backGroundName))) {
		sf::Vector2f size = sf::Vector2f{ backgroundTexture.getSize() };
		backgroundSprite.setTexture(backgroundTexture);
		backgroundSprite.setPosition(0, 0);
		backgroundSprite.scale(sf::Vector2f{ windowSize.x / size.x, windowSize.y / size.y });
	}
}


void BackGround::draw(sf::RenderWindow &window) {
	window.draw(backgroundSprite);
}

void BackGround::draw(VirtualScreen &virtualScreen) {
	virtualScreen.drawSurfaceDraw(backgroundSprite);
}