#pragma once
#include "sqlite3.h"
#include <functional>
class Database
{
private:
	sqlite3 * db;
public:
	Database();
	Database(const char* filename);

	bool open(const char* filename);
	bool open(const char* filename, int flags, const char *zVfs);
	bool close();

	bool cmd(const char *query, int(*callback)(void*, int, char**, char**) = NULL, void * firstagumentofcallback = NULL, char **errmsg = NULL);

	template <typename T>
	bool cmd(const char *query, T callback, void * firstagumentofcallback = NULL, char **errmsg = NULL);

	inline sqlite3 * getInstance() { return db; };


	~Database();
};

template<typename T>
inline bool Database::cmd(const char * query, T callback, void * firstagumentofcallback, char ** errmsg){

	return (SQLITE_OK == sqlite3_exec(db, query, callback, firstagumentofcallback, errmsg));
}
