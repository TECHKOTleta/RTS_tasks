#ifndef HIST_H
#define HIST_H

extern int hist_step;
extern int max_hist;

void put_value(int t, int* histogram);
void norm_hist(int* histogram, float* histogram_f);
void draw_hist(float* histogram);

#endif