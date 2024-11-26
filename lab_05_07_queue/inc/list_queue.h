#ifndef __LIST_QUEUE__H__
#define __LIST_QUEUE__H__
#include "constants.h"
#include <stdio.h>

typedef struct __node_t
{
    data_t *data; // Данные
    struct __node_t *next;
} node_t;

typedef struct __list_queue_t
{
    node_t *head; // Указатель на начало
    node_t *end;  // Указатель на конец

    size_t UP_LIMIT; // Максимальное количество элементов
    size_t count;    // Текущее количество элементов
} list_queue_t;

int list_test(void);
void list_queue_init(list_queue_t *queue);
void list_queue_print_char(const list_queue_t queue);
int list_queue_push(list_queue_t *queue, const void *src_data, size_t src_size);
int list_queue_pop(list_queue_t *queue, void *dst_data, size_t src_size);
void list_queue_free(list_queue_t *queue);
int list_queue_is_empty(const list_queue_t queue);
#endif
