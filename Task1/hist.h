#ifndef HIST_H
#define HIST_H

extern int min;
extern int max;

void put_value(int t, int* histogram);
void get_borders(int* bords);
void norm_hist(int* histogram, float* histogram_f);
void draw_hist(float* histogram);

#endif