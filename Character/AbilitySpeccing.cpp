#include "AbilitySpeccing.hpp"



AbilitySpeccing::AbilitySpeccing(std::shared_ptr<PlayerCharacter> playerCharacter, sf::RenderWindow & window):
	playerCharacter(playerCharacter),
	textBox(window, 100, 10, "Assets/arial.ttf", sf::Vector2i(400, 750), sf::Vector2f(0, 150), sf::Color::Transparent),
	windowSize(400, 900),
	virtualWindow(unsigned int(windowSize.x), unsigned int(windowSize.y))
{
	spriteTexture.loadFromFile("Assets/PointerArrow.png");
	pointerArrow.setTexture(spriteTexture);

	background.add("levelParchment", "Assets/levelUpParchment.png");
	background.setBackGround("levelParchment", sf::Vector2f{ 0,0 }, windowSize);

	textBox.setTextFillColor(sf::Color::Black);
	textBox.setTextOutlineColor(sf::Color::White);
	textBox.setTextPosition(sf::Vector2f{ 20.0f,20.0f });
	textBox.setTextLineSpacing(2.0f);

	updateStats();
}


AbilitySpeccing::~AbilitySpeccing()
{
}

void AbilitySpeccing::resetAbilits() {
	int count = 0;
	std::unordered_map<AbilityScores, int> characterStats(playerCharacter->getCharacterStats());
	for (auto & s : characterStats) {
		count += (s.second -10) ;
		s.second = 10;
	}
	playerCharacter->setAbilityPoints(count);
	playerCharacter->setCharacterStats(characterStats);
	updateStats();
}

void AbilitySpeccing::use(sf::RenderWindow & window) {

	experienceBar = ResourceBar(sf::Vector2f(50, 800), sf::Vector2f(150, 30), playerCharacter->getExperienceGauge(), playerCharacter->getExperience(), sf::Color::Green);

	vectorIndex = 0;

	pointerArrow.setPosition(levelUpVector[0].second);

	buffer.loadFromFile("SoundEffects/ScrollOpen1.wav");
	sound.setBuffer(buffer);
	sound.play();

	keyhandle.addListener(sf::Keyboard::W, [&]()->void {
		vectorIndex--;
		if (vectorIndex < 0) vectorIndex = levelUpVector.size() - 1;
		pointerArrow.setPosition(levelUpVector[vectorIndex].second);
	});

	keyhandle.addListener(sf::Keyboard::S, [&]()->void {
		vectorIndex++;
		if (vectorIndex > static_cast<int>(levelUpVector.size() - 1)) vectorIndex = 0;
		pointerArrow.setPosition(levelUpVector[vectorIndex].second);
	});

	keyhandle.addListener(sf::Keyboard::Enter, [&]()->void {levelUp(); });

	while (playerCharacter->getAbilityPoints() > 0) {
		window.clear();
		textBox.clear();
		virtualWindow.drawSurfaceClear();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
				keyhandle.processKey(event.key.code);

		}
		
		background.draw(virtualWindow);
		virtualWindow.drawSurfaceDraw(pointerArrow);
		virtualWindow.drawSurfaceDisplay();
		experienceBar.draw(virtualWindow);
		
		window.draw(virtualWindow);
		textBox.draw();
		window.display();
	}

	playerCharacter->reCalculateHealth();
	sf::sleep(sf::seconds(0.5f));
	buffer.loadFromFile("SoundEffects/ScrollClose1.wav");
	sound.setBuffer(buffer);
	sound.play();

}


void AbilitySpeccing::levelUp() {

	if (playerCharacter->getCharacterStats()[levelUpVector[vectorIndex].first] < 99 && playerCharacter->getAbilityPoints() > 0) {

		auto tmp = playerCharacter->getCharacterStats();
		tmp[levelUpVector[vectorIndex].first]++;

		playerCharacter->setCharacterStats(tmp);

		playerCharacter->setAbilityPoints(playerCharacter->getAbilityPoints()-1);
		updateStats();


		buffer.loadFromFile("SoundEffects/LevelUp.wav");
		sound.setBuffer(buffer);
		sound.setVolume(30.0f);
		sound.play();
		sf::sleep(sf::seconds(0.7f));
	}
	else {
		buffer.loadFromFile("SoundEffects/LevelError.wav");
		sound.setBuffer(buffer);
		sound.play();
		sf::sleep(sf::seconds(0.7f));
	}
}

void AbilitySpeccing::updateStats() {
	std::unordered_map<AbilityScores, int> characterStats(playerCharacter->getCharacterStats());

	std::vector<std::string> stringVector = { playerCharacter->getName() };
	std::stringstream ss;
	ss << "Ability points: " << playerCharacter->getAbilityPoints();
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
}