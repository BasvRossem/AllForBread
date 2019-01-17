#include "Combat.hpp"


Combat::Combat(sf::RenderWindow & window, Party & party, CharacterContainer<std::shared_ptr<Character>> & monster, std::string surrounding):
	State(window),
	party(party),
	monsters(monster),
	surroundings(surrounding),
	animationScreen(animationScreenSize.x , animationScreenSize.y),
	damageScreen(damageScreenSize.x, damageScreenSize.y),
	menuScreen(menuScreenSize.x, menuScreenSize.y)
{
	sf::Vector2f animationScreenTopLeft(0.0, 0.0);
	sf::Vector2f damageScreenTopLeft(0.0, 0.0);
	sf::Vector2f menuScreenTopLeft(0.0, 680);
	animationScreen.setLocation(animationScreenTopLeft);
	damageScreen.setLocation(damageScreenTopLeft);
	menuScreen.setLocation(menuScreenTopLeft);

	attackFont.loadFromFile("PIXEARG_.ttf");
	//Load the background
	std::string backgr = ""; 
	backgr += surroundings;
	if (!backgroundTexture.loadFromFile(surroundings, sf::IntRect(0, 0, 1920, 1080))){
		std::cout << "Can't load background image: " << backgr << std::endl;
		if (!backgroundTexture.loadFromFile("error.JPG", sf::IntRect(0, 0, 1920, 1080))) {
			std::cout << "Can't load background image: " << backgr << std::endl;
		}
	}
	backgroundSprite.setTexture(backgroundTexture);
	sf::Vector2u backSize = backgroundTexture.getSize();
	float xScale = static_cast<float>(1920.0 / backSize.x);
	float yScale = static_cast<float>(680.0 / backSize.y);
	backgroundSprite.scale(sf::Vector2f(xScale, yScale));
}


Combat::~Combat(){
}

void Combat::start() {

};

State* Combat::update() {
	attackFeedback(monsters[0], 200);
	monsters[0]->decreaseHealth(20);
	for(;;){
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		draw();
		
	}
	
	
	return nullptr;
};

void Combat::draw() {
	window.clear();

	damageScreen.drawSurfaceClear(sf::Color::Transparent);
	animationScreen.drawSurfaceClear(sf::Color::Red);
	menuScreen.drawSurfaceClear(sf::Color::Blue);

	animationScreen.drawSurfaceDraw(backgroundSprite);
	for (int i = 0; i < party.size(); i++) {
		party[i]->update();
		party[i]->draw(animationScreen);
	}
	for (int j = 0; j < monsters.size(); j++) {
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
	window.draw(backgroundSprite);

	window.draw(animationScreen);

	window.draw(damageScreen);
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