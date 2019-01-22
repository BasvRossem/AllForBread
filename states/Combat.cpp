#include "Combat.hpp"


Combat::Combat(sf::RenderWindow & window, Party & party, CharacterContainer<std::shared_ptr<Character>> & monster, std::string surrounding, BackGround & backgrnd):
	State(window),
	party(party),
	monsters(monster),
	animationScreen(animationScreenSize.x , animationScreenSize.y),
	damageScreen(damageScreenSize.x, damageScreenSize.y),
	menuScreen(menuScreenSize.x, menuScreenSize.y),
	backgrnd(backgrnd),
	surrounding(surrounding),
	diaBox(window, 40, 5, "Assets/PIXEARG_.ttf", sf::Vector2i(menuScreenSize.x, menuScreenSize.y), sf::Vector2f(0.0f, static_cast<float>(animationScreenSize.y)))
{
	//Calculate initiative
	currentCharacter = party[0];
	for (size_t i = 0; i < party.size(); i++){
		initiative.push_back(party[i]);
	}
	for (size_t i = 0; i < monster.size(); i++) {
		initiative.push_back(monster[i]);
	}
	calculateInitiative(initiative);

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
	backgrnd.setBackGround(surrounding, sf::Vector2f(animationScreenSize));

	/*while(!CombatFinished){
		if (!attackFeedbackFinished) {
			updateAttackFeedback();
		}
		combatChoices.clear();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
				keyhandle.processKey(event.key.code);

		}
		auto curChar = initiative[curInitiative];
		auto actionKeys = curChar->getActions();
		for (size_t i = 0; i < actionKeys.size(); i++){
			keyhandle.addListener(sf::Keyboard::Num0, [i, &curChar, this]() {curChar->activateCombatAction(i, this->getMonster(0)); attackFeedback(monsters[0], curChar->getActions()[i]->getModifier()); });
			std::stringstream tempstring;
			tempstring << i << ' ' << curChar->getActionName(i);
			
			combatChoices.push_back(tempstring.str());
		}
		combatChoices.push_back("4. Stop combat");
		keyhandle.addListener(sf::Keyboard::Num4, [this]()->void {this->CombatFinished = true; });

		window.clear();

		damageScreen.drawSurfaceClear(sf::Color::Transparent);
		animationScreen.drawSurfaceClear(sf::Color::Red);
		menuScreen.drawSurfaceClear(sf::Color::Black);

		backgrnd.draw(animationScreen);
		for (unsigned int i = 0; i < party.size(); i++) {
			party[i]->update();
			party[i]->draw(animationScreen);
		}
		for (unsigned int j = 0; j < monsters.size(); j++) {
			monsters[j]->update();
			monsters[j]->draw(animationScreen);
		}
		
		else {
			//Make combat actions

		}


		checkMonstersDeath();

		animationScreen.drawSurfaceDisplay();
		menuScreen.drawSurfaceDisplay();
		damageScreen.drawSurfaceDisplay();

		window.draw(menuScreen);

		window.draw(animationScreen);

		window.draw(damageScreen);

		diaBox.printPerm(combatChoices);
		diaBox.draw();

		window.display();
		/////
		
	}*/
	
	while (!CombatFinished) {
		checkEvents();
		combatChoices.clear();
		if (!attackFeedbackFinished) {
			updateAttackFeedback();
		}
		else {
			auto curChar = currentCharacter;
			auto actions = currentCharacter->getActions();
			for (size_t i = 0; i < actions.size(); i++) {
				keyhandle.addListener(sf::Keyboard::Num0, [i, &curChar, this]() {
					curChar->activateCombatAction(i, this->getMonster(0));
					makeAttackFeedback(monsters[0], "boop");
				});
				std::stringstream tempstring;
				tempstring << i << ' ' << curChar->getActionName(i);

				combatChoices.push_back(tempstring.str());
			}
		}
		checkMonstersDeath();
		draw();
	}

	return nullptr;
};

void Combat::newCurrentCharacter() {
	currentInitiative++;
	if (currentInitiative >= initiative.size()) {
		currentInitiative = 0;
	}
	currentCharacter = initiative[currentInitiative];
}

void Combat::draw() {
	window.clear();

	damageScreen.drawSurfaceClear(sf::Color::Transparent);
	animationScreen.drawSurfaceClear(sf::Color::Red);
	menuScreen.drawSurfaceClear(sf::Color::Black);

	backgrnd.draw(animationScreen);

	for (auto character : initiative) {
		character->update();
		character->draw(animationScreen);
	}

	if (!attackFeedbackFinished) {
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

//-Added (Niels)
void Combat::checkMonstersDeath() {
	for (unsigned int i = 0; i < monsters.size(); i++) {
		if (monsters[i]->getHealth() <= 0) {
			monsters[i]->doDeath();
		}
	}
}

//-Added (Niels)
//-Not yet finished, requires monster templated container for 
// getRewardsExperience/getRewardsCurrency to be functional
void Combat::partyVictory() {
	int totalExperienceReward, totalCurrencyReward;

	for (unsigned int i = 0; i < monsters.size(); i++) {
		//totalRewardExperience += monsters[i]->getRewardExperience();
		//totalRewardExperience += monsters[i]->getRewardsCurrency();

	}

	party.addExperience(totalExperienceReward);
	party.addCurrency(totalCurrencyReward);
}

//-Added (Niels)
//Not yet finished
void Combat::monsterVictory() {

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

std::shared_ptr<Character> Combat::getMonster(unsigned int i) {
	return monsters[i];
}