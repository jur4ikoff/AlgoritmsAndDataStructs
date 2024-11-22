#ifndef __ARR_QUEUE__H__
#define __ARR_QUEUE__H__
#include "constants.h"
#include <stdio.h>

#define MAX_QUEUE_SIZE 5

typedef struct __arr_queue_t
{
    size_t size;  // Количество элементов всего
    data_t data[MAX_QUEUE_SIZE];
    data_t *start; // Указатель на начало
    data_t *end;   // Указатель на конец
} arr_queue_t;

typedef void (*func_arr_queue_ptr)(data_t *data, void *arg);

int arr_queue_create(arr_queue_t *queue);
void arr_queue_print_char(const arr_queue_t queue);
int arr_queue_push(arr_queue_t *queue, char element);


int arr_test(void);
#endif
