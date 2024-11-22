#include "list_queue.h"
#include "constants.h"
#include "errors.h"

void list_queue_init(list_queue_t *queue)
{
    queue->prev = NULL;
    queue->next = NULL;
    queue->UP_LIMIT = MAX_QUEUE_SIZE;
}

void list_queue_allocation(list_queue_t *queue)
{
}

void list_queue_print_char(const list_queue_t queue)
{
    if (!queue.next)
    {
        printf("%sОчередь пустая%s\n", YELLOW, RESET);
        return;
    }

    list_queue_t *current = queue;
    while (current)
    {
        printf("%c ", queue.data.element);
        current = current->next;
    }
}

int list_queue_push(list_queue_t *queue, char element)
{
    (void)queue;
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
}
