#include "playerInventoryTile.hpp"
#include "../Character/EnumClasses.hpp"


PlayerInventoryTile::PlayerInventoryTile(std::shared_ptr<PlayerCharacter> character, const sf::Vector2f & position, const sf::Vector2f & size) :
	character(character)
{
	weapons = character->getWeaponMap();
	armor = character->getArmorMap();

	float outLine = 2;
	float spaceBetweenTiles = 5; 

	rect.setPosition(sf::Vector2f{ position.x + outLine + spaceBetweenTiles, position.y + outLine + spaceBetweenTiles});
	rect.setSize(sf::Vector2f{ size.x - 2* (outLine +spaceBetweenTiles), size.y - 2* (outLine +spaceBetweenTiles)});
	rect.setFillColor(sf::Color::Black);
	rect.setOutlineThickness(outLine);
	rect.setOutlineColor(sf::Color::White);

	font.loadFromFile("Assets/PIXEARG_.ttf");
	textPlayerName.setFont(font);
	textPlayerName.setPosition(sf::Vector2f{ position.x + 10, position.y + size.y / 7 * 1 });
	textPlayerName.setCharacterSize(int(size.y / 7));
	textPlayerName.setStyle(sf::Text::Bold);
	textPlayerName.setFillColor(sf::Color::White);
	textPlayerName.setString(character->getName());

	int i = 0;
	for (auto & w : weapons) {
		tileWaponNames.push_back(
			std::make_shared<InventoryTile>(std::make_shared<Weapon>(w.second),
				sf::Vector2f(sf::Vector2f{ position.x + 10, position.y + size.y / 3 * i + 100}),
				sf::Vector2f(350.0f ,float(size.y / 4))));
		i++;
	}
	i = 0;
	for (auto & a : armor) {
		tileArmorNames.push_back(
			std::make_shared<InventoryTile>(std::make_shared<Armor>(a.second),
				sf::Vector2f(sf::Vector2f{ position.x + 400, position.y + size.y / 6 * i  }),
				sf::Vector2f(350.0f, float(size.y / 6))));
		i++;
	}



	/*int i = 0;
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
	}*/
}


void PlayerInventoryTile::draw(sf::RenderWindow & window) {
	window.draw(rect);
	window.draw(textPlayerName);
	for (const auto &w : tileWaponNames) {
		w->draw(window);
	}
	for (const auto &a : tileArmorNames) {
		a->draw(window);
	}

}

void PlayerInventoryTile::draw(VirtualScreen & vScreen) {
	vScreen.drawSurfaceDraw(rect);
	vScreen.drawSurfaceDraw(textPlayerName);
	for (const auto &w : tileWaponNames) {
		w->draw(vScreen);
	}
	for (const auto &a : tileArmorNames) {
		a->draw(vScreen);
	}
}

sf::Vector2f PlayerInventoryTile::getSelectboxPosition() {
	return sf::Vector2f{ rect.getPosition().x + 20 + (rect.getSize().x - 110), rect.getPosition().y + 10 + 20 };
}

void PlayerInventoryTile::setColor(sf::Color color) {
	rect.setFillColor(color);
}

std::shared_ptr<PlayerCharacter> PlayerInventoryTile::getCharacter() {
	return character;
}

std::unordered_map<WeaponSlots, Weapon> PlayerInventoryTile::getWeapons() {
	return weapons;
}
std::unordered_map<ArmorSlots, Armor> PlayerInventoryTile::getArmor() {
	return armor;
}

std::shared_ptr<Item> PlayerInventoryTile::getItem(const int &collom, const int &row) {
	if (collom == 0) {
		return tileWaponNames[row]->getItem();
	}
	else if (collom == 1) {
		return tileArmorNames[row]->getItem();
	}
}

std::vector<std::shared_ptr<InventoryTile>> PlayerInventoryTile::getWeaponTiles() {
	return tileWaponNames;
}
std::vector<std::shared_ptr<InventoryTile>> PlayerInventoryTile::getArmorTiles() {
	return tileArmorNames;
}