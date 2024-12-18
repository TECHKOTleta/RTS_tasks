#ifndef HIST_H
#define HIST_H

void put_value(int t, int* histogram);
void norm_hist(int* histogram, float* histogram_f);
void draw_hist(float* histogram);

#endif