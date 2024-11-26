#define _GNU_SOURCE

#include "simulation.h"
#include "arr_queue.h"
#include "list_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ABS(x) ((x) < 0 ? -(x) : (x))

#define STEP_REPORT 100
#define MAX_CYCLES 5

size_t MAX_REQUEST_COUNT = 1000;

int T1_LOWER = 0;
int T1_UPPER = 6;

int T2_LOWER = 0;
int T2_UPPER = 1;

static float random_float(float min, float max)
{
    return min + (max - min) * ((float)rand() / (float)RAND_MAX);
}

void run_simulation_list_queue(float *exp_time)
{
    srand(time(NULL));
    struct timespec start, end;
    size_t entered = 0, left = 0, work_time = 0;
    float current_time = 0.0f, total_idle_time = 0.0f; // Текущее время и время простоя
float next_arrival_time = 0.0f; // Время прибытия следующей заявки
    float state = 0.0f;
    
    list_queue_t queue = { 0 };
    list_queue_init(&queue);

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    printf("%sСимуляция обслуживания %zu заявок обслуживающего аппарата%s\n", GREEN, MAX_REQUEST_COUNT, RESET);

    while (left < (size_t)MAX_REQUEST_COUNT)
    {
        // while (current_time > next_arrival_time && entered < MAX_REQUEST_COUNT)
        // while (list_queue_is_empty(queue) || current_time > next_arrival_time) Исходное
        while (current_time > next_arrival_time)
        {
            next_arrival_time += random_float(T1_LOWER, T1_UPPER);
            if (list_queue_is_empty(queue) && next_arrival_time > current_time)
            {
                total_idle_time += next_arrival_time - current_time;
                current_time = next_arrival_time;
            }
            entered++;
            data_t request = { .request_data = { .arrival_time = next_arrival_time, .processing_count = 1 } };
            list_queue_push(&queue, &request, sizeof(data_t));
        }
        int is_report = 0;
        state += queue.count;
        work_time++;
        current_time += random_float(T2_LOWER, T2_UPPER);

        data_t request = { 0 };
        list_queue_pop(&queue, &request, sizeof(data_t));

        if (request.request_data.processing_count <= MAX_CYCLES)
        {
            request.request_data.processing_count++;
            request.request_data.arrival_time = current_time;
            // Возвращается в конец очереди
            list_queue_push(&queue, &request, sizeof(data_t));
        }
        else
        {
            // Выходит из очереди
            left++;
            is_report = 1;
        }

        if (is_report && left % STEP_REPORT == 0)
        {
            printf("Количество заявок: %zu\n", left);
            printf("Текущая длина очереди: %zu\n", queue.count);
            printf("Средняя длина очереди: %.2f\n\n", state / work_time);
            is_report = 0;
        }
    }

    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    *exp_time = (float)((end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3);

    printf("\nОбщее время моделирования: %.2f\n"
           "Время простоя ОА: %.2f\n"
           "Кол-во вошедших заявок: %zu\n"
           "Кол-во вышедших заявок: %zu\n"
           "Кол-во срабатываний ОА: %zu\n",
           current_time, total_idle_time, entered, left, work_time);

    

    
    
    float average_enter_wait = (float)(T1_UPPER + T1_LOWER) / 2;
    float calc_request_count = current_time / average_enter_wait;
    float calculated_time = average_enter_wait * MAX_REQUEST_COUNT;
    printf("\nВычисление погрешностей.\n"
           "Вычисленное кол-во заявок: %.2f, имеем: %zu, погрешность: %.2f%%\n"
           "Аппарат работал: %zu е.в., простаивал: %.2f е.в.\n"
           "Значит время моделирования должно быть: %.2f е.в., имеем %.2f е.в., погрешность: %.2f%%\n",
           calc_request_count, entered, ABS((entered - calc_request_count) / calc_request_count * 100),
           work_time, total_idle_time,
           calculated_time, current_time, ABS((current_time - calculated_time) / calculated_time * 100));

    list_queue_free(&queue);
}
