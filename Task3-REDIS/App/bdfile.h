#ifndef BDFILE_H
#define BDFILE_H
#include "sqlite3.h"

void create_DB(sqlite3 *DB);
int insert(sqlite3* DB, int cycle, int index, float time_mcs);

#endif