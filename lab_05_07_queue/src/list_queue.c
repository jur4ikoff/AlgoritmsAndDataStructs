#include "list_queue.h"
#include "constants.h"
#include "errors.h"
#include <stdlib.h>
#include <string.h>

void list_queue_init(list_queue_t *queue)
{
    queue->head = NULL;
    queue->end = NULL;
    queue->UP_LIMIT = MAX_QUEUE_SIZE;
    queue->count = 0;
}

void list_queue_print_char(const list_queue_t queue)
{
    node_t *cur = queue.head;
    if (!cur)
    {
        printf("%sОчередь пустая%s\n", YELLOW, RESET);
        return;
    }

    while (cur)
    {
        printf("%c ", cur->data->element);
        cur = cur->next;
    }
    printf("\n");
}

int list_queue_push(list_queue_t *queue, char src)
{
    if (queue->count >= queue->UP_LIMIT)
        return ERR_QUEUE_OVERFLOW;

    node_t *node = malloc(sizeof(node_t));
    data_t *data = malloc(sizeof(data_t));
    if (!node || !data)
    {
        return ERR_MEMORY_ALLOCATION;
        free(node);
        free(data);
    }

    data->element = src;
    node->next = NULL;
    node->prev = NULL;
    node->data = data;

    if (!queue->head)
    {
        queue->head = node;
        queue->end = node;
    }
    else
    {
        queue->end->next = node;
        node->prev = queue->end;
        queue->end = node;
    }
    queue->count++;
    return ERR_OK;
}

int list_queue_pop(list_queue_t *queue, char *element)
{
    if (queue->count <= 0)
        return ERR_QUEUE_UNDERFLOW;

    node_t *next = queue->head;
    *element = next->data->element;
    queue->head = next->next;


    free(next->data);
    free(next);
    queue->count--;
    return ERR_OK;
}

void list_queue_free(list_queue_t *queue)
{
    node_t *cur = queue->head;
    while (cur)
    {
        node_t *tmp = cur->next;
        free(cur->data);
        free(cur);
        cur = tmp;
    }
}
