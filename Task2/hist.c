#include "stdio.h"
#include "math.h"
#include "hist.h"

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
	printf("xx-xx--|----------\n");
	for(int i = 0; i < 10; i++){
		int value = (int)(histogram[i]*10);
		printf("%2d-%2dms|", i*2+1, i*2+2);
		for(int j = 0; j < value; j++){
			printf("*");
		}
		printf("\n");
	}
	printf("xx-xx--|----------\n");
	printf("xx-xx--|***100%%***\n");
}