#pragma once
#include "../database/Database.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../Character/Party.hpp"
#include "../PointsOfIntrest/pointOfInterestContainer.hpp"
#include <map>
#include "../Core/background.hpp"
class DataManager
{
private:
	//the database object
	Database db;

	/*================================================
	  _      ____          _____ _____ _   _  _____ 
	 | |    / __ \   /\   |  __ \_   _| \ | |/ ____|
	 | |   | |  | | /  \  | |  | || | |  \| | |  __ 
	 | |   | |  | |/ /\ \ | |  | || | | . ` | | |_ |
	 | |___| |__| / ____ \| |__| || |_| |\  | |__| |
	 |______\____/_/    \_\_____/_____|_| \_|\_____|

	================================================*/
	//base template for unpacking
	template<typename T, typename ... Attributes>
	void loading(T& t, Attributes& ... attributes) {
		loading(t);
		loading(attributes...);
	}

	//base template for loading please specialise
	template<typename T>
	void loading(T& t) {

	}

	//poi loading
	template<>
	void loading<std::pair< PointOfInterestContainer&, std::map<std::string, std::function<void()>>&>>(std::pair< PointOfInterestContainer&, std::map<std::string, std::function<void()>>&>& box) {
		std::tuple<Database*, PointOfInterestContainer*, std::map<std::string, std::function<void()>>* > passThrough(&db, &box.first, &box.second);
		db.cmd("SELECT x, y, size, Color.r, Color.g, Color.b, Color.a, locationType, functionName, pathId FROM POI, Color WHERE Color.id = colorId ORDER BY POI.id ASC", [](void * pt, int argc, char **argv, char **azColName)->int {
			auto pass = (std::tuple<Database*, PointOfInterestContainer*, std::map<std::string, std::function<void()>>*>*)pt;
			std::vector<sf::Vector2f > path = {};
			//second query
			std::string q("SELECT x, y FROM PathPoints WHERE pathId = ");
			q += argv[9];
			q += " ORDER BY id ASC";
			std::get<0>(*pass)->cmd(q.c_str(), [](void * p, int argc, char **argv, char **azColName)->int {
				auto pp = (std::vector<sf::Vector2f >*)p;
				pp->push_back(sf::Vector2f(std::stof(argv[0]), std::stof(argv[1])));
				return 0;
			}, &path);
			std::get<1>(*pass)->add(sf::Vector2f(std::stof(argv[0]), std::stof(argv[1])), std::stof(argv[2]), sf::Color(std::stoi(argv[3]), std::stoi(argv[4]), std::stoi(argv[5]), std::stoi(argv[6])), argv[7], (*std::get<2>(*pass))[argv[8]], path);
			return 0;
		}, &passThrough);
	}

	//party loading
	template<>
	void loading<Party*>(Party*& p) {
		std::vector<std::shared_ptr<PlayerCharacter>> heroVector;
		std::pair<Database&, std::vector<std::shared_ptr<PlayerCharacter>>&> passThrough(db, heroVector);
		db.cmd("SELECT id ,name, texturePath FROM Player", [](void * p, int argc, char **argv, char **azColName)->int {
			auto pass = (std::pair<Database&, std::vector<std::shared_ptr<PlayerCharacter>>&>*)p;
			auto character = std::make_shared<PlayerCharacter>(argv[1], argv[2]);
			//second query
			std::string q("SELECT Attack.name, Attack.damage FROM Player INNER JOIN (Attack INNER JOIN PlayerAttack ON Attack.id = PlayerAttack.attackId) ON Player.id = PlayerAttack.playerId where Player.id = ");
			q += argv[0];
			pass->first.cmd(q.c_str(), [](void * c, int argc, char **argv, char **azColName)->int {
				auto cc = (std::shared_ptr<PlayerCharacter>*)c;
				(*cc)->addCombatAction(std::make_shared<Attack>(argv[0], std::stoi(argv[1]) ) );
				return 0;
			}, &character);
			pass->second.push_back(character);
			return 0;
		}, &passThrough);
		p = new Party(heroVector);
	}

	//background loading
	template<>
	void loading<BackGround>(BackGround & background) {
		db.cmd("SELECT name, texturePath FROM Background", [](void * b, int argc, char **argv, char **azColName)->int {
			auto bb = (BackGround*)b;
			bb->add(argv[0], argv[1]);
			return 0;
		}, &background);
	}

	//specialised template of loading for the multiple textures
	template<>
	void loading<std::vector<sf::Texture>> (std::vector<sf::Texture>& t) {

	}

	//specialised template of loading for one texture
	template<>
	void loading<sf::Texture>(sf::Texture& t) {

	}

	/*================================================
	   _____    __      _______ _   _  _____
	  / ____|  /\ \    / /_   _| \ | |/ ____|
	 | (___   /  \ \  / /  | | |  \| | |  __
	  \___ \ / /\ \ \/ /   | | | . ` | | |_ |
	  ____) / ____ \  /   _| |_| |\  | |__| |
	 |_____/_/    \_\/   |_____|_| \_|\_____|

	================================================*/

	
public:

	//loads data from the database into the given parameters
	//note: please make sure that there is a specialised version for your type available
	template<typename ... T>
	void load(T& ... t) {
		loading(t...);
	}

	template<typename ... T>
	void save(T& ... t) {
		saving(t...);
	}

	//open the data base with the given parameter
	DataManager(const char *);

	//closes the database
	~DataManager();


};

