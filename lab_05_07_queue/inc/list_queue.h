#ifndef __LIST_QUEUE__H__
#define __LIST_QUEUE__H__
#include "constants.h"
#include <stdio.h>

typedef struct __list_queue_t
{
    size_t UP_LIMIT; // Максимальное количество элементов
    data_t data; // Данные
    struct __list_queue_t *next;
    struct __list_queue_t *prev;
} list_queue_t;

int list_test(void);
void list_queue_init(list_queue_t *queue);
void list_queue_allocation(list_queue_t *queue);
void list_queue_print_char(const list_queue_t queue);
int list_queue_push(list_queue_t *queue, char element);
int list_queue_pop(list_queue_t *queue, char *element);
#endif
