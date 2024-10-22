#ifndef TIME_MEASURING_H__
#define TIME_MEASURING_H__
#include <stdio.h>

#define MAX_PART_LEN 256
#define MAX_EXP_SIZE 1000
#define MIN_ITERATIONS 10
#define MAX_ITERATIONS 1000
#define PERCENTIAGE_STEP 15
#define MAX_PERCENTIAGE 100
#define INCR_COEF 100

typedef struct
{
    size_t size;
    long long time_def_matrix;
    long long time_csc_matrix;
} measuring_t;

int run_profiling(void);

#endif