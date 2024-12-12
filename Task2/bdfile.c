#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "bdfile.h"

void create() {

    sqlite3* DB;
    int exit = sqlite3_open("histogram.db", &DB);

    if (exit) { 
        printf("Ошибка при открытии базы данных\n");
    } 
    else {
        printf("База данных успешно открыта\n");
    }
    char *sql_create_table = "DROP TABLE IF EXISTS range;"
                "CREATE TABLE range(min integer, max integer, quantity int, method int, PRIMARY KEY(min, method))";
    
    exit = sqlite3_exec(DB, sql_create_table, 0, 0, 0);
    if (exit != SQLITE_OK ) {
        printf("Ошибка добавления таблицы\n");
    }
    else {
        printf("Таблица range создана\n");
    }
    sqlite3_close(DB);
}

int insert(int histogram_data, int i, int j, int counting_success) {
    sqlite3* DB;
    int exit = sqlite3_open("histogram.db", &DB);

    if (exit) {
        printf("Ошибка при открытии базы данных: %s\n", sqlite3_errmsg(DB));
    }

    const char *sql_insert_value = "INSERT INTO range (min, max, quantity, method) VALUES (?, ?, ?, ?)";
    sqlite3_stmt *stmt;

    exit = sqlite3_prepare_v2(DB, sql_insert_value, -1, &stmt, NULL);
    if (exit != SQLITE_OK) {
        printf("Ошибка подготовки запроса: %s\n", sqlite3_errmsg(DB));
        sqlite3_close(DB);
    }

    char fir[10], sec[10], third[10], four[10];
    sprintf(fir, "%d", j * 2 + 1);
    sprintf(sec, "%d", j * 2 + 2);
    sprintf(third, "%d", histogram_data);
    sprintf(four, "%d", i);

    sqlite3_bind_text(stmt, 1, fir, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, sec, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, third, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, four, -1, SQLITE_TRANSIENT);

    exit = sqlite3_step(stmt);
    if (exit != SQLITE_DONE) {
        printf("Ошибка выполнения запроса\n");
    }
    else {
        counting_success = counting_success +1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);

    return (counting_success);
}