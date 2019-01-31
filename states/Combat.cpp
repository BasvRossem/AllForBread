#include "Combat.hpp"


Combat::Combat(sf::RenderWindow & window, Party & party, Mob & monster, std::string surrounding, BackGround & backgrnd):
	State(window),
	party(party),
	monsters(monster),
	animationScreen(animationScreenSize.x , animationScreenSize.y),
	damageScreen(damageScreenSize.x, damageScreenSize.y),
	menuScreen(menuScreenSize.x, menuScreenSize.y),
	backgrnd(backgrnd),
	surrounding(surrounding),
	diaBox(window, 40, 5, "Assets/PIXEARG_.ttf", sf::Vector2i(menuScreenSize.x, menuScreenSize.y), sf::Vector2f(0.0f, static_cast<float>(animationScreenSize.y)), sf::Color::Black),
	afterCombatBox(window, 1000, 5, "Assets/PIXEARG_.ttf", sf::Vector2i(menuScreenSize.x, menuScreenSize.y), sf::Vector2f(0.0f, static_cast<float>(animationScreenSize.y)), sf::Color::Black),
	sound(MusicType::battle, 5.0f)
{
	//dialogue config
	diaBox.setTextPosition(sf::Vector2f{ 20.0f, 20.0f });
	afterCombatBox.setSound("Assets/key.wav");
	//Calculate initiative
	currentCharacter = party[0];
	for (size_t i = 0; i < party.size(); i++){
		initiative.push_back(party[i]);
	}
	for (size_t i = 0; i < monster.size(); i++) {
		initiative.push_back(monster[i]);
	}
	calculateInitiative(initiative);
	allCharacters = initiative;

	//Prepare virtual screens
	sf::Vector2f animationScreenTopLeft(0.0, 0.0);
	sf::Vector2f damageScreenTopLeft(0.0, 0.0);
	sf::Vector2f menuScreenTopLeft(0.0, 680);
	animationScreen.setLocation(animationScreenTopLeft);
	damageScreen.setLocation(damageScreenTopLeft);
	menuScreen.setLocation(menuScreenTopLeft);
	
	//Load a font
	attackFont.loadFromFile("Assets/PIXEARG_.ttf");

	//Initalize turnPointer	 
	if (!turnPointerTexture.loadFromFile("Assets/turnPointer.png")) {
		//Reee
	}
	turnPointer.setTexture(turnPointerTexture);
	turnPointer.setScale(sf::Vector2f(0.1f, 0.1f));
	turnPointer.setPosition(currentCharacter->getSpriteMidpoint().x - 50, currentCharacter->getSpriteMidpoint().y - 250);
}


Combat::~Combat(){
}


void Combat::checkEvents() {
	sf::Event event;
	while (window.pollEvent(event)){
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		if (attackFeedbackFinished && event.type == sf::Event::KeyPressed && isPlayer(currentCharacter)) {
			keyhandle.processKey(event.key.code);
		}
	}
}

