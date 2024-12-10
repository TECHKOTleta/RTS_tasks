#include <stdio.h>
#include <locale.h>
#include "hist.h"



int histogram[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
float histogram_norm[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int borders[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int main() {
	setlocale(LC_ALL, "ru_RU.UTF-8");
	printf("Введите min и max, разделяя enter\n");
	int m1, m2;
	scanf("%d", &min); scanf("%d", &max); //переменные из файла hist
	int a = 0;
	printf("Вводите значения через enter, окончить 0\n");
	scanf("%d", &a);
	while(a != 0){
		put_value(a, histogram);
		scanf("%d", &a);
	}

	norm_hist(histogram, histogram_norm);

	draw_hist(histogram_norm);
	
	return 0;
}