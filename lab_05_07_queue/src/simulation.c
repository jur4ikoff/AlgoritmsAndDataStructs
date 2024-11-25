#define _GNU_SOURCE

#include "simulation.h"
#include "arr_queue.h"
#include "list_queue.h"
#include <stdlib.h>

#define MAX_EXP_COUNT 1000
#define STEP_REPORT 100

int T1_LOWER = 0;
int T1_UPPER = 6;

int T2_LOWER = 0;
int T2_UPPER = 1;

static float random_float(float min, float max)
{
    return min + (max - min) * ((float)rand() / (float)RAND_MAX);
}

void run_simulation_list_queue(void)
{
    // Код для запуска моделирования системы на основе списка
    float a = random_float(1, 2);
    printf("%f\n", a);
}