State* Combat::update() {
	//Avengers Mode
	bool avengersMode = false;
	bool avengersIsPlaying = false;

	//Load background
	backgrnd.setBackGround(surrounding, sf::Vector2f{ 0,0 }, sf::Vector2f(animationScreenSize));

	//Position players
	for (unsigned int i = 0; i < party.size(); i++) {
		party[i]->setSpriteBottomPosition(sf::Vector2f(static_cast<float>(100 + (i * 200)), static_cast<float>(660)));
	}

	//Calculate Initiative
	calculateInitiative(initiative);
	turnPointer.setPosition(initiative[0]->getSpriteMidpoint().x - 50, initiative[0]->getSpriteMidpoint().y - 250);

	//Place health bars
	for (unsigned int i = 0; i < party.size(); i++) {
		party[i]->update();
		party[i]->centreHealthBar();
	}

	//Play music
	if (!CombatFinished) {
		sound.playSoundEffect(SoundEffect::battleStart);
		sf::sleep(sf::milliseconds(50));
		sound.setMusicLoop(true);
		sound.playMusic();
	}
	else {
		sound.playSoundEffect(SoundEffect::error);
	}

	//Position monsters
	for (unsigned int i = 0; i < monsters.size(); i++) {
		monsters[i]->setSpriteBottomPosition(sf::Vector2f(static_cast<float>(1820 - (i * 200)), static_cast<float>(660)));
	}

	
	//State machine setup
	enum class combatMenu { main, attack, flee };
	combatMenu state = combatMenu::main;
	keyhandle.setOverride(true);

	//Available attacks vector
	std::vector<std::tuple<std::string, WeaponSlots, int>> availableAttacks;

	while(!CombatFinished){
		checkEvents();
		combatChoices.clear();

		if (sound.getMusicVolume() < 90.0f) sound.setMusicVolume(sound.getMusicVolume() + 0.3f);

		if (!attackFeedbackFinished && !CombatFinished) {
			updateAttackFeedback();
		}
		else {
			//-Player Actions
			//===========================================================================================================================================
			if (isPlayer(initiative[currentInitiative])) {
				//state machine
				switch (state) {
					case combatMenu::main:
						combatChoices.push_back("1. Attacks");
						keyhandle.addListener(sf::Keyboard::Num1, [&state]()->void {state = combatMenu::attack; });
						combatChoices.push_back("2. Flee");
						keyhandle.addListener(sf::Keyboard::Num2, [&state]()->void {state = combatMenu::flee; });
						keyhandle.addListener(sf::Keyboard::A, [&avengersMode]()->void {avengersMode = true; });
						break;
					case combatMenu::attack:
						availableAttacks = currentCharacter->getAvailableAttacks();
						for (unsigned int i = 0; i < availableAttacks.size(); i++) {
							keyhandle.addListener(
								sf::Keyboard::Key(sf::Keyboard::Key::Num1 + i), 
								[&state, i, &curChar = currentCharacter, this, &monsters = monsters, &availableAttacks = availableAttacks]() {

								int totalDamageDealt = monsters[0]->processDamage(currentCharacter->generateAttack(availableAttacks[i]));

								if (totalDamageDealt > int(monsters[0]->getHealth() / 4)) {
									sound.playSoundEffect(SoundEffect::strongAttack);
								}
								else {
									sound.playSoundEffect(SoundEffect::weakAttack);
								}

								if (totalDamageDealt > monsters[0]->getHealth()) {
									//sound.playSoundEffect(SoundEffect::monsterDeath);
								}

									makeAttackFeedback(monsters[0], totalDamageDealt);
									checkMonstersDeath();
									state = combatMenu::main; 
									newCurrentCharacter();
								});
							std::stringstream tempstring;
							tempstring << i + 1 << ". " << std::get<0>(availableAttacks[i]);
							combatChoices.push_back(tempstring.str());
						}
						combatChoices.push_back("0. Back");
						keyhandle.addListener(sf::Keyboard::Num0, [&state]()->void {state = combatMenu::main; });
						break;
					case combatMenu::flee:
						CombatFinished = true;

						while (sound.getMusicVolume() > 10.0f) {
							sound.setMusicVolume(sound.getMusicVolume() - 0.4f);
							draw();
							sf::sleep(sf::milliseconds(1));
						}
						sound.stopMusic();

						sound.playSoundEffect(SoundEffect::battleStart);
						break;
					}

			//-Monster Actions
			//===========================================================================================================================================
			} else if(!isPlayer(initiative[currentInitiative])) {
				int randomTargetSelect = (rand() % party.size() + 0);
				while (party[randomTargetSelect]->getHealth() <= 0) {
					randomTargetSelect = (rand() % party.size() + 0);
					std::cout << "Random index: " << randomTargetSelect << "\n";
				}

				int totalDamageDealt = party[randomTargetSelect]->processDamage(currentCharacter->generateAttack({ "Punch", WeaponSlots::mainhand, 1 }));

				if (totalDamageDealt > int(party[randomTargetSelect]->getHealth() / 2)) {
					sound.playSoundEffect(SoundEffect::laugh);
				} else if (totalDamageDealt > int(party[randomTargetSelect]->getHealth() / 4)) {
					sound.playSoundEffect(SoundEffect::strongAttack);
				} else {
					sound.playSoundEffect(SoundEffect::weakAttack);
				}

				if (totalDamageDealt > party[randomTargetSelect]->getHealth()) {
					sound.playSoundEffect(SoundEffect::playerDeath);
				}

				makeAttackFeedback(party[randomTargetSelect], totalDamageDealt);
				checkPlayerDeath();
				newCurrentCharacter();

			//-Error?
			//===========================================================================================================================================
			} else {
				std::cout << "You stupid!\n";
			}
		}

		if (avengersMode && !avengersIsPlaying) {
			sound.playMusicType(MusicType::avengers);
			avengersIsPlaying = true;
		}

		draw();
	}
	return nullptr;
};

