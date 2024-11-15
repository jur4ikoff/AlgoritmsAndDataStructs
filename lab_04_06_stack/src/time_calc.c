#include "time_calc.h"
#include "errors.h"
#include "list_stack.h"
#include "static_stack.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Сложение массива double
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

// Вычисление среднего
static double mean(double array[], size_t count)
{
    double mean = 0;
    for (size_t i = 0; i < count; i++)
    {
        mean += (array[i] - mean) / (i + 1);
    }
    return mean;
}

static void generate_random_string(char *string, size_t count)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (size_t i = 0; i < count; i++)
    {
        string[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    string[count - 1] = 0;
}

void run_profiling(void)
{
    srand(time(NULL));
    // Инициализация переменных
    struct timespec start_time, end_time;
    int size = 10, itterations = 0;
    double time_array[MAX_ITERATIONS], rse = 100, time;
    double time_static_stack, time_list_stack;

    // Открытие файлов
    FILE *file = fopen("./data/speed.csv", "w");
    FILE *file_memory = fopen("./data/memory.csv", "w");
    if (file == NULL || file_memory == NULL)
        return;

    fprintf(file, "size;static;list\n");
    fprintf(file_memory, "size;static;list\n");

    while (size <= MAX_SIZE)
    {
        char *string = malloc(sizeof(char) * size);
        if (!string)
            return;

        printf("Замер стека размером %d\n", size);

        // Прогон стека на массиве
        itterations = 0;
        rse = 100;
        while ((itterations < MAX_ITERATIONS) && (rse > 1 || itterations < MIN_ITERATIONS))
        {
            generate_random_string(string, size);
            clock_gettime(CLOCK_REALTIME, &start_time);
            static_stack_is_palindrome(string);
            clock_gettime(CLOCK_REALTIME, &end_time);
            time = (double)((end_time.tv_sec - start_time.tv_sec) * 1e9 + (end_time.tv_nsec - start_time.tv_nsec));
            time_array[itterations] = time;
            itterations++;
            calc_rse(time_array, itterations, &rse);
        }
        time_static_stack = mean(time_array, itterations);

        // Прогон стека на списке
        itterations = 0;
        rse = 100;
        while ((itterations < MAX_ITERATIONS) && (rse > 1 || itterations < MIN_ITERATIONS))
        {
            generate_random_string(string, size);
            clock_gettime(CLOCK_REALTIME, &start_time);
            list_stack_is_palindrome(string);
            clock_gettime(CLOCK_REALTIME, &end_time);
            time = (double)((end_time.tv_sec - start_time.tv_sec) * 1e9 + (end_time.tv_nsec - start_time.tv_nsec));
            time_array[itterations] = time;
            itterations++;
            calc_rse(time_array, itterations, &rse);
        }
        time_list_stack = mean(time_array, itterations);

        // Получение объема памяти выделенной под матрицы
        long long memory_static = sizeof(static_stack_t);
        long long memory_list = sizeof(list_stack_t) * (size + 1);

        // Запись в файл
        fprintf(file, "%d;%.4f;%.4f\n", size, time_static_stack, time_list_stack);
        fprintf(file_memory, "%d;%lld;%lld\n", size, memory_static, memory_list);

        if (size == 10)
            size = 0;
        size += SIZE_STEP;
        free(string);
    }
    fclose(file);
    fclose(file_memory);

    // Запуск скрипта для вывода информации
    system("python3 src/print_res.py");
}
