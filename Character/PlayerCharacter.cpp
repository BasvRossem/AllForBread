#include "PlayerCharacter.hpp"

PlayerCharacter::PlayerCharacter(const std::string & characterName, const std::string & textureName, const int & exp) :
	Character(characterName, textureName),
	experience(exp) {
};

PlayerCharacter::PlayerCharacter(const std::string & characterName, const std::string & textureName, const int & frameAmount, const int & exp) :
	Character(characterName, textureName, frameAmount),
	experience(exp) {
};

void PlayerCharacter::increaseExperience(const int & exp) {
	//-Safeguard from negative xpReward Values
	if (exp <= 0) {
		return;
	}

	if (experience + exp >= experienceGauge) {
		int excessExperience = (experience + exp) - experienceGauge;
		experience = 0;
		level++;
		isLevelUp = true;
		abilityPoints++;
		float newExperienceGauge = experienceGauge * float(1.2);
		experienceGauge = static_cast<int>(newExperienceGauge);
		increaseExperience(excessExperience);

	} else {
		experience += exp;
		return;
	}
}


int PlayerCharacter::calculateTotalExperience() {
	int totalExperience = 0;
	int experiencePerLevel = 100;

	for (int i = 1; i < level; i++) {
		totalExperience += experiencePerLevel;
		float newExperiencePerLevel = experiencePerLevel * float(1.2);
		experiencePerLevel = static_cast<int>(newExperiencePerLevel);
	}

	totalExperience += experience;

	return totalExperience;
}

bool PlayerCharacter::getLevelUp() {
	return isLevelUp;
}

int PlayerCharacter::requiredExperience() {
	return experienceGauge - experience;
}

void PlayerCharacter::printTotalExperience() {
	std::cout << "Total experience aquired: " << calculateTotalExperience() << "\n";
}

void PlayerCharacter::printExperience() {
	std::cout << "Current Experience:	" << experience << "\n";
	std::cout << "Experience Gauge:	" << experienceGauge << "\n";
	std::cout << "Player Level:		" << level << "\n";
	std::cout << "\n";
}

Armor PlayerCharacter::getArmor(const ArmorSlots & slot) {
	return armor.at(slot);
}

Weapon PlayerCharacter::getWeapon(const WeaponSlots & slot) {
	return weapons.at(slot);
}

void PlayerCharacter::setArmor(const ArmorSlots & slot, const Armor & newArmor) {
	armor[slot] = newArmor;
}

void PlayerCharacter::setWeapon(const WeaponSlots & slot, const Weapon & newWeapon) {
	switch (slot) {
	case WeaponSlots::twohanded:
		if (weapons.find(WeaponSlots::mainhand) != weapons.end()) {
			weapons.erase(WeaponSlots::mainhand);
		}
		if (weapons.find(WeaponSlots::offhand) != weapons.end()) {
			weapons.erase(WeaponSlots::offhand);
		}
		break;

	case WeaponSlots::offhand:
	case WeaponSlots::mainhand:
		if (weapons.find(slot) != weapons.end()) {
			weapons.erase(WeaponSlots::twohanded);
		}
		break;
	}
	weapons[slot] = newWeapon;
}


std::unordered_map<WeaponSlots, Weapon> PlayerCharacter::getWeaponMap(){
	return weapons;
}

std::unordered_map<ArmorSlots, Armor> PlayerCharacter::getArmorMap(){
	return armor;
}

void PlayerCharacter::clearEquipment() {
	weapons.clear();
	armor.clear();
}