void Combat::newCurrentCharacter() {
	unsigned int tempInitiativeIndex = currentInitiative;
	if (tempInitiativeIndex + 1 >= initiative.size()) {
		currentInitiative = 0;
	} else {
		currentInitiative++;
	}
	currentCharacter = initiative[currentInitiative];
	turnPointer.setPosition(currentCharacter->getSpriteMidpoint().x - 50, currentCharacter->getSpriteMidpoint().y - 250);
}

void Combat::draw() {
	window.clear();

	damageScreen.drawSurfaceClear(sf::Color::Transparent);
	animationScreen.drawSurfaceClear(sf::Color::Red);
	menuScreen.drawSurfaceClear(sf::Color::Black);

	backgrnd.draw(animationScreen);

	for (auto character : allCharacters) {
		character->update();
		character->draw(animationScreen);
	}

	if (!attackFeedbackFinished && !CombatFinished) {
		damageScreen.drawSurfaceDraw(*damageText);
	}

	animationScreen.drawSurfaceDisplay();
	menuScreen.drawSurfaceDisplay();
	damageScreen.drawSurfaceDisplay();

	window.draw(menuScreen);
	window.draw(animationScreen);
	window.draw(damageScreen);
	window.draw(turnPointer);

	diaBox.printPerm(combatChoices);
	diaBox.draw();

	window.display();
}

void Combat::stop() {
	CombatFinished = true;
}

void Combat::makeAttackFeedback(const std::shared_ptr<Character> & target, const int & info) {
	sf::String information = std::to_string(info);
	attackFeedbackInitialiser(target, information);
}

void Combat::makeAttackFeedback(const std::shared_ptr<Character> & target, const std::string & info) {
	attackFeedbackInitialiser(target, info);
}

void Combat::updateAttackFeedback() {
	damageMover.update();
	if (damageMover.isFinished()) {
		attackFeedbackFinished = 1;
	}
}

void Combat::attackFeedbackInitialiser(const std::shared_ptr<Character> & target, const sf::String & info) {
	attackFeedbackFinished = 0;
	characterMidpoint = target->getSpriteMidpoint();
	
	damageText = std::shared_ptr < sf::Text>(new sf::Text);
	damageText->setFont(attackFont);
	damageText->setString(info);
	damageText->setCharacterSize(24);
	damageText->setFillColor(sf::Color::White);
	damageText->setOutlineColor(sf::Color::Black);
	damageTextMidPoint = sf::Vector2f(damageText->getLocalBounds().width / 2, damageText->getLocalBounds().height / 2);
	damageText->setOrigin(damageTextMidPoint);
	damageText->setPosition(characterMidpoint);
	
	damageMover = TransformableMovement(damageText, characterMidpoint + sf::Vector2f(0, -200), 1.0);
	damageMover.blend();
}

