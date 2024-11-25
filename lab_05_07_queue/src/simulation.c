#define _GNU_SOURCE

#include "simulation.h"
#include "arr_queue.h"
#include "list_queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define STEP_REPORT 100

int MAX_EXP_COUNT = 1000;

int T1_LOWER = 0;
int T1_UPPER = 6;

int T2_LOWER = 0;
int T2_UPPER = 1;

static float random_float(float min, float max)
{
    return min + (max - min) * ((float)rand() / (float)RAND_MAX);
}

/**
 * @brief Функция для симуляции работы обслуживающего автомата
 * @param logfile Файл для записи в файл информации о работе аппарата
 * @param exp_time Полное время эксперимента
 */
void run_simulation_list_queue(char *logfile, float *exp_time)
{
    // Инициализация очереди
    list_queue_t queue = {0};
    list_queue_init(&queue);

    // инициализация переменных
    struct timespec start, end;
    size_t entered = 0, left = 0; // счетчик зашедших и вышедших переменных
    // float cur_time = 0.0f, total_idle_time = 0.0f;

    printf("Симуляция обработки %d заявок обслуживающего автомата\n", MAX_EXP_COUNT);

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    while (left < MAX_EXP_COUNT)
    {
    }

    float a = random_float(1, 2);
    printf("%f\n", a);
    list_queue_free(&queue);

    (void)logfile;
    (void)exp_time;
    (void)entered;
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
}

/*
int simulate_first_n(size_t n, queue_base_t *queue, float *time)
{
    size_t entered = 0, left = 0;
    size_t act = 0;
    float current_time = 0.0f, total_idle_time = 0.0f;
    float next_arrival_time = 0.0f; // Время прибытия следующей заявки
    float state = 0.0f;
    while (left < n)
    {
        while (queue->is_empty(queue) || current_time > next_arrival_time)
        {
            next_arrival_time += rand_in_range_float(T1_LOWER, T1_UPPER);
            if (queue->is_empty(queue) && next_arrival_time > current_time)
            {
                total_idle_time += next_arrival_time - current_time;
                current_time = next_arrival_time;
            }
            entered++;
            data_t req = { .req = { .arrival_time = next_arrival_time } };
            if ((rc = queue->push(queue, &req)) != ERR_OK)
                goto exit;
        }

        int f = 0;
        state += queue->size;
        act++;
        current_time += rand_in_range_float(T2_LOWER, T2_UPPER);

        data_t req = { 0 };
        if ((rc = queue->pop(queue, &req)) != ERR_OK)
            goto exit;

        if (rand_with_probability(P))
        {
            req.req.arrival_time = current_time;
            // Возвращается в конец очереди
            if ((rc = queue->push(queue, &req)) != ERR_OK)
                goto exit;
        }
        else
        {
            // Выходит из очереди
            // total_idle_time += current_time - req.req.arrival_time;
            left++;
            f = 1;
        }

        if (f && left % REPORT_INTERVAL == 0)
        {
            printf("Количетсво заявок: %zu\n", left);
            printf("Текущая длина очереди: %zu\n", queue->size);
            printf("Средняя длина очереди: %.2f\n\n", state / act);
        }
        if (f)
            f = 0;
    }

    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    *time = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;

    printf("\nОбщее время моделирования: %.2f\n"
           "Время простоя ОА: %.2f\n"
           "Кол-во вошедших заявок: %zu\n"
           "Кол-во вышедших заявок: %zu\n"
           "Кол-во срабатываний ОА: %zu\n",
           current_time, total_idle_time, entered, left, act);

    double calculated_time = 0;

    if ((double)(T1_UPPER + T1_LOWER) / 2 > (double)(T2_UPPER + T2_LOWER) / 2 / (1-P))
        calculated_time = ((double)(T1_UPPER + T1_LOWER) / 2) * n;
    else
        calculated_time = (double)(T2_UPPER + T2_LOWER) / 2 * n * (1 / (1 - P));

    float t_avg_wait_req = (float)(T1_UPPER + T1_LOWER) / 2;
    // float t_avg_serv_req = (float)(T2_UPPER + T2_LOWER) / 2;
    float calculated_req_cnt = current_time / t_avg_wait_req;
    printf("\nВычисление погрешностей.\n"
           "Вычисленное кол-во заявок: %.2f, имеем: %zu, погрешность: %.2f%%\n"
           "Аппарат работал: %zu, простаивал: %.2f\n"
           "Значит время моделирования должно быть: %.2f, имеем %.2f, погрешность: %.2f%%\n",
           calculated_req_cnt, entered, ABS((entered - calculated_req_cnt) / calculated_req_cnt * 100),
           act, total_idle_time,
           calculated_time, current_time, ABS((current_time - calculated_time) / calculated_time * 100));

    exit:
    return rc;
}
*/
