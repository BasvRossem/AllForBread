#include "Combat.hpp"


Combat::Combat(sf::RenderWindow & window, Party & party, CharacterContainer<std::shared_ptr<Character>> & monster, std::string surrounding, BackGround & backgrnd):
	State(window),
	party(party),
	monsters(monster),
	surrounding(surrounding),
	animationScreen(animationScreenSize.x , animationScreenSize.y),
	damageScreen(damageScreenSize.x, damageScreenSize.y),
	menuScreen(menuScreenSize.x, menuScreenSize.y),
	backgrnd(backgrnd),
	diaBox(window, 40, 5, "Assets/PIXEARG_.ttf", sf::Vector2i(menuScreenSize.x, menuScreenSize.y), sf::Vector2f(0.0f, static_cast<float>(animationScreenSize.y)))
{
	for (size_t i = 0; i < party.size(); i++){
		initiative.push_back(party[i]);
	}
	for (size_t i = 0; i < monster.size(); i++) {
		initiative.push_back(monster[i]);
	}
	calculateInitiative(initiative);
	sf::Vector2f animationScreenTopLeft(0.0, 0.0);
	sf::Vector2f damageScreenTopLeft(0.0, 0.0);
	sf::Vector2f menuScreenTopLeft(0.0, 680);
	animationScreen.setLocation(animationScreenTopLeft);
	damageScreen.setLocation(damageScreenTopLeft);
	menuScreen.setLocation(menuScreenTopLeft);

	attackFont.loadFromFile("Assets/PIXEARG_.ttf");
	//Load the background

}


Combat::~Combat(){
}

void Combat::start() {

};

State* Combat::update() {
	CombatFinished = false;
	backgrnd.setBackGround(surrounding, sf::Vector2f(animationScreenSize));
	

	//state machine setup
	enum combatMenu { main, attack, inventory, flee };
	combatMenu state = main;
	keyhandle.setOverride(true);
	std::array<std::pair<std::string, int>, 4> attackKeys;



	while(!CombatFinished){
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

		//state machine
		switch (state)
		{
		case main:
			combatChoices.push_back("1. Attacks");
			keyhandle.addListener(sf::Keyboard::Num1, [&state]()->void {state = attack; });
			combatChoices.push_back("2. inventory");
			keyhandle.addListener(sf::Keyboard::Num2, [&state]()->void {state = inventory; });
			combatChoices.push_back("3. flee");
			keyhandle.addListener(sf::Keyboard::Num3, [&state]()->void {state = flee; });
			break;
		case attack:
			attackKeys = curChar->getAttacks();
			for (unsigned int i = 0; i < 4; i++) {
				keyhandle.addListener(sf::Keyboard::Key(sf::Keyboard::Key::Num1 + i), [&state, i, &curChar, this]() {curChar->activateAttack(this->getMonster(0), i); attackFeedback(monsters[0], curChar->getModifier(i)); state = main; });
				std::stringstream tempstring;
				tempstring << i+1 << ' ' << attackKeys[i].first;
				combatChoices.push_back(tempstring.str());
			}
			combatChoices.push_back("5. Back");
			keyhandle.addListener(sf::Keyboard::Num5, [&state]()->void {state = main; });
			break;
		case inventory:
			break;
		case flee:
			CombatFinished = true;
			break;
		}

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
		if (!attackFeedbackDone) {
			attackFeedback(monsters[0], 200);
			//attackFeedback(party[0], 250);
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
		
	}
	
	
	return nullptr;
};

void Combat::draw() {
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
	if (!attackFeedbackDone) {
		attackFeedback(monsters[0], 200);
		//attackFeedback(party[0], 250);
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
}

void Combat::Stop() {
	CombatFinished = true;
}

void Combat::attackFeedback(std::shared_ptr<Character> & attacked, int dmg) {
	if (attackFeedbackDone) {
		attackFeedbackDone = 0;
		sf::String damage = std::to_string(dmg);
		damageText = std::shared_ptr < sf::Text>(new sf::Text);

		damageText->setFont(attackFont);
		damageText->setString(damage);
		damageText->setCharacterSize(24);
		damageText->setFillColor(sf::Color::White);
		damageText->setOutlineColor(sf::Color::Black);
		damageTextMidPoint = sf::Vector2f(damageText->getLocalBounds().width / 2, damageText->getLocalBounds().height / 2);
		damageText->setOrigin(damageTextMidPoint);
		characterMidpoint = sf::Vector2f(
			attacked->getDrawable()->getPosition().x + 0,
			attacked->getDrawable()->getPosition().y);
		damageText->setPosition(characterMidpoint);
		std::cout << characterMidpoint.x << ", " << characterMidpoint.y << std::endl;
		std::cout << damageText->getPosition().x << ", " << damageText->getPosition().y << std::endl;
		damageMover = TransformableMovement(damageText, characterMidpoint + sf::Vector2f(0, -200), 1.0);
		damageMover.blend();
		std::cout << "attack feedback made" << std::endl;
	}
	else {
		//std::cout << "floating" << std::endl;
		damageMover.update();
		damageScreen.drawSurfaceDraw(*damageText);
		if (damageMover.isFinished()) {
			attackFeedbackDone = 1;
		}
	}
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

	std::sort(characterVector.begin(), characterVector.end(),
		[](std::shared_ptr<Character> c1, std::shared_ptr<Character> c2) {
		return (c1->getStat(AbilityScores::dexterity) > c2->getStat(AbilityScores::dexterity));
	}
	);

}

std::shared_ptr<Character> Combat::getMonster(unsigned int i) {
	return monsters[i];
}