void Combat::checkMonstersDeath() {
	int deadMonsters = 0;
	for (unsigned int i = 0; i < monsters.size(); i++) {
		if (monsters[i]->getHealth() <= 0) {
			monsters[i]->doDeath();
			removeFromInitiative(monsters[i]);
			deadMonsters++;
		}
	}

	if (deadMonsters == monsters.size()) {
		partyVictory();
	}
}

void Combat::checkPlayerDeath() {
	int deadPlayers = 0;
	for (unsigned int i = 0; i < party.size(); i++) {
		if (party[i]->getHealth() <= 0) {
			party[i]->doDeath();
			removeFromInitiative(party[i]);
			deadPlayers++;
		}
	}
	if (deadPlayers == party.size()) {
		monsterVictory();
	}
}

void Combat::partyVictory() {
	CombatFinished = true;
	combatChoices.clear();
	//=======================================================================================
	//-Calculate total rewards
	//=======================================================================================
	int totalExperienceReward = 0;
	int totalCurrencyReward = 0;

	for (unsigned int i = 0; i < monsters.size(); i++) {
		totalExperienceReward += monsters[i]->getRewardExperience();
		totalCurrencyReward += monsters[i]->getRewardCurrency();

	}

	//=======================================================================================
	// Final frames and cut out music
	//=======================================================================================
	while (sound.getMusicVolume() > 10.0f) {
		sound.setMusicVolume(sound.getMusicVolume() - 0.4f);
		draw();
		sf::sleep(sf::milliseconds(1));
	}

	//=======================================================================================
	// Construct and show rewards screen
	//=======================================================================================
	std::cout << "currency: " << totalCurrencyReward << '\n';
	party.addCurrency(totalCurrencyReward);
	std::vector<std::pair<std::shared_ptr<PlayerCharacter>, bool>> luckyBastards = party.addExperience(totalExperienceReward);

	std::string afterCombatInfo;
	afterCombatInfo += "You received ";
	afterCombatInfo += std::to_string(totalCurrencyReward);
	afterCombatInfo += " crumbs \n";
	afterCombatInfo += "You received ";
	afterCombatInfo += std::to_string(totalExperienceReward);
	afterCombatInfo += " experience points \n";

	for (unsigned int i = 0; i < luckyBastards.size(); i++) {
		if (luckyBastards[i].second) {
			afterCombatInfo += (luckyBastards[i].first->getName() + " recieved double XP! \n");
		}
	}

	afterCombatBox.print(afterCombatInfo);
	sound.stopMusic();

	for (unsigned int i = 0; i < party.size(); i++) {
		if (party[i]->getLevelUp()) {
			AbilitySpeccing a(party[i], window);
			a.use(window);
			party[i]->setIsLevelUp(false);
		}
	}
}

void Combat::monsterVictory() {
	CombatFinished = true;
	sound.playSoundEffect(SoundEffect::laugh);
	while (sound.getMusicVolume() > 5.0f) {
		sound.setMusicVolume(sound.getMusicVolume() - 0.4f);
		draw();
		sf::sleep(sf::milliseconds(1));
	}
	sound.stopMusic();

	// Show "You died" screen
	// Load from last save file

}

void Combat::calculateInitiative(std::vector<std::shared_ptr<Character>> &characterVector) {
	std::sort(
		characterVector.begin(), 
		characterVector.end(),
		[](std::shared_ptr<Character> c1, std::shared_ptr<Character> c2) {
			return (c1->getStat(AbilityScores::dexterity) > c2->getStat(AbilityScores::dexterity));
		}
	);
	currentCharacter = initiative[0];
}

void Combat::removeFromInitiative(const std::shared_ptr<Character> & character) {
	for (unsigned int i = 0; i < initiative.size(); i++) {
		if (initiative[i] == character) {
			initiative.erase(initiative.begin() + i);
			break;
		}
	}
}

bool Combat::isPlayer(const std::shared_ptr<Character> & character) {
	for (unsigned int i = 0; i < party.size(); i++) {
		if (party[i] == character) {
			return true;
		}
	}
	return false;
}