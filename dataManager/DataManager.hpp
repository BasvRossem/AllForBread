#pragma once
#include "../database/Database.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../Character/Party.hpp"
#include "../Character/EnumClasses.hpp"
#include "../PointsOfInterest/pointOfInterestContainer.hpp"
#include <map>
#include "../Core/background.hpp"
#include "../Items/Item.hpp"
#include "../Items/Consumable.hpp"
#include "../Items/Armor.hpp"
#include "../Items/Weapon.hpp"
class DataManager
{
private:
	//the database object
	Database db;

	std::map<std::string, std::function<void()>>& functions;

	std::map<std::string, AbilityScores> abilityScores;
	std::map<AbilityScores, int> abilityScoresId;
	std::map<std::string, DamageTypes> damageTypes;
	std::map<std::string, ArmorSlots> armorSlots;
	std::map<std::string, WeaponSlots> weaponSlots;

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
		std::cerr << "uknown type: " << typeid(t).name() << std::endl;
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
		db.cmd("SELECT id, name, texturePath, individualFrame, portrait, death FROM Player", [](void * p, int argc, char **argv, char **azColName)->int {
			auto pass = (std::pair<Database&, std::vector<std::shared_ptr<PlayerCharacter>>&>*)p;
			std::pair<std::string, std::string> texturePair(argv[2], argv[3]);
			auto character = std::make_shared<PlayerCharacter>(argv[1], texturePair);
			character->setPortraitFilename(argv[4]);
			character->setDeathAnimation(argv[5]);
			pass->second.push_back(character);
			return 0;
		}, &passThrough);
		p = new Party(heroVector);
		loading(*p);
	}

	//background loading !needs to become std::map!
	template<>
	void loading<BackGround>(BackGround & background) {
		db.cmd("SELECT name, texturePath FROM Background", [](void * b, int argc, char **argv, char **azColName)->int {
			auto bb = (BackGround*)b;
			bb->add(argv[0], argv[1]);
			return 0;
		}, &background);
	}

	//weapons loading
	template<>
	void loading< std::map<std::string, Weapon>>(std::map<std::string, Weapon>& weaponMap) {
		std::tuple<std::map<std::string, Weapon>&, std::map<std::string, WeaponSlots>&, std::map<std::string, DamageTypes>&, Database&> combinedMap(weaponMap, weaponSlots, damageTypes, db);

		db.cmd("SELECT Item.name, Item.description, Item.weight, Item.baseValue, WeaponSlot.name, DamageType.name, Weapon.primDamage, Weapon.id FROM Item INNER JOIN(DamageType INNER JOIN(WeaponSlot INNER JOIN Weapon ON WeaponSlot.[id] = Weapon.[weaponSlotId]) ON DamageType.[id] = Weapon.[primDamageTypeId]) ON Item.[id] = Weapon.[itemId];", [](void * map, int argc, char **argv, char **azColName)->int {
			auto m = (std::tuple<std::map<std::string, Weapon>&, std::map<std::string, WeaponSlots>&, std::map<std::string, DamageTypes>&, Database&>*)map;
			Weapon weapon(std::get<1>(*m)[argv[4]], std::pair<DamageTypes, int>(std::get<2>(*m)[argv[5]], std::stoi(argv[6])));
			weapon.setName(argv[0]);
			weapon.setDescription(argv[1]);
			weapon.setWeight(std::stoi(argv[2]));
			weapon.setBaseValue(std::stoi(argv[3]));
			std::pair<Weapon&, std::map<std::string, DamageTypes>&> wAm(weapon, std::get<2>(*m));
			std::string q = "SELECT DamageType.name, WeaponSecDamageType.damage FROM DamageType INNER JOIN WeaponSecDamageType ON DamageType.[id] = WeaponSecDamageType.[damageTypeId] WHERE WeaponSecDamageType.weaponId = ";
			q += argv[7];
			std::get<3>(*m).cmd(q.c_str(), [](void * w, int argc, char **argv, char **azColName)->int {
				auto ww = (std::pair<Weapon&, std::map<std::string, DamageTypes>&>*)w;
				ww->first.addSecondaryDamageEffect(std::pair<DamageTypes, int>(ww->second[argv[0]], std::stoi(argv[1])));
				return 0;
			}, &wAm);
			std::get<0>(*m)[argv[0]] = weapon;
			return 0;
		},&combinedMap);
	}

	//item loading
	template<>
	void loading < std::map<std::string, Item>>(std::map<std::string, Item>& itemMap) {
		db.cmd("SELECT name, description, weight, baseValue FROM Item", [](void * someP, int argc, char **argv, char **azColName)->int {
			auto p = (std::map<std::string, Item>*)someP;
			
			Item item;
			item.setName(argv[0]);
			item.setDescription(argv[1]);
			item.setWeight(std::stoi(argv[2]));
			item.setBaseValue(std::stoi(argv[3]));
		
			(*p)[argv[0]] = item;
			return 0;
		}, &itemMap);
	}

	//armor loading
	template<>
	void loading<std::map<std::string, Armor>>(std::map<std::string, Armor>& armorMap) {
		std::tuple< std::map<std::string, Armor>&, std::map<std::string, ArmorSlots>&, std::map<std::string, AbilityScores>&, Database&> combo(armorMap, armorSlots, abilityScores, db);
		db.cmd("SELECT [Item].[name], [Item].[description], [Item].[weight], [Item].[baseValue], [ArmorSlot].[name], [Armor].[physicalProtection], [Armor].[magicalProtecton], [Armor].[id] FROM (ArmorSlot INNER JOIN Armor ON [ArmorSlot].[id] =[Armor].[armorSlotId]) INNER JOIN Item ON [Armor].[itemId] = [Item].[id];", [](void * someP, int argc, char **argv, char **azColName)->int {
			auto p = (std::tuple< std::map<std::string, Armor>&, std::map<std::string, ArmorSlots>&, std::map<std::string, AbilityScores>&, Database&>*)someP;
			Armor armor;
			armor.setName(argv[0]);
			armor.setDescription(argv[1]);
			armor.setWeight(std::stoi(argv[2]));
			armor.setBaseValue(std::stoi(argv[3]));
			armor.setArmorSlot(std::get<1>(*p)[argv[4]]);
			armor.setPhysicalProtection(std::stoi(argv[5]));
			armor.setMagicalProtection(std::stoi(argv[6]));

			std::pair< Armor&, std::map<std::string, AbilityScores>&> AaM(armor, std::get<2>(*p));
			std::string q("SELECT AbilityScore.name, ArmorPropMod.[mod] FROM AbilityScore INNER JOIN ArmorPropMod ON AbilityScore.[id] = ArmorPropMod.[abilityScoreId] WHERE ArmorPropMod.armorId = ");
			q += argv[7];
			std::get<3>(*p).cmd(q.c_str(), [](void * somePP, int argc, char **argv, char **azColName)->int {
				auto pp = (std::pair< Armor&, std::map<std::string, AbilityScores>&>*) somePP;
				pp->first.addPropertyModifier(std::pair<AbilityScores, int>(pp->second[argv[0]],std::stoi(argv[1])));
				return 0;
			}, &AaM);

			std::get<0>(*p)[argv[0]] = armor;
			return 0;
		}, &combo);
	}

	//consumable loading
	template<>
	void loading<std::map<std::string, Consumable>>(std::map<std::string, Consumable>& consMap) {

		std::pair<std::map<std::string, Consumable>&, std::map<std::string, std::function<void()>>&> combo(consMap, functions);
		db.cmd("SELECT [Item].[name], [Item].[description], [Item].[weight], [Item].[baseValue], [Consumable].[functionName], [Consumable].[quantityUses] FROM Consumable INNER JOIN Item ON [Consumable].[itemId] = [Item].[id];", [](void * someP, int argc, char **argv, char **azColName)->int {
			auto p = (std::pair<std::map<std::string, Consumable>&, std::map<std::string, std::function<void()>>&>*)someP;
			Consumable consumable(p->second[argv[4]]);
			consumable.setName(argv[0]);
			consumable.setDescription(argv[1]);
			consumable.setWeight(std::stoi(argv[2]));
			consumable.setBaseValue(std::stoi(argv[3]));
			consumable.setQuantityUses(std::stoi(argv[5]));
			p->first[argv[0]] = consumable;
			return 0;
		}, &combo);
	}

	//loading save data
	template<>
	void loading<Party>(Party& party) {
		//set party info
		db.cmd("SELECT currency, overworldPosition FROM PartyInfo WHERE id = 1", [](void * someP, int argc, char **argv, char **azColName)->int {
			auto p = (Party*)someP;
			p->setCurrency(std::stoi(argv[0]));
			p->setOverworldPosition(std::stoi(argv[1]));
			return 0;
		}, &party);

		//load party inventory
		std::map<std::string, Weapon> weapons;
		std::map<std::string, Armor> armor;
		std::map<std::string, Consumable> consumables;
		loading(weapons, armor, consumables);
		std::tuple<Party&, std::map<std::string, Weapon>&, std::map<std::string, Armor>&, std::map<std::string, Consumable>&> allForMap(party, weapons, armor, consumables);
		party.clearInventory();
		db.cmd("SELECT Item.name FROM Item INNER JOIN (Inventory INNER JOIN InventoryItem ON Inventory.id = InventoryItem.inventoryId) ON Item.id = InventoryItem.itemId WHERE Inventory.playerId = 0;", [](void * someP, int argc, char **argv, char **azColName)->int {
			auto p = (std::tuple<Party&, std::map<std::string, Weapon>&, std::map<std::string, Armor>&, std::map<std::string, Consumable>&>*)someP;
			auto & partey = std::get<0>(*p);
			auto & weaponMap = std::get<1>(*p);
			auto & armorMap = std::get<2>(*p);
			auto & consumablesMap = std::get<3>(*p);
			auto w = weaponMap.find(argv[0]);
			if (w != weaponMap.end()) {
				partey.addToInventory(std::make_shared<Weapon>(w->second));
				return 0;
			} 
			auto a = armorMap.find(argv[0]);
			if (a != armorMap.end()) {
				partey.addToInventory(std::make_shared<Armor>(a->second));
				return 0;
			}
			auto c = consumablesMap.find(argv[0]);
			if (c != consumablesMap.end()) {
				partey.addToInventory(std::make_shared<Consumable>(c->second));
				return 0;
			}
			return 0;
		}, &allForMap);
		//load inventory each player
		for (unsigned int i = 0; i < party.size(); i++) {
			party[i]->clearEquipment();

			//load level abilityPoints exp
			std::string qL("SELECT Player.[exp], Player.[level], Player.[abilityPoints] FROM Player WHERE Player.id = ");
			qL += std::to_string(i + 1);
			db.cmd(qL.c_str(), [](void * someP, int argc, char **argv, char **azColName)->int {
				auto p = (std::shared_ptr<PlayerCharacter>*)someP;
				(*p)->setAbilityPoints(std::stoi(argv[2]));
				(*p)->setCharlevel(std::stoi(argv[1]));
				(*p)->setExperience(std::stoi(argv[0]));
				return 0;			
			},&party[i]);

			//load Ability scores
			std::string qAS("SELECT AbilityScore.name, AbilityScorePlayer.value FROM AbilityScore INNER JOIN AbilityScorePlayer ON AbilityScore.[id] = AbilityScorePlayer.[abilityScoreId] WHERE AbilityScorePlayer.playerId = ");
			qAS += std::to_string(i + 1);

			std::unordered_map<AbilityScores, int> stats;
			std::pair< std::unordered_map<AbilityScores, int>&, std::map<std::string, AbilityScores>&> comboAS(stats, abilityScores);
			db.cmd(qAS.c_str(), [](void * someP, int argc, char **argv, char **azColName)->int {
				auto p = (std::pair< std::unordered_map<AbilityScores, int>&, std::map<std::string, AbilityScores>&>*)someP;
				p->first[p->second[argv[0]]] = std::stoi(argv[1]);
				return 0;
			}, &comboAS);

			party[i]->setCharacterStats(stats);

			//armor loading
			std::tuple<std::shared_ptr<PlayerCharacter>&, std::map<std::string, ArmorSlots>&, std::map<std::string, AbilityScores>&, Database&> comboArmor(party[i], armorSlots, abilityScores, db);
			std::string qA("SELECT Item.name, Item.description, Item.weight, Item.baseValue, ArmorSlot.name, Armor.physicalProtection, Armor.magicalProtecton, Armor.id FROM ((ArmorSlot INNER JOIN Armor ON ArmorSlot.[id] = Armor.[armorSlotId]) INNER JOIN Item ON Armor.[itemId] = Item.[id]) INNER JOIN ((Player INNER JOIN Inventory ON Player.id = Inventory.playerId) INNER JOIN InventoryItem ON Inventory.id = InventoryItem.inventoryId) ON Item.id = InventoryItem.itemId WHERE Player.id = ");
			qA += std::to_string(i + 1);
			db.cmd(qA.c_str(), [](void * someP, int argc, char **argv, char **azColName)->int {
				//primaire attributes
				auto p = (std::tuple<std::shared_ptr<PlayerCharacter>&, std::map<std::string, ArmorSlots>&, std::map<std::string, AbilityScores>&, Database&>*)someP;
				Armor armor;
				armor.setName(argv[0]);
				armor.setDescription(argv[1]);
				armor.setWeight(std::stoi(argv[2]));
				armor.setBaseValue(std::stoi(argv[3]));
				armor.setArmorSlot(std::get<1>(*p)[argv[4]]);
				armor.setPhysicalProtection(std::stoi(argv[5]));
				armor.setMagicalProtection(std::stoi(argv[6]));
				//second
				std::pair< Armor&, std::map<std::string, AbilityScores>&> AaM(armor, std::get<2>(*p));
				std::string q("SELECT AbilityScore.name, ArmorPropMod.[mod] FROM AbilityScore INNER JOIN ArmorPropMod ON AbilityScore.[id] = ArmorPropMod.[abilityScoreId] WHERE ArmorPropMod.armorId = ");
				q += argv[7];
				std::get<3>(*p).cmd(q.c_str(), [](void * someP, int argc, char **argv, char **azColName)->int {
					auto p = (std::pair< Armor&, std::map<std::string, AbilityScores>&>*)someP;
					p->first.addPropertyModifier(std::pair<AbilityScores, int>(p->second[argv[0]], std::stoi(argv[1])));
					return 0;
				}, &AaM);

				std::get<0>(*p)->setArmor(armor.getArmorSlot(), armor);
				return 0;
			}, &comboArmor);

			//weapon loading
			std::tuple<std::shared_ptr<PlayerCharacter>&, std::map<std::string, WeaponSlots>&, std::map<std::string, DamageTypes>&, Database&> comboWeapon(party[i], weaponSlots, damageTypes, db);
			std::string qW("SELECT Item.name AS Item_name, Item.description, Item.weight, Item.baseValue, WeaponSlot.name AS WeaponSlot_name, DamageType.name AS DamageType_name, Weapon.primDamage, Weapon.id FROM (Item INNER JOIN (DamageType INNER JOIN (WeaponSlot INNER JOIN Weapon ON WeaponSlot.[id] = Weapon.[weaponSlotId]) ON DamageType.[id] = Weapon.[primDamageTypeId]) ON Item.[id] = Weapon.[itemId]) INNER JOIN InventoryItem ON Item.id = InventoryItem.itemId WHERE InventoryItem.inventoryId = ");
			qW += std::to_string(i + 2);
			db.cmd(qW.c_str(), [](void * someP, int argc, char **argv, char **azColName)->int {
				auto p = (std::tuple<std::shared_ptr<PlayerCharacter>&, std::map<std::string, WeaponSlots>&, std::map<std::string, DamageTypes>&, Database&>*)someP;
				Weapon weapon(std::get<1>(*p)[argv[4]], std::pair<DamageTypes, int>(std::get<2>(*p)[argv[5]], std::stoi(argv[6])));
				weapon.setName(argv[0]);
				weapon.setDescription(argv[1]);
				weapon.setWeight(std::stoi(argv[2]));
				weapon.setBaseValue(std::stoi(argv[3]));
				std::pair<Weapon&, std::map<std::string, DamageTypes>&> wAm(weapon, std::get<2>(*p));
				std::string q = "SELECT DamageType.name, WeaponSecDamageType.damage FROM DamageType INNER JOIN WeaponSecDamageType ON DamageType.[id] = WeaponSecDamageType.[damageTypeId] WHERE WeaponSecDamageType.weaponId = ";
				q += argv[7];
				std::get<3>(*p).cmd(q.c_str(), [](void * w, int argc, char **argv, char **azColName)->int {
					auto ww = (std::pair<Weapon&, std::map<std::string, DamageTypes>&>*)w;
					ww->first.addSecondaryDamageEffect(std::pair<DamageTypes, int>(ww->second[argv[0]], std::stoi(argv[1])));
					return 0;
				}, &wAm);
				std::get<0>(*p)->setWeapon(weapon.getWeaponSlot(), weapon);
				return 0;
			}, &comboWeapon);
		}
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

	//base template for unpacking
	template<typename T, typename ... Attributes>
	void saving(T& t, Attributes& ... attributes) {
		saving(t);
		saving(attributes...);
	}

	//base template for saving please specialise
	template<typename T>
	void saving(T& t) {
		std::cerr << "uknown type: " << typeid(t).name() << std::endl;
	}

	template<>
	void saving<Party>(Party& party) {
		
		std::string query("");
		std::string id("");

		db.cmd("BEGIN");

		query = "UPDATE PartyInfo SET ";
		query += ("currency = " + std::string(std::to_string(party.getCurrency())) + ", ");
		query += ("overworldPosition = " + std::string(std::to_string(party.getOverworldPosition())) + " WHERE id = 1");

		db.cmd(query.c_str());

		db.cmd("DELETE FROM InventoryItem");

		db.cmd("VACUUM");

		for (auto & item : party.getInventory()) {
			query = "SELECT id FROM Item Where name = ";
			query += ("'"+item->getName()+"'");
			db.cmd(query.c_str(), [](void * someP, int argc, char **argv, char **azColName)->int {
				auto p = (std::string*)someP;
				*p = argv[0];
				return 0;
			}, &id);

			query = "INSERT INTO InventoryItem (inventoryId, itemId) VALUES ( 1, ";
			query += (id + " )");
			db.cmd(query.c_str());
		}

		for (unsigned int i = 0; i < party.size(); i++) {
			//save exp level attr
			query = "UPDATE Player SET ";
			query += ("exp = " + std::string(std::to_string(party[i]->getExperience())) + ", ");
			query += ("abilityPoints = " + std::string(std::to_string(party[i]->getAbilityPoints())) + ", ");
			query += ("level = " + std::string(std::to_string(party[i]->getCharlevel())) + " WHERE id = " + std::string(std::to_string(i + 1)));
			db.cmd(query.c_str());


			
			auto stats = party[i]->getCharacterStats();
			
			for (auto & stat : stats) {				
				query = "UPDATE AbilityScorePlayer SET value = " + std::string(std::to_string(stat.second)) + " ";
				query += "WHERE ";
				query += "playerId = " + std::string(std::to_string(i + 1)) + " AND ";
				query += "abilityScoreId = " + std::string(std::to_string(abilityScoresId[stat.first])) + ";";
				db.cmd(query.c_str());
			}

			//save weapons
			for (auto & weapon : party[i]->getWeaponMap()) {
				query = "SELECT id FROM Item Where name = ";
				query += ("'" + weapon.second.getName() + "'");
				db.cmd(query.c_str(), [](void * someP, int argc, char **argv, char **azColName)->int {
					auto p = (std::string*)someP;
					*p = argv[0];
					return 0;
				}, &id);

				query = "INSERT INTO InventoryItem (inventoryId, itemId) VALUES ";
				query += ("( " + std::to_string(i+2) + ", " + id + " )");
				db.cmd(query.c_str());
			}

			//save armor
			for (auto & armor : party[i]->getArmorMap()) {
				query = "SELECT id FROM Item Where name = ";
				query += ("'" + armor.second.getName() + "'");
				db.cmd(query.c_str(), [](void * someP, int argc, char **argv, char **azColName)->int {
					auto p = (std::string*)someP;
					*p = argv[0];
					return 0;
				}, &id);

				query = "INSERT INTO InventoryItem (inventoryId, itemId) VALUES ";
				query += ("( " + std::to_string(i + 2) + ", " + id + " )");
				db.cmd(query.c_str());
			}
		}

		db.cmd("COMMIT");
	}
	
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
	DataManager(const char *, std::map<std::string, std::function<void()>>&func);

	//closes the database
	~DataManager();


};

