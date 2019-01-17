#pragma once
#include "database/Database.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Character/Party.hpp"
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

