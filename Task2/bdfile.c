#include <stdio.h>
#include <stdlib.h>
#include "bdfile.h"

void connect(){
    sqlite3* DB; 
    int exit = 0; 
    exit = sqlite3_open("example.db", &DB); 
  
    if (exit) { 
        printf("Error open DB\n");
    } 
    else
        printf("Opened Database Successfully!\n");

    char *sql_create_table = "DROP TABLE IF EXISTS signal;"
                "CREATE TABLE signal(id INTEGER PRIMARY KEY AUTOINCREMENT, time FLOAT);";
    
    enter_ = sqlite3_exec(DB, sql_create_table, 0, 0);
    if (enter_ != SQLITE_OK ) {
        printf("Ошибка добавления таблицы\n");
    }
    else {
        printf("Таблица создана\n");
    }
    sqlite3_close(DB);
}