#include "virtualScreen.hpp"


VirtualScreen::VirtualScreen(const unsigned int & width, const unsigned int & height) {
	setSize(width,height);
}

void VirtualScreen::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	sf::Sprite sprScreen(vScreen.getTexture());
	states.transform.translate(location);
	target.draw(sprScreen, states);
}

bool VirtualScreen::collision(const sf::Vector2i & point)
{
	sf::Sprite spr(vScreen.getTexture());
	spr.setPosition(location);
	
	return spr.getGlobalBounds().contains(sf::Vector2f(point));
}