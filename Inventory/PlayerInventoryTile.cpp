#include "playerInventoryTile.hpp"
#include "../Character/EnumClasses.hpp"


PlayerInventoryTile::PlayerInventoryTile(std::shared_ptr<PlayerCharacter> character, const sf::Vector2f & position, const sf::Vector2f & size) :
	character(character)
{
	weapons = character->getWeaponMap();
	armor = character->getArmorMap();

	float outLine = 2;
	float spaceBetweenTiles = 5;

	rect.setPosition(sf::Vector2f{ position.x + outLine + spaceBetweenTiles, position.y + outLine + spaceBetweenTiles });
	rect.setSize(sf::Vector2f{ size.x - 2 * (outLine + spaceBetweenTiles), size.y - 2 * (outLine + spaceBetweenTiles) });
	rect.setFillColor(sf::Color(124, 79, 33));
	rect.setOutlineThickness(outLine);
	rect.setOutlineColor(sf::Color(102, 51, 0));

	font.loadFromFile("Assets/arial.ttf");
	textPlayerName.setFont(font);
	textPlayerName.setPosition(sf::Vector2f{ position.x + 10, position.y + size.y / 7 * 1 });
	textPlayerName.setCharacterSize(int(size.y / 7));
	textPlayerName.setFillColor(sf::Color::White);
	textPlayerName.setString(character->getName());
	textPlayerName.setOutlineThickness(1);
	textPlayerName.setOutlineColor(sf::Color::Black);

	int i = 0;
	for (auto & w : weapons) {
		tileWaponNames.push_back(
			std::make_shared<InventoryTile>(std::make_shared<Weapon>(w.second),
				sf::Vector2f(sf::Vector2f{ position.x + 10, position.y + size.y / 3 * i + 100 }),
				sf::Vector2f(450.0f, float(size.y / 4))));
		i++;
	}
	i = 0;
	for (auto & a : armor) {
		tileArmorNames.push_back(
			std::make_shared<InventoryTile>(std::make_shared<Armor>(a.second),
				sf::Vector2f(sf::Vector2f{ position.x + 465, position.y + size.y / 6 * i }),
				sf::Vector2f(350.0f, float(size.y / 6))));
		i++;
	}
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

void PlayerInventoryTile::setBorderColor(sf::Color color) {
	rect.setOutlineColor(color);
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
	return std::shared_ptr<Item>(nullptr);
}

std::vector<std::shared_ptr<InventoryTile>> PlayerInventoryTile::getWeaponTiles() {
	return tileWaponNames;
}
std::vector<std::shared_ptr<InventoryTile>> PlayerInventoryTile::getArmorTiles() {
	return tileArmorNames;
}