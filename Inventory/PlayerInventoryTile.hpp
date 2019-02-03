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

	/// \brief
	/// This function draws a Tile on a window
	void draw(sf::RenderWindow & window);

	/// \brief
	/// This function draws a Tile on a VirtualScreen
	void draw(VirtualScreen & vScreen);
	/// \brief
	/// This function gets the postion of a normal size Tile for the selectbox.
	sf::Vector2f getSelectboxPosition();

	/// \brief
	/// With this function you can set the color of a tile.
	void setColor(sf::Color color);

	/// \brief
	/// With this function you can set the outline color.
	void setBorderColor(sf::Color color);

	/// \brief
	/// With this function you can get the shared_ptr from the character inside the Tile
	std::shared_ptr<PlayerCharacter> getCharacter();

	/// \brief
	/// With this function you can get the unorder_map Weapon from the character inside the Tile
	std::unordered_map<WeaponSlots, Weapon> getWeapons();

	/// \brief
	/// With this function you can get the unorder_map Armor from the character inside the Tile
	std::unordered_map<ArmorSlots, Armor> getArmor();

	/// \brief
	/// With this function you can get the item from the character inside the Tile
	/// It requers collom index for Weapon or Armor and a row index of the vector  
	std::shared_ptr<Item>  getItem(const int &collom, const int &row);

	/// \brief
	/// With this function you can get the weaponTiles
	std::vector<std::shared_ptr<InventoryTile>> getWeaponTiles();

	/// \brief
	///  With this function you can get the armorTiles 
	std::vector<std::shared_ptr<InventoryTile>> getArmorTiles();
};
