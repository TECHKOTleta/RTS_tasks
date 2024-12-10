#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include "data.h"
#include <sqlite3.h>


int main() {

    setlocale(LC_ALL, "ru_RU.UTF-8"); //установка кириллического вывода 
    int rows = 1000, cols = 1000;

    //-------------------работа с БД----------------------
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


    //-----------------конец работы с БД--------------------

    int **mos = malloc(rows * sizeof(int*)); //выделение памяти под двумерный массив

    for (int i = 0; i < rows; i++) {
        
        mos[i] = malloc(cols * sizeof(int));

    }


    //-----------------------отчет времени для do0---------------------
    int time = clock(); //начало отчета времени

    for (int i = 0; i < 10000; i++) {

        do0(mos);

    }
    time = clock() - time; //подсчет секунд

    printf("На выполнение функции do0 10.000 раз потрачено %f секунд\n", (float)time / CLOCKS_PER_SEC);


    //-----------------------отчет времени для do1---------------------
    time = clock(); //начало отчета времени

    for (int i = 0; i < 10000; i++) {

        do1(mos);

    }
    time = clock() - time; //подсчет секунд

    printf("На выполнение функции do1 10.000 раз потрачено %f секунд\n", (float)time / CLOCKS_PER_SEC);
}