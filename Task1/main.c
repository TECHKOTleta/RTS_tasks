#include <stdio.h>
#include <string.h>
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
	char temp[5] = "";
	printf("Вводите значения через enter, окончить -e\n");
	scanf("%s", &temp);
	while(temp[0] != '-' && temp[1] != 'e'){
		int a = atoi(temp);
		put_value(a, histogram);
		scanf("%s", &temp);
	}

	norm_hist(histogram, histogram_norm);
	draw_hist(histogram_norm);
	
	return 0;
}