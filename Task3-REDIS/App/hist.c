#include "stdio.h"
#include "math.h"
#include "hist.h"

int hist_step = 50;

int min = 1;
int max_hist;

void put_value(int t, int* histogram) {
    if( t < min || t > max_hist){
        return;
    }
    int length = max_hist - min + 1; //длина диапазона
    t = t - min + 1; //преобразовываем число из исходного дипазона в диапазон 1-length
    float point = ceil((float)t*10/length); //point проецирует положение t с диапазона 1-length на диапазон 1-10
    t = (int)point-1; //сменяем на диапазон индексов 0-9
    histogram[t] = histogram[t]+1;
}

void norm_hist(int* histogram, float* histogram_f){
    int maxi = histogram[0];
    for(int i = 1; i < 10; i++){
        maxi = histogram[i] > maxi ? histogram[i] : maxi;
    }
    for(int i = 0; i < 10; i++){
        histogram_f[i] = (float)histogram[i]/maxi;
    }
}

void draw_hist(float* histogram){
    printf("xxxxx-xxxxx----------|----------\n");
    for(int i = 0; i < 10; i++){
        int value = (int)(histogram[i]*10);
        printf("%5d-%5d microsecs|", i*hist_step+1, (i+1)*hist_step);
        for(int j = 0; j < value; j++){
            printf("*");
        }
        printf("\n");
    }
    printf("xxxxx-xxxxx----------|----------\n");
    printf("xxxxx-xxxxx----------|***100%%***\n");
}