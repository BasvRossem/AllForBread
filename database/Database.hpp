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

	bool cmd(const char *query, int(*callback)(void*, int, char**, char**) = NULL, void * firstargumentofcallback = NULL, char **errmsg = NULL);

	template <typename T>
	bool cmd(const char *query, T callback, void * firstargumentofcallback = NULL, char **errmsg = NULL);

	inline sqlite3 * getInstance() { return db; };


	~Database();
};

template<typename T>
inline bool Database::cmd(const char * query, T callback, void * firstagumentofcallback, char ** errmsg){
	auto h = sqlite3_exec(db, query, callback, firstagumentofcallback, errmsg);
	return (SQLITE_OK == h);
}
