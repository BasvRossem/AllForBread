#pragma once
#include <unordered_map>
#include <string>
#include "EnumClasses.hpp"
#include "Character.hpp"
#include "../Items/Weapon.hpp"
#include "../Items/Armor.hpp"
#include "ResourceBar.hpp"
#include "../Core/KeyboardHandler.hpp"
#include "../Core/background.hpp"
#include "../Core/dialogBox.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include "PlayerCharacter.hpp"

class AbilitySpeccing{
private:
	std::shared_ptr<PlayerCharacter> playerCharacter;
	sf::Vector2f windowSize;
	VirtualScreen virtualWindow;
	sf::Texture spriteTexture;
	sf::Sprite pointerArrow;
	BackGround background;
	DialogBox textBox;
	std::vector<std::string> stringVector;
	std::stringstream ss;
	KeyboardHandler keyhandle;
	ResourceBar experienceBar;
	int vectorIndex = 0;
	sf::Sound sound;
	sf::SoundBuffer buffer;

	std::vector<std::pair<AbilityScores, sf::Vector2f>> levelUpVector = {
		{AbilityScores::vitality,	sf::Vector2f(250, 284)},
		{AbilityScores::strength,	sf::Vector2f(250, 338)},
		{AbilityScores::dexterity,	sf::Vector2f(250, 394)},
		{AbilityScores::arcanism,	sf::Vector2f(250, 450)},
		{AbilityScores::charisma,	sf::Vector2f(250, 506)},
		{AbilityScores::luck,		sf::Vector2f(250, 564)}
	};

public:
	AbilitySpeccing(std::shared_ptr<PlayerCharacter> playerCharacter, sf::RenderWindow & window);
	~AbilitySpeccing();
	void use(sf::RenderWindow & window);
	void resetAbilits();
	void levelUp();
	void updateStats();
};
