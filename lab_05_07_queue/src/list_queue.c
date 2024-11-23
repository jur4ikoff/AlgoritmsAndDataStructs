#include "list_queue.h"
#include "constants.h"
#include "errors.h"
#include "stdlib.h"

void list_queue_init(list_queue_t *queue)
{
    queue->head = NULL;
    queue->end = NULL;
    queue->UP_LIMIT = MAX_QUEUE_SIZE;
    queue->count = 0;
}

static node_t *create_node(data_t *data, int *rc)
{
    *rc = ERR_OK;
    node_t *node = malloc(sizeof(node_t));
    if (!node)
        *rc = ERR_MEMORY_ALLOCATION;

    node->next = NULL;
    node->prev = NULL;
    node->data = data;

    return node;
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

int list_queue_push(list_queue_t *queue, data_t *data)
{
    if (queue->count >= queue->UP_LIMIT)
        return ERR_QUEUE_OVERFLOW;

    if (!data)
        return ERR_DATA;

    int rc = ERR_OK;
    node_t *node = create_node(data, &rc);
    if (rc)
        return rc;

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
    return rc;
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
