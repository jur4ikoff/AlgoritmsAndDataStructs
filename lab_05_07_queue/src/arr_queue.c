#include "arr_queue.h"
#include "errors.h"
#include <stdio.h>

int arr_queue_create(arr_queue_t *queue)
{
    queue->size = MAX_QUEUE_SIZE;
    queue->count = 0;
    queue->start = queue->data;
    queue->end = queue->data;
    return ERR_OK;
}




