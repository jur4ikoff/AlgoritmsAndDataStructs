#ifndef __ARR_QUEUE__H__
#define __ARR_QUEUE__H__
#include "constants.h"
#include <stdio.h>

typedef struct __arr_queue_t
{
    size_t UP_LIMIT; // Максимальное количество элементов
    size_t count; // Количество элементов
    data_t data[MAX_QUEUE_SIZE];
    data_t *start; // Указатель на начало
    data_t *end;   // Указатель на конец
} arr_queue_t;

int arr_queue_init(arr_queue_t *queue);
void arr_queue_print_char(const arr_queue_t queue);
int arr_queue_push(arr_queue_t *queue, data_t *element);
int arr_queue_pop(arr_queue_t *queue, data_t *element);
int arr_queue_is_empty(const arr_queue_t);
int arr_test(void);
#endif
