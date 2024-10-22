#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "time_measuring.h"
#include "errors.h"
#include "csc_matrix.h"
#include "default_matrix.h"
#include "utils.h"

static double sum_time(double time_array[], size_t count)
{
    double sum = 0;
    for (size_t i = 0; i < count; i++)
    {
        sum += time_array[i];
    }
    return sum;
}

// Подсчет RSE
static int calc_rse(double time_array[], size_t count, double *rse)
{
    double t_avg, dispersion = 0;
    if (count <= 1)
        return -1;
    t_avg = sum_time(time_array, count) / count;

    for (size_t i = 0; i < count; i++)
    {
        dispersion += pow((time_array[i] - t_avg), 2);
    }
    dispersion /= (count - 1);
    double standard_deviation = sqrt(dispersion);
    double std_error = standard_deviation / sqrt(count);
    *rse = std_error * 100 / t_avg;
    return ERR_OK;
}

static double mean(double array[], size_t count)
{
    double mean = 0;
    for (size_t i = 0; i < count; i++)
    {
        mean += (array[i] - mean) / (i + 1);
    }
    return mean;
}

static void create_random_matrix(matrix_t *matrix, size_t size, size_t percentiage)
{
    matrix->rows_count = (size_t)size;
    matrix->columns_count = (size_t)size;

    for (size_t i = 0; i < matrix->rows_count; i++)
    {
        for (size_t j = 0; j < matrix->columns_count; j++)
        {
            if (random_chance(percentiage))
            {
                matrix->values[i][j] = rand() % 10000;
            }
        }
    }
}

int run_profiling(void)
{
    struct timespec start_time, end_time;
    size_t size_cur = 10, percentiage = 10, itteration_count = 0;
    int rc = ERR_OK;
    double time_array[MAX_ITERATIONS], rse = 100, time;
    double cpu_time_default, cpu_time_csc;
    matrix_t default_matrix_1 = {0}, default_matrix_2 = {0}, def_res = {0};
    csc_t csc_matrix_1 = {0}, csc_matrix_2 = {0}, csc_res = {0};

    while (percentiage <= MAX_PERCENTIAGE)
    {
        size_cur = 10;
        char filename[MAX_PART_LEN];
        snprintf(filename, sizeof(filename), "./data/matrix_%zu_fill.csv", percentiage);
        FILE *file = fopen(filename, "w");
        if (file == NULL)
            return ERR_FILENAME;
        fprintf(file, "size;def;csc\n");

        while (size_cur <= MAX_EXP_SIZE)
        {
            printf("Замер матриц размером %zu, процент заполнения - %zu\n", size_cur, percentiage);
            create_default_matrix(&default_matrix_1, size_cur, size_cur);
            create_default_matrix(&default_matrix_2, size_cur, size_cur);

            itteration_count = 0;
            rse = 100;
            // Прогон qsort
            while ((itteration_count < MAX_ITERATIONS) && (rse > 1 || itteration_count < MIN_ITERATIONS))
            {
                create_random_matrix(&default_matrix_1, size_cur, percentiage); // Генерация рандомной матрицы
                create_random_matrix(&default_matrix_2, size_cur, percentiage);

                clock_gettime(CLOCK_REALTIME, &start_time);
                add_matrix_t(default_matrix_1, default_matrix_2, &def_res);
                clock_gettime(CLOCK_REALTIME, &end_time);

                free_default_matrix(&def_res);
                time = (double)((end_time.tv_sec - start_time.tv_sec) * 1e9 + (end_time.tv_nsec - start_time.tv_nsec));

                time_array[itteration_count] = time;
                itteration_count++;
                calc_rse(time_array, itteration_count, &rse);
            }
            cpu_time_default = mean(time_array, itteration_count);

            itteration_count = 0;
            rse = 100;
            // Прогон qsort
            while ((itteration_count < MAX_ITERATIONS) && (rse > 1 || itteration_count < MIN_ITERATIONS))
            {
                create_random_matrix(&default_matrix_1, size_cur, percentiage); // Генерация рандомной матрицы
                create_random_matrix(&default_matrix_2, size_cur, percentiage);
                csc_matrix_1 = convert_to_csc(default_matrix_1);
                csc_matrix_2 = convert_to_csc(default_matrix_2);

                clock_gettime(CLOCK_REALTIME, &start_time);
                sum_csc_matrix(csc_matrix_1, csc_matrix_2, &csc_res);
                clock_gettime(CLOCK_REALTIME, &end_time);

                free_csc_matrix(&csc_matrix_1);
                free_csc_matrix(&csc_matrix_2);
                free_csc_matrix(&csc_res);
                time = (double)((end_time.tv_sec - start_time.tv_sec) * 1e9 + (end_time.tv_nsec - start_time.tv_nsec));

                time_array[itteration_count] = time;
                itteration_count++;
                calc_rse(time_array, itteration_count, &rse);
            }
            cpu_time_csc = mean(time_array, itteration_count);
            fprintf(file, "%zu;%.4f;%.4f\n", size_cur, cpu_time_default, cpu_time_csc);

            free_default_matrix(&default_matrix_1);
            free_default_matrix(&default_matrix_2);
            size_cur += INCR_COEF;
        }
        percentiage += PERCENTIAGE_STEP;

        fclose(file);
    }
    return rc;
}
