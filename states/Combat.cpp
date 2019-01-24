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
	afterCombatBox(window,80, 5, "Assets/PIXEARG_.ttf", sf::Vector2i(menuScreenSize.x, menuScreenSize.y), sf::Vector2f(0.0f, static_cast<float>(animationScreenSize.y)), sf::Color::Black)
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
}


Combat::~Combat(){
}


void Combat::checkEvents() {
	sf::Event event;
	while (window.pollEvent(event)){
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		if (attackFeedbackFinished && event.type == sf::Event::KeyPressed) {
			keyhandle.processKey(event.key.code);
		}
	}
}

State* Combat::update() {
	//Load background
	backgrnd.setBackGround(surrounding, sf::Vector2f{ 0,0 }, sf::Vector2f(animationScreenSize));

	//Place health bars
	for (unsigned int i = 0; i < party.size(); i++) {
		party[i]->update();
		party[i]->centreHealthBar();
	}
	
	//State machine setup
	enum class combatMenu { main, attack, inventory, flee };
	combatMenu state = combatMenu::main;
	keyhandle.setOverride(true);
	std::array<std::pair<std::string, int>, 4> attackKeys;

	while(!CombatFinished){
		checkEvents();
		combatChoices.clear();
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
						combatChoices.push_back("2. inventory");
						keyhandle.addListener(sf::Keyboard::Num2, [&state]()->void {state = combatMenu::inventory; });
						combatChoices.push_back("3. flee");
						keyhandle.addListener(sf::Keyboard::Num3, [&state]()->void {state = combatMenu::flee; });
						break;
					case combatMenu::attack:
						attackKeys = currentCharacter->getAttacks();
						for (unsigned int i = 0; i < 4; i++) {
							keyhandle.addListener(
								sf::Keyboard::Key(sf::Keyboard::Key::Num1 + i), 
								[&state, i, &curChar = currentCharacter, this]() {
								currentCharacter->activateAttack(this->getMonster(0), i);
									makeAttackFeedback(monsters[0], currentCharacter->getModifier(i));
									checkMonstersDeath();
									state = combatMenu::main; 
									newCurrentCharacter();
								});
							std::stringstream tempstring;
							tempstring << i + 1 << ' ' << attackKeys[i].first;
							combatChoices.push_back(tempstring.str());
						}
						combatChoices.push_back("5. Back");
						keyhandle.addListener(sf::Keyboard::Num5, [&state]()->void {state = combatMenu::main; });
						break;
					case combatMenu::inventory:
						combatChoices.push_back("1. Back");
						keyhandle.addListener(sf::Keyboard::Num1, [&state]()->void {state = combatMenu::main; });
						checkMonstersDeath();
						break;
					case combatMenu::flee:
						CombatFinished = true;
						break;
					}

			//-Monster Actions
			//===========================================================================================================================================
			} else if(!isPlayer(initiative[currentInitiative])) {
				std::cout << "monster made a move that good, you didn't even notice." << std::endl;
				checkPlayerDeath();
				newCurrentCharacter();

			//-Error?
			//===========================================================================================================================================
			} else {
				std::cout << "You stupid!\n";
			}
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
	int totalExperienceReward = 0;
	int totalCurrencyReward = 0;

	for (unsigned int i = 0; i < monsters.size(); i++) {
		totalExperienceReward += monsters[i]->getRewardExperience();
		totalCurrencyReward += monsters[i]->getRewardCurrency();

	}

	draw();
	sf::sleep(sf::seconds(1.50));

	// Show victory screen
	std::string afterCombatInfo;
	afterCombatInfo += "You recieved ";
	afterCombatInfo += std::to_string(totalCurrencyReward);
	afterCombatInfo += " crumbs \n";
	afterCombatInfo += "You recieved ";
	afterCombatInfo += std::to_string(totalExperienceReward);
	afterCombatInfo += " experience points \n";

	afterCombatBox.print(afterCombatInfo);

	party.addCurrency(totalCurrencyReward);
	party.addExperience(totalExperienceReward);

	for (unsigned int i = 0; i < party.size(); i++) {
		if (party[i]->getLevelUp()) {
			party[i]->levelUp(window);
		}
	}
}

void Combat::monsterVictory() {
	CombatFinished = true;

	// Show "You died" screen

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

std::shared_ptr<Monster> Combat::getMonster(unsigned int i) {
	return monsters[i];
}