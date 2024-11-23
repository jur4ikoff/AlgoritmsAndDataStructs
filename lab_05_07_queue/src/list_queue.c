#include "list_queue.h"
#include "constants.h"
#include "errors.h"
#include "stdlib.h"

void list_queue_init(list_queue_t *queue)
{
    queue->head = NULL;
    queue->end = NULL;
    queue->UP_LIMIT = MAX_QUEUE_SIZE;
}

void list_queue_allocation(list_queue_t *queue)
{
    (void)queue;
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
}

int list_queue_push(list_queue_t *queue, char element)
{
    if (queue->count >= queue->UP_LIMIT)
    {
        return ERR_QUEUE_OVERFLOW;
    }

    node_t *node = malloc(sizeof(node_t));
    data_t *data = malloc(sizeof(data_t));
    if (!node || !data)
        return ERR_MEMORY_ALLOCATION;

    node->next = NULL;
    node->data = data;

    node->prev = queue->end;
    queue->end = node;
    (void)element;
    return ERR_OK;
}

int list_queue_pop(list_queue_t *queue, char *element)
{
    (void)queue;
    (void)element;
    return ERR_OK;
}

void list_queue_free(list_queue_t *queue)
{
    (void)queue;
}
