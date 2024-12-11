#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <math.h>
#include "data.h"
#include "hist.h"
#include "bdfile.h"


int main() {

    setlocale(LC_ALL, "ru_RU.UTF-8"); //установка кириллического вывода 
    int rows = 1000, cols = 1000;
    int **mos = malloc(rows * sizeof(int*)); //выделение памяти под двумерный массив
    for (int i = 0; i < rows; i++) {
        
        mos[i] = malloc(cols * sizeof(int));

    }

    int histogram_data[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    float histogram_data_norm[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    create(); //создание БД

    //--------------------отчет времени для do0----------------------
    int time; //начало отчета времени

    for (int i = 0; i < 10000; i++) {
        time = clock();
        do0(mos);
        time = clock() - time; //подсчет секунд
        int index = ceil((float)time / CLOCKS_PER_SEC * 500) - 1; //500 есть сокращение 1000/2, где 1000 - перевод из секунду в милисекунды, а 2 - ширина столбца гистограммы в 2мс, -1 ради индексации
        //printf("На выполнение функции do0 10.000 раз потрачено %f миллисекундсекунд   %d\n", (float)time / CLOCKS_PER_SEC, index);
        histogram_data[index]++;
    }
    
    norm_hist(histogram_data, histogram_data_norm);
    printf("Рузельтаты работы do0: \n");
    draw_hist(histogram_data_norm);

    //--------------------запись результатов в БД----------------------
    for (int j = 0; j < 10; j++) {
        insert(histogram_data[j], 0, j);
    }

    //--------------------обнуление гистограммы----------------------
    for (int i = 0; i < 10; i++) {
        //printf("%d ", histogram_data[i]);
        histogram_data[i] = 0;
    }

    //--------------------отчет времени для do1----------------------
    for (int i = 0; i < 10000; i++) {
        time = clock();
        do1(mos);
        time = clock() - time; //подсчет секунд
        int index = ceil((float)time / CLOCKS_PER_SEC * 500) - 1; 
        //printf("На выполнение функции do1 10.000 раз потрачено %f миллисекунд    %d\n", (float)time / CLOCKS_PER_SEC, index);
        histogram_data[index]++;
    }

    norm_hist(histogram_data, histogram_data_norm);
    printf("Рузельтаты работы do1: \n");
    draw_hist(histogram_data_norm);
    
    //--------------------запись результатов в БД----------------------
    for (int j = 0; j < 10; j++) {
        insert(histogram_data[j], 1, j);
    }
    

    //--------------------обнуление гистограммы----------------------
    for (int i = 0; i < 10; i++) {
        //printf("%d ", histogram_data[i]);
        histogram_data[i] = 0;
    }
}