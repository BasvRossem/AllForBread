#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "../Items/Item.hpp"
#include "../virtualScreen/virtualScreen.hpp"
#include "../Character/PlayerCharacter.hpp"
#include "../Items/Weapon.hpp"
#include "../Items/Armor.hpp"
#include "InventoryTile.hpp"

class PlayerInventoryTile{
private:
	sf::RectangleShape rect;
	sf::Font font;
	sf::Text textPlayerName;
	std::vector<std::shared_ptr<InventoryTile>> tileWaponNames;
	std::vector<std::shared_ptr<InventoryTile>> tileArmorNames;
	std::unordered_map<WeaponSlots, Weapon> weapons;
	std::unordered_map<ArmorSlots, Armor> armor;
	std::shared_ptr<PlayerCharacter> character;
public:
	PlayerInventoryTile(std::shared_ptr<PlayerCharacter> character, const sf::Vector2f & position, const sf::Vector2f & size);
	void draw(sf::RenderWindow & window);
	void draw(VirtualScreen & vScreen);
	sf::Vector2f getSelectboxPosition();
	void setColor(sf::Color color);
	std::shared_ptr<PlayerCharacter> getCharacter();
	std::unordered_map<WeaponSlots, Weapon> getWeapons();
	std::unordered_map<ArmorSlots, Armor> getArmor();
	std::shared_ptr<Item>  getItem(const int &collom, const int &row);
	std::vector<std::shared_ptr<InventoryTile>> getWeaponTiles();
	std::vector<std::shared_ptr<InventoryTile>> getArmorTiles();

};
