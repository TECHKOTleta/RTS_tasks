#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "dbfile.h"

void create_DB(sqlite3 *DB) {
char *err = 0;
/*int exit = sqlite3_open("Times.db", &DB);

if (exit) {
printf("Ошибка при открытии базы данных\n");
}
else {
printf("База данных успешно открыта\n");
}*/

char *sql_create_table = "DROP TABLE IF EXISTS answer_times;"
"CREATE TABLE answer_times(cycle integer, arr_index integer, time_mcs float, PRIMARY KEY(cycle, arr_index))";

int exit = sqlite3_exec(DB, sql_create_table, 0, 0, &err);
if (exit != SQLITE_OK ) {
printf("Ошибка добавления таблицы %s\n", sqlite3_errmsg(DB));
sqlite3_free(err);
}
else {
printf("Таблица создана\n");
}
//sqlite3_close(DB);
}

int insert(sqlite3 *DB, int cycle, int index, float time_mcs) {
char* err = 0;
/*sqlite3* DB;
int exit = sqlite3_open("Times.db", &DB);

if (exit) {
printf("Ошибка при открытии базы данных: %s\n", sqlite3_errmsg(DB));
}*/

const char *sql_insert_value = "INSERT INTO answer_times(cycle, arr_index, time_mcs) VALUES(?, ?, ?);";
sqlite3_stmt *stmt;
int exit = sqlite3_prepare_v2(DB, sql_insert_value, -1, &stmt, 0);
if (exit != SQLITE_OK) {
printf("Ошибка подготовки запроса: %s\n", sqlite3_errmsg(DB));
// sqlite3_close(DB);
return 0;
}

sqlite3_bind_int(stmt, 1, cycle);
sqlite3_bind_int(stmt, 2, index);
sqlite3_bind_double(stmt, 3, time_mcs);

//printf("Cycle: %d, Index: %d\n", cycle, index);
exit = sqlite3_step(stmt);
int counting_success = 0;
if (exit != SQLITE_DONE) {
printf("Ошибка выполнения запроса%s\n", sqlite3_errmsg(DB));
}
else {
counting_success = 1;
}

sqlite3_finalize(stmt);
//sqlite3_close(DB);

return (counting_success);
}