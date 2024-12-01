/*
Файл с функциями для симуляции работы обслуживающего аппарата
*/

// Определение констант
#define _GNU_SOURCE
#define ABS(x) ((x) < 0 ? -(x) : (x))
#define STEP_REPORT 100
#define MAX_CYCLES 5

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

// Функция запускает симуляцию работы ОА
// Реализация очереди на списке
void run_simulation_list_queue(float *exp_time)
{
    // Инициализируем функцию srand от unix времени
    srand(time(NULL));
    // Инициализируем переменные
    struct timespec start, end;
    size_t entered = 0, left = 0, work_time = 0;
    float current_time = 0.0f, total_idle_time = 0.0f; // Текущее время и время простоя
    float next_arrival_time = 0.0f;                    // Время прибытия следующей заявки
    float state = 0.0f;

    // Создание очереди
    list_queue_t queue = { 0 };
    list_queue_init(&queue);

    printf("%sСимуляция обслуживания %zu заявок обслуживающего аппарата%s\n", GREEN, MAX_REQUEST_COUNT, RESET);

    // Запуск времени
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    while (left < (size_t)MAX_REQUEST_COUNT || entered < MAX_REQUEST_COUNT)
    {
        while (current_time > next_arrival_time)
        {
            // Расчитываем время
            next_arrival_time += random_float(T1_LOWER, T1_UPPER);
            if (list_queue_is_empty(queue) && next_arrival_time > current_time)
            {
                total_idle_time += next_arrival_time - current_time;
                current_time = next_arrival_time;
            }
            entered++;
            data_t request = { .request_data = { .arrival_time = next_arrival_time, .processing_count = 0 } };
            list_queue_push(&queue, &request, sizeof(data_t));
        }
        // Флаг - нужен ли в текущей иттерации вывод на экран
        int is_report = 0;
        state += queue.count;
        work_time++;
        current_time += random_float(T2_LOWER, T2_UPPER);

        // Берем элемент из очереди
        data_t request = { 0 };
        list_queue_pop(&queue, &request, sizeof(data_t));

        // Обновляем данные запроса и возвращаем обратно в очередь
        if (request.request_data.processing_count < MAX_CYCLES)
        {
            request.request_data.processing_count++;
            request.request_data.arrival_time = current_time;
            // Возвращается в конец очереди
            list_queue_push(&queue, &request, sizeof(data_t));
        }
        else
        {
            // Если элемент прошел больше 5 циклов, то он выходит из очереди
            left++;
            is_report = 1;
        }

        // Вывод данных, когда нужно
        if (is_report && left % STEP_REPORT == 0)
        {
            printf("Количество заявок: %zu\n", left);
            printf("Текущая длина очереди: %zu\n", queue.count);
            printf("Средняя длина очереди: %.2f\n\n", state / work_time);
            is_report = 0;
        }
    }

    // Вычисление замера времени
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    *exp_time = (float)((end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3);

    // Вывод информации о замерах
    printf("\nОбщее время моделирования: %.2f\n"
           "Время простоя ОА: %.2f\n"
           "Кол-во вошедших заявок: %zu\n"
           "Кол-во вышедших заявок: %zu\n"
           "Кол-во срабатываний ОА: %zu\n",
           current_time, total_idle_time, entered, left, work_time);

    // Подсчет времени
    float average_enter_wait = (float)(T1_UPPER + T1_LOWER) / 2;
    float average_enter_out = (float)(T2_UPPER + T2_LOWER) / 2;
    float calc_request_count = current_time / average_enter_wait;
    float calculated_time;
    if (average_enter_wait > average_enter_out)
        calculated_time = average_enter_wait * MAX_REQUEST_COUNT;
    else
        calculated_time = average_enter_out * MAX_REQUEST_COUNT + average_enter_wait * MAX_REQUEST_COUNT;

    // Вывод времени и погрешности
    printf("\nВычисление погрешностей.\n"
           "Вычисленное кол-во заявок: %.2f, имеем: %zu, погрешность: %.2f%%\n"
           "Аппарат работал: %zu е.в., простаивал: %.2f е.в.\n"
           "Значит время моделирования должно быть: %.2f е.в., имеем %.2f е.в., погрешность: %.2f%%\n",
           calc_request_count, entered, ABS((entered - calc_request_count) / calc_request_count * 100),
           work_time, total_idle_time,
           calculated_time, current_time, ABS((current_time - calculated_time) / calculated_time * 100));

    list_queue_free(&queue);
}

// Запуск симуляции для очереди на статическом массиве
void run_simulation_arr_queue(float *exp_time)
{
    // Инициализируем функцию srand от unix времени
    srand(time(NULL));
    // Инициализируем переменные
    struct timespec start, end;
    size_t entered = 0, left = 0, work_time = 0;
    float current_time = 0.0f, total_idle_time = 0.0f; // Текущее время и время простоя
    float next_arrival_time = 0.0f;                    // Время прибытия следующей заявки
    float state = 0.0f;

    // Создание очереди
    arr_queue_t queue = { 0 };
    arr_queue_init(&queue);

    printf("%sСимуляция обслуживания %zu заявок обслуживающего аппарата%s\n", GREEN, MAX_REQUEST_COUNT, RESET);

    // Запуск времени
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    while (left < (size_t)MAX_REQUEST_COUNT || entered < MAX_REQUEST_COUNT)
    {
        while (current_time > next_arrival_time)
        {
            // Расчитываем время
            next_arrival_time += random_float(T1_LOWER, T1_UPPER);
            if (arr_queue_is_empty(queue) && next_arrival_time > current_time)
            {
                total_idle_time += next_arrival_time - current_time;
                current_time = next_arrival_time;
            }
            entered++;
            data_t request = { .request_data = { .arrival_time = next_arrival_time, .processing_count = 0 } };
            arr_queue_push(&queue, &request);
        }
        // Флаг - нужен ли в текущей иттерации вывод на экран
        int is_report = 0;
        state += queue.count;
        work_time++;
        current_time += random_float(T2_LOWER, T2_UPPER);

        // Берем элемент из очереди
        data_t request = { 0 };
        arr_queue_pop(&queue, &request);

        // Обновляем данные запроса и возвращаем обратно в очередь
        if (request.request_data.processing_count < MAX_CYCLES)
        {
            request.request_data.processing_count++;
            request.request_data.arrival_time = current_time;
            // Возвращается в конец очереди
            arr_queue_push(&queue, &request);
        }
        else
        {
            // Если элемент прошел больше 5 циклов, то он выходит из очереди
            left++;
            is_report = 1;
        }

        // Вывод данных, когда нужно
        if (is_report && left % STEP_REPORT == 0)
        {
            printf("Количество заявок: %zu\n", left);
            printf("Текущая длина очереди: %zu\n", queue.count);
            printf("Средняя длина очереди: %.2f\n\n", state / work_time);
            is_report = 0;
        }
    }

    // Вычисление замера времени
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    *exp_time = (float)((end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3);

    // Вывод информации о замерах
    printf("\nОбщее время моделирования: %.2f\n"
           "Время простоя ОА: %.2f\n"
           "Кол-во вошедших заявок: %zu\n"
           "Кол-во вышедших заявок: %zu\n"
           "Кол-во срабатываний ОА: %zu\n",
           current_time, total_idle_time, entered, left, work_time);

    // Подсчет времени
    float average_enter_wait = (float)(T1_UPPER + T1_LOWER) / 2;
    float average_enter_out = (float)(T2_UPPER + T2_LOWER) / 2;
    float calc_request_count = current_time / average_enter_wait;
    float calculated_time;
    if (average_enter_wait > average_enter_out)
        calculated_time = average_enter_wait * MAX_REQUEST_COUNT;
    else
        calculated_time = average_enter_out * MAX_REQUEST_COUNT + average_enter_wait * MAX_REQUEST_COUNT;

    // Вывод времени и погрешности
    printf("\nВычисление погрешностей.\n"
           "Вычисленное кол-во заявок: %.2f, имеем: %zu, погрешность: %.2f%%\n"
           "Аппарат работал: %zu е.в., простаивал: %.2f е.в.\n"
           "Значит время моделирования должно быть: %.2f е.в., имеем %.2f е.в., погрешность: %.2f%%\n",
           calc_request_count, entered, ABS((entered - calc_request_count) / calc_request_count * 100),
           work_time, total_idle_time,
           calculated_time, current_time, ABS((current_time - calculated_time) / calculated_time * 100));
}

void calc_memory_usage(void)
{
    printf("\n\n");
    printf("Память из data_t %ld\n", sizeof(data_t));
    printf("Память, занимаемая очередью на статическом массиве: %ld\n\n", sizeof(arr_queue_t));
    for (size_t i = 100; i <= 2000; i += 500)
    {
        printf("Память, занимаемая очередью на списке размером %zu элементов: %ld\n", i, sizeof(list_queue_t) + i * sizeof(node_t));
        if (i == 100)
            i = 0;
    }
}

// Функция запускает симуляцию работы ОА без вывода
// Реализация очереди на списке
void run_simulation_list_queue_test(void)
{
    // Инициализируем функцию srand от unix времени
    srand(time(NULL));
    // Инициализируем переменные
    struct timespec start, end;
    size_t entered = 0, left = 0, work_time = 0;
    float current_time = 0.0f, total_idle_time = 0.0f; // Текущее время и время простоя
    float next_arrival_time = 0.0f;                    // Время прибытия следующей заявки
    float state = 0.0f;

    // Создание очереди
    list_queue_t queue = { 0 };
    list_queue_init(&queue);

    // Запуск времени
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    while (left < (size_t)MAX_REQUEST_COUNT || entered < MAX_REQUEST_COUNT)
    {
        while (current_time > next_arrival_time)
        {
            // Расчитываем время
            next_arrival_time += random_float(T1_LOWER, T1_UPPER);
            if (list_queue_is_empty(queue) && next_arrival_time > current_time)
            {
                total_idle_time += next_arrival_time - current_time;
                current_time = next_arrival_time;
            }
            entered++;
            data_t request = { .request_data = { .arrival_time = next_arrival_time, .processing_count = 0 } };
            list_queue_push(&queue, &request, sizeof(data_t));
        }

        state += queue.count;
        work_time++;
        current_time += random_float(T2_LOWER, T2_UPPER);

        // Берем элемент из очереди
        data_t request = { 0 };
        list_queue_pop(&queue, &request, sizeof(data_t));

        // Обновляем данные запроса и возвращаем обратно в очередь
        if (request.request_data.processing_count < MAX_CYCLES)
        {
            request.request_data.processing_count++;
            request.request_data.arrival_time = current_time;
            // Возвращается в конец очереди
            list_queue_push(&queue, &request, sizeof(data_t));
        }
        else
        {
            // Если элемент прошел больше 5 циклов, то он выходит из очереди
            left++;
        }
    }

    // Вычисление замера времени
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    float exp_time = (float)((end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3);

    // Вывод времени и погрешности
    printf("\nВошло %zu Время моделирования УЕ: %.2f Время моделирования МКС %.2f\n",
           entered, exp_time, current_time);

    list_queue_free(&queue);
}
