/*
Файл с функциями для симуляции работы обслуживающего аппарата
*/

// Определение констант
#define _GNU_SOURCE
#define ABS(x) ((x) < 0 ? -(x) : (x))
#define STEP_REPORT 100
#define MAX_CYCLES 4

// Инклюды заголовочных файлов
#include "simulation.h"
#include "arr_queue.h"
#include "list_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Определение константных переменных
size_t MAX_REQUEST_COUNT = 1000;

int T1_LOWER = 0;
int T1_UPPER = 6;

int T2_LOWER = 0;
int T2_UPPER = 1;

/**
 * @brief Функция генерирует случайное вещественное число в диапазоне от min до max
 * @param min Нижняя граница
 * @param max Верхняя граница
 * @return Случайное вещественное число в диапазоне [min, max]
 */
static float random_float(float min, float max)
{
    return min + (max - min) * ((float)rand() / (float)RAND_MAX);
}

void calc_memory_usage(void)
{
    printf("\n\n");
    printf("Память из data_t %ld\n", sizeof(data_t));
    printf("Память, занимаемая очередью на статическом массиве: %ld\n\n", sizeof(arr_queue_t));
    for (size_t i = 100; i <= 2000; i += 500)
    {
        printf("Память, занимаемая очередью на списке размером %zu элементов: %ld\n", i, sizeof(list_queue_t) + i * sizeof(node_t) + i * sizeof(data_t));
        if (i == 100)
            i = 0;
    }
}

