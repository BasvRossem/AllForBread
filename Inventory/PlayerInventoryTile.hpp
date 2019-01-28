#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "../Items/Item.hpp"
#include "../virtualScreen/virtualScreen.hpp"
#include "../Character/PlayerCharacter.hpp"
#include "../Items/Weapon.hpp"
#include "../Items/Armor.hpp"

class PlayerInventoryTile{
private:
	sf::RectangleShape rect;
	sf::Font font;
	sf::Text textPlayerName;
	std::vector<sf::Text> textWaponNames;
	std::vector<sf::Text> textArmorNames;
	std::unordered_map<WeaponSlots, Weapon> weapons;
	std::unordered_map<ArmorSlots, Armor> armor;
	std::shared_ptr<PlayerCharacter> character;
public:
	PlayerInventoryTile(std::shared_ptr<PlayerCharacter> character, const sf::Vector2f & position, const sf::Vector2f & size);
	void draw(sf::RenderWindow & window);
	void draw(VirtualScreen & vScreen);
	sf::Vector2f getSelectboxPosition();
};
