#include <stdio.h>
#include "data.h"


void do0(int** mos) {

    for (int i = 0; i < 1000; i++) {

        for (int j = 0; j < 1000; j++) {
            mos[i][j] = 0;
        }
    }

}

void do1(int** mos) {

    for (int j = 0; j < 1000; j++) {
        for (int i = 0; i < 1000; i++) {
            mos[i][j] = 0;
        }
    }

}



