#include "playerInventoryTile.hpp"
#include "../Character/EnumClasses.hpp"


PlayerInventoryTile::PlayerInventoryTile(std::shared_ptr<PlayerCharacter> character, const sf::Vector2f & position, const sf::Vector2f & size) :
	character(character)
{
	weapons = character->getWeaponMap();
	armor = character->getArmorMap();


	rect.setPosition(position);
	rect.setSize(size);
	rect.setFillColor(sf::Color::Black);

	font.loadFromFile("Assets/PIXEARG_.ttf");
	textPlayerName.setFont(font);
	textPlayerName.setPosition(sf::Vector2f{ position.x + 10, position.y + size.y / 7 * 1 });
	textPlayerName.setCharacterSize(int(size.y / 7));
	textPlayerName.setStyle(sf::Text::Bold);
	textPlayerName.setFillColor(sf::Color::White);
	textPlayerName.setString(character->getName());

	int i = 0;
	for (auto & w : weapons) {
		textWaponNames.push_back(sf::Text());
		textWaponNames[i].setFont(font);
		textWaponNames[i].setPosition(sf::Vector2f{ position.x + 10, position.y + size.y / 7 * (i + 3 + i * 1) });
		textWaponNames[i].setCharacterSize(int(size.y / 7));
		textWaponNames[i].setStyle(sf::Text::Bold);
		textWaponNames[i].setFillColor(sf::Color::White);
		textWaponNames[i].setString(w.second.getName());
		i++;
	}

	i = 0;
	for (auto & a : armor) {
		textArmorNames.push_back(sf::Text());
		textArmorNames[i].setFont(font);
		textArmorNames[i].setPosition(sf::Vector2f{ position.x + 400, position.y + size.y / 12 * (i + 1 + i * 1) });
		textArmorNames[i].setCharacterSize(int(size.y / 12));
		textArmorNames[i].setStyle(sf::Text::Bold);
		textArmorNames[i].setFillColor(sf::Color::White);
		textArmorNames[i].setString(a.second.getName());
		i++;
	}
}


void PlayerInventoryTile::draw(sf::RenderWindow & window) {
	window.draw(rect);
	window.draw(textPlayerName);
	for (const auto &w : textWaponNames) {
		window.draw(w);
	}
	for (const auto &a : textArmorNames) {
		window.draw(a);
	}

}

void PlayerInventoryTile::draw(VirtualScreen & vScreen) {
	vScreen.drawSurfaceDraw(rect);
	vScreen.drawSurfaceDraw(textPlayerName);
	for (const auto &w : textWaponNames) {
		vScreen.drawSurfaceDraw(w);
	}
	for (const auto &a : textArmorNames) {
		vScreen.drawSurfaceDraw(a);
	}
}

sf::Vector2f PlayerInventoryTile::getSelectboxPosition() {
	return sf::Vector2f{ rect.getPosition().x + 20 + (rect.getSize().x - 110), rect.getPosition().y + 10 + 20 };
}

