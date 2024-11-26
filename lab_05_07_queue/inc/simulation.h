#ifndef __SIMULATION__H__
#define __SIMULATION__H__
#include <stdio.h>

extern int T1_LOWER;
extern int T1_UPPER;

extern int T2_LOWER;
extern int T2_UPPER;

extern size_t MAX_REQUEST_COUNT;

void run_simulation_list_queue(float *exp_time);
void run_simulation_arr_queue(float *exp_time);
#endif