void PlayerCharacter::levelUp(sf::RenderWindow & window) {
	//-Screen & Drawable variables
	//================================================================================================================================
	sf::Vector2f windowSize = sf::Vector2f(400, 900);
	VirtualScreen virtualWindow(unsigned int(windowSize.x), unsigned int(windowSize.y));

	sf::Texture spriteTexture;
	spriteTexture.loadFromFile("Assets/PointerArrow.png");
	sf::Sprite pointerArrow;
	pointerArrow.setTexture(spriteTexture);
	
	BackGround background;
	background.add("levelParchment", "Assets/levelUpParchment.png");
	background.setBackGround("levelParchment", sf::Vector2f{ 0,0 }, windowSize);

	DialogBox textBox(window, 100, 10, "Assets/arial.ttf", sf::Vector2i(400, 750), sf::Vector2f(0, 150), sf::Color::Transparent);

	textBox.setTextFillColor(sf::Color::Black);
	textBox.setTextOutlineColor(sf::Color::White);
	textBox.setTextPosition(sf::Vector2f{ 20.0f,20.0f });
	textBox.setTextLineSpacing(2.0f);

	std::vector<std::string> stringVector = {name};
	std::stringstream ss;
	ss << "Ability points: " << abilityPoints;
	stringVector.push_back(ss.str());
	ss.str(std::string());

	ss << "Vitality:	" << characterStats[AbilityScores::vitality];
	stringVector.push_back(ss.str());
	ss.str(std::string());

	ss << "Strength:	" << characterStats[AbilityScores::strength];
	stringVector.push_back(ss.str());
	ss.str(std::string());

	ss << "Dexterity:	" << characterStats[AbilityScores::dexterity];
	stringVector.push_back(ss.str());
	ss.str(std::string());

	ss << "Arcanism:	" << characterStats[AbilityScores::arcanism];
	stringVector.push_back(ss.str());
	ss.str(std::string());

	ss << "Charisma:	" << characterStats[AbilityScores::charisma];
	stringVector.push_back(ss.str());
	ss.str(std::string());

	ss << "Luck:		" << characterStats[AbilityScores::luck];
	stringVector.push_back(ss.str());
	ss.str(std::string());
	textBox.printPerm(stringVector);

	//-Functional variables
	//================================================================================================================================
	KeyboardHandler keyhandle;
	ResourceBar experienceBar = ResourceBar(sf::Vector2f(50, 800),sf::Vector2f(150, 30), experienceGauge, experience, sf::Color::Green);

	int vectorIndex = 0;
	std::vector<std::pair<AbilityScores, sf::Vector2f>> levelUpVector = { 
		{AbilityScores::vitality,	sf::Vector2f(250, 300)},
		{AbilityScores::strength,	sf::Vector2f(250, 350)},
		{AbilityScores::dexterity,	sf::Vector2f(250, 400)},
		{AbilityScores::arcanism,	sf::Vector2f(250, 450)},
		{AbilityScores::charisma,	sf::Vector2f(250, 500)},
		{AbilityScores::luck,		sf::Vector2f(250, 550)}
	};

	pointerArrow.setPosition(levelUpVector[0].second);

	//-Sound variables
	//================================================================================================================================
	sf::SoundBuffer buffer;
	buffer.loadFromFile("SoundEffects/ScrollOpen1.wav");
	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();

	//-Keyhandler
	//================================================================================================================================
	keyhandle.addListener(sf::Keyboard::Up, [&vectorIndex, &levelUpVector, &pointerArrow]()->void {
		vectorIndex--;
		if (vectorIndex < 0) vectorIndex = levelUpVector.size() - 1;
		pointerArrow.setPosition(levelUpVector[vectorIndex].second);
	});

	keyhandle.addListener(sf::Keyboard::Down, [&vectorIndex, &levelUpVector, &pointerArrow]()->void {
		vectorIndex++;
		if (vectorIndex > static_cast<int>(levelUpVector.size() - 1)) vectorIndex = 0;
		pointerArrow.setPosition(levelUpVector[vectorIndex].second);
	});

	keyhandle.addListener(sf::Keyboard::Enter, [&window, &vectorIndex, &levelUpVector, &characterStats = characterStats, &abilityPoints = abilityPoints, &name = name, &textBox, &sound, &buffer]()->void {
		if (characterStats[levelUpVector[vectorIndex].first] < 99 && abilityPoints > 0) {
			characterStats[levelUpVector[vectorIndex].first]++;
			abilityPoints--;

			std::vector<std::string> stringVector = { name };
			std::stringstream ss;
			ss << "Ability points: " << abilityPoints;
			stringVector.push_back(ss.str());
			ss.str(std::string());

			ss << "Vitality:	" << characterStats[AbilityScores::vitality];
			stringVector.push_back(ss.str());
			ss.str(std::string());

			ss << "Strength:	" << characterStats[AbilityScores::strength];
			stringVector.push_back(ss.str());
			ss.str(std::string());

			ss << "Dexterity:	" << characterStats[AbilityScores::dexterity];
			stringVector.push_back(ss.str());
			ss.str(std::string());

			ss << "Arcanism:	" << characterStats[AbilityScores::arcanism];
			stringVector.push_back(ss.str());
			ss.str(std::string());

			ss << "Charisma:	" << characterStats[AbilityScores::charisma];
			stringVector.push_back(ss.str());
			ss.str(std::string());

			ss << "Luck:		" << characterStats[AbilityScores::luck];
			std::cout << "Luck:		" << characterStats[AbilityScores::luck] << "\n";
			stringVector.push_back(ss.str());
			ss.str(std::string());

			buffer.loadFromFile("SoundEffects/LevelUp.wav");
			sound.setBuffer(buffer);
			sound.setVolume(30.0f);
			sound.play();
			sf::sleep(sf::seconds(0.7f));
			textBox.printPerm(stringVector);
		}
		else {
			buffer.loadFromFile("SoundEffects/LevelError.wav");
			sound.setBuffer(buffer);
			sound.play();
			sf::sleep(sf::seconds(0.7f));
		}
	});

	//-Levelup loop
	//================================================================================================================================
	while (abilityPoints > 0) {
		window.clear();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
				keyhandle.processKey(event.key.code);

		}

		virtualWindow.drawSurfaceClear();
		background.draw(virtualWindow);
		virtualWindow.drawSurfaceDraw(pointerArrow);
		virtualWindow.drawSurfaceDisplay();
		experienceBar.draw(virtualWindow);
		window.draw(virtualWindow);
		textBox.draw();
		window.display();
	}
	sf::sleep(sf::seconds(0.5f));

	buffer.loadFromFile("SoundEffects/ScrollClose1.wav");
	sound.setBuffer(buffer);
	sound.play();
	isLevelUp = false;
}

