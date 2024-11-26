#include "arr_queue.h"
#include "errors.h"
#include <stdio.h>

static void move_elements_to_begin(arr_queue_t *queue)
{
    int n = queue->end - queue->start;
    queue->end = queue->data + n;

    for (int i = 0; i < n; i++)
    {
        queue->data[i] = *queue->start;
        queue->start++;
    }
    queue->start = queue->data;
}

int arr_queue_init(arr_queue_t *queue)
{
    queue->UP_LIMIT = MAX_QUEUE_SIZE;
    queue->start = queue->data;
    queue->end = queue->data;
    queue->count = 0;
    return ERR_OK;
}

void arr_queue_print_char(const arr_queue_t queue)
{
    if (queue.start - queue.end == 0)
    {
        printf("%sОчередь пустая%s\n", YELLOW, RESET);
        return;
    }
    data_t *start = queue.start;
    while (start != queue.end)
    {
        printf("%c ", start->element);
        start++;
    }
    printf("\n");
}

int arr_queue_push(arr_queue_t *queue, data_t *element)
{
    if (queue->start > queue->end)
        return ERR_QUEUE_OVERFLOW;

    if (queue->end - queue->start >= (long int)queue->UP_LIMIT)
        return ERR_QUEUE_OVERFLOW;

    if (queue->end == queue->data + queue->UP_LIMIT)
        move_elements_to_begin(queue);

    *queue->end = *element;
    queue->end++;
    queue->count++;
    return ERR_OK;
}

int arr_queue_pop(arr_queue_t *queue, data_t *data)
{
    if (queue->start == queue->end)
        return ERR_QUEUE_UNDERFLOW;

    if (queue->start >= queue->data + queue->UP_LIMIT)
        return ERR_QUEUE_OVERFLOW;

    *data = *queue->start;
    queue->start++;
    queue->count--;
    return ERR_OK;
}

/**
 * @brief Функция проверяет пустая ли очередь
 * @param queue Очередь
 * @return 1 - Пустая, 0 - Не пустая
 */
int arr_queue_is_empty(const arr_queue_t queue)
{
    return queue.count == 0;
}
