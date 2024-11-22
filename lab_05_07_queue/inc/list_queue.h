#ifndef __ARR_QUEUE__H__
#define __ARR_QUEUE__H__
#include "constants.h"
#include <stdio.h>

typedef struct __list_queue_t
{
    size_t size; // Максимальное количество элементов
    data_t data; // Данные
    struct __list_queue_t *next;
    struct __list_queue_t *prev;
} list_queue_t;

int arr_test(void);
#endif
