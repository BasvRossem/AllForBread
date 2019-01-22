#include "Database.hpp"

Database::Database():
	db(NULL)
{}

Database::Database(const char * filename):
	db(NULL)
{
	open(filename);
}

bool Database::open(const char * filename) {
	if (close()) {
		sqlite3_open(filename, &db);
		return true;
	}
	return false;
}

bool Database::open(const char * filename, int flags, const char * zVfs) {
	if (close()) {
		if(SQLITE_OK == sqlite3_open_v2(filename, &db, flags, zVfs))
		return true;
	}
	return false;
}

bool Database::close(){
	return (SQLITE_OK == sqlite3_close(db));
}

bool Database::cmd(const char * query, int(*callback)(void *, int, char **, char **), void * firstargumentofcallback, char ** errmsg){
	return (SQLITE_OK == sqlite3_exec(db, query, callback, firstargumentofcallback, errmsg));
}


Database::~Database() {
}
