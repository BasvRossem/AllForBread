#include "DataManager.hpp"



DataManager::DataManager(const char * s)
{
	db.open(s);
}


DataManager::~DataManager()
{
	db.close();
}
