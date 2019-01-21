#pragma once
#include "../database/Database.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../Character/Party.hpp"
#include "../PointsOfIntrest/pointOfInterestContainer.hpp"
#include <map>
class DataManager
{
private:
	//the database object
	Database db;

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

	template<>
	void loading<std::pair< PointOfInterestContainer&, std::map<std::string, std::function<void()>>&>>(std::pair< PointOfInterestContainer&, std::map<std::string, std::function<void()>>&>& box) {
		std::tuple<Database*, PointOfInterestContainer*, std::map<std::string, std::function<void()>>* > passThrough(&db, &box.first, &box.second);
		db.cmd("SELECT x, y, size, Color.r, Color.g, Color.b, Color.a, locationType, functionName, pathId FROM POI, Color WHERE Color.id == colorId ORDER BY POI.id ASC", [](void * pt, int argc, char **argv, char **azColName)->int {
			auto pass = (std::tuple<Database*, PointOfInterestContainer*, std::map<std::string, std::function<void()>>*>*)pt;
			std::vector<sf::Vector2f > path = {};
			std::string q("SELECT x, y FROM PathPoints WHERE pathId == ");
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

	//specialised template of loading for the party
	template<>
	void loading<std::unique_ptr<Party>>(std::unique_ptr<Party>& p) {
		std::vector<std::shared_ptr<PlayerCharacter>> v;
		db.cmd("SELECT Name, ImgPath FROM Player", [](void * vector, int argc, char **argv, char **azColName)->int {
			auto vec = (std::vector<std::shared_ptr<PlayerCharacter>>*)vector;
			auto player = std::make_shared<PlayerCharacter>(argv[0],argv[1]);
			vec->push_back(player);
			return 0;
		}, &v);
		p = std::make_unique<Party>(v);
	}

	//specialised template of loading for the multiple textures
	template<>
	void loading<std::vector<sf::Texture>> (std::vector<sf::Texture>& t) {

	}

	//specialised template of loading for one texture
	template<>
	void loading<sf::Texture>(sf::Texture& t) {

	}

	
public:

	//loads data from the database into the given parameters
	//note: please make sure that there is a specialised version for your type available
	template<typename ... T>
	void load(T& ... t) {
		loading(t...);
	}

	//open the data base with the given parameter
	DataManager(const char *);

	//closes the database
	~DataManager();


};

