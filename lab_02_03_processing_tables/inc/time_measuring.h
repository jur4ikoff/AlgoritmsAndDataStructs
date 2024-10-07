#ifndef TIME_H
#define TIME_H
#include <stdio.h>

#define MAX_EXP_FILES 10
typedef struct
{
    size_t size;
    long long time_def_mysort;
    long long time_def_qsort;
    long long time_key_mysort;
    long long time_key_qsort;
} measuring;

int compare_times();
#endif