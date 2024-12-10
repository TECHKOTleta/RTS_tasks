#include "stdio.h"
#include "math.h"
#include "hist.h"

int min;
int max;

void put_value(int t, int* histogram) {
	if( t < min || t > max){
		return;
	}
	int length = max - min + 1; //длина диапазона
	t = t - min + 1; //преобразовываем число из исходного дипазона в диапазон 1-length
	float point = ceil((float)t*10/length); //point проецирует положение t с диапазона 1-length на диапазон 1-10
	t = (int)point-1; //сменяем на диапазон индексов 0-9
	histogram[t] = histogram[t]+1;
}

void get_borders(int* bords){  //записывает верхние значения каждого диапазона
	int length = max-min+1;
	float gap_length = (float)length/10;
	float progres = 0;
	for(int i = 0; i < 10; i++){
		progres+=gap_length;
		int value = (int)floor(progres);
		bords[i] = value+min-1;
	}
	bords[9]++; //алгебраически progres бдет стремиться к последнему элементу, но его не достигнет, хотя учитывать его нужно
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
	printf("xxx-xxx|----------\n");
	int borders_values[10];
	get_borders(borders_values);
	for(int i = 0; i < 10; i++){
		int value = (int)(histogram[i]*10);
		printf("%3d-%3d|", i == 0 ? min : borders_values[i-1]+1, borders_values[i]);
		for(int j = 0; j < value; j++){
			printf("*");
		}
		printf("\n");
	}
	printf("xxx-xxx|----------\n");
	printf("xxx-xxx|***100%%***");
}