// Функция запускает симуляцию работы ОА
// Реализация очереди на списке
void run_simulation_list_queue(float *exp_time)
{
    printf("%sСимуляция первых %zu заявок обслуживающего аппарата%s\n", GREEN, MAX_REQUEST_COUNT, RESET);

    // Инициализация переменных
    struct timespec start, end;
    size_t entered = 0, left = 0;
    size_t act = 0;
    float current_time = 0.0f, total_idle_time = 0.0f;
    float next_arrival_time = 0.0f; // Время прибытия следующей заявки
    float state = 0.0f;

    float avg_time_in = (float)(T1_LOWER + T1_UPPER) / 2;
    float avg_time_out = (float)(T2_LOWER + T2_UPPER) / 2;

    list_queue_t queue = {0};
    list_queue_init(&queue);

    // Запуск времени
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    while (left < MAX_REQUEST_COUNT)
    {
        while (list_queue_is_empty(queue) || current_time > next_arrival_time)
        {
            next_arrival_time += random_float(T1_LOWER, T1_UPPER);
            if (list_queue_is_empty(queue) && next_arrival_time > current_time)
            {
                total_idle_time += next_arrival_time - current_time;
                current_time = next_arrival_time;
            }
            entered++;
            data_t req = {.request_data = {.arrival_time = next_arrival_time}};
            list_queue_push(&queue, &req, sizeof(req));
        }

        int is_left = 0;
        state += queue.count;
        act++;
        current_time += random_float(T2_LOWER, T2_UPPER);

        data_t req = {0};
        list_queue_pop(&queue, &req, sizeof(req));

        if (req.request_data.processing_count < MAX_CYCLES)
        {
            req.request_data.arrival_time = current_time;
            req.request_data.processing_count++;
            // Возвращается в конец очереди
            list_queue_push(&queue, &req, sizeof(req));
        }
        else
        {
            // Заявка выходит из очереди
            left++;
            is_left = 1;
        }

        if (is_left && left % STEP_REPORT == 0)
        {
            printf("Количество заявок: %zu\n", left);
            printf("Текущая длина очереди: %zu\n", queue.count);
            printf("Средняя длина очереди: %.2f\n\n", state / act);
        }
        if (is_left)
            is_left = 0;
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    *exp_time = (end.tv_sec - start.tv_sec) * (float)1e6 + (end.tv_nsec - start.tv_nsec) / (float)1e3;

    double expected_time = 0;

    if ((float)(T1_UPPER + T1_LOWER) / 2 * left > (float)(T2_UPPER + T2_LOWER) / 2 * left * (MAX_CYCLES + 1))
    {
        expected_time = avg_time_in * MAX_REQUEST_COUNT;
    }
    else
    {
        expected_time = avg_time_out * act;
    }

    float calculated_requests_count = current_time / avg_time_in;

    printf("\nВремя моделирования: %.2f Теоретическое %.2f Погрешность: %.2f%%\n"
           "Аппарат работал: %.2f Простаивал: %.2f е.в\n"
           "Число вошедших заявок: %zu Теоретическое число заявок %.2f  Погрешность %.2f%%\n"
           "Количество вышедших заявок %zu\n"
           "Количество срабатывания ОА %zu\n",
           current_time, expected_time, ABS(expected_time - current_time) / current_time * 100,
           current_time - total_idle_time, total_idle_time,
           entered, calculated_requests_count, ABS(calculated_requests_count - entered) / calculated_requests_count,
           left, act);

    list_queue_free(&queue);
}

// Функция запускает симуляцию работы ОА
// Реализация очереди на массиве
void run_simulation_arr_queue(float *exp_time)
{
    printf("%sСимуляция первых %zu заявок обслуживающего аппарата%s\n", GREEN, MAX_REQUEST_COUNT, RESET);

    // Инициализация переменных
    struct timespec start, end;
    size_t entered = 0, left = 0;
    size_t act = 0;
    float current_time = 0.0f, total_idle_time = 0.0f;
    float next_arrival_time = 0.0f; // Время прибытия следующей заявки
    float state = 0.0f;

    float avg_time_in = (float)(T1_LOWER + T1_UPPER) / 2;
    float avg_time_out = (float)(T2_LOWER + T2_UPPER) / 2;

    arr_queue_t queue = {0};
    arr_queue_init(&queue);


    // Запуск времени
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    while (left < MAX_REQUEST_COUNT)
    {

        // while (arr_queue_is_empty(queue) || current_time > next_arrival_time)
        while (!queue.count || current_time > next_arrival_time)
        {
            next_arrival_time += random_float(T1_LOWER, T1_UPPER);
            if (!queue.count && next_arrival_time > current_time)
            {
                total_idle_time += next_arrival_time - current_time;
                current_time = next_arrival_time;
            }
            entered++;
            data_t req = {.request_data = {.arrival_time = next_arrival_time}};
            arr_queue_push(&queue, &req);
        }

        int is_left = 0;
        state += queue.count;
        act++;
        current_time += random_float(T2_LOWER, T2_UPPER);

        data_t req = {0};
        arr_queue_pop(&queue, &req);
        
        if (req.request_data.processing_count < MAX_CYCLES)
        {
            req.request_data.arrival_time = current_time;
            req.request_data.processing_count++;
            // Возвращается в конец очереди
            arr_queue_push(&queue, &req);
        }
        else
        {
            // Заявка выходит из очереди
            left++;
            is_left = 1;
        }

        if (is_left && left % STEP_REPORT == 0)
        {
            printf("Количество заявок: %zu\n", left);
            printf("Текущая длина очереди: %zu\n", queue.count);
            printf("Средняя длина очереди: %.2f\n\n", state / act);
        }
        if (is_left)
            is_left = 0;
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    *exp_time = (end.tv_sec - start.tv_sec) * (float)1e6 + (end.tv_nsec - start.tv_nsec) / (float)1e3;

    double expected_time = 0;

    if ((float)(T1_UPPER + T1_LOWER) / 2 * left > (float)(T2_UPPER + T2_LOWER) / 2 * left * (MAX_CYCLES + 1))
    {
        expected_time = avg_time_in * MAX_REQUEST_COUNT;
    }
    else
    {
        expected_time = avg_time_out * act;
    }

    float calculated_requests_count = current_time / avg_time_in;

    printf("\nВремя моделирования: %.2f Теоретическое %.2f Погрешность: %.2f%%\n"
           "Аппарат работал: %.2f Простаивал: %.2f е.в\n"
           "Число вошедших заявок: %zu Теоретическое число заявок %.2f  Погрешность %.2f%%\n"
           "Количество вышедших заявок %zu\n"
           "Количество срабатывания ОА %zu\n",
           current_time, expected_time, ABS(expected_time - current_time) / current_time * 100,
           current_time - total_idle_time, total_idle_time,
           entered, calculated_requests_count, ABS(calculated_requests_count - entered) / calculated_requests_count,
           left, act);
}
