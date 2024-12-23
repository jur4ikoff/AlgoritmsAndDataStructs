#ifndef LINKED_LIST_H__
#define LINKED_LIST_H__

#include "errors.h"
#include "constants.h"
#include <stddef.h>

typedef struct _linked_list_node_ list_t;

struct _linked_list_node_
{
    data_t *data;
    list_t *next;
};

list_t *list_node_create(void);

typedef void (*list_func_t)(list_t *node, void *param);

void list_free(list_t **head);
void list_free_without_data(list_t **head);

int list_push_back(list_t **head, data_t *data);

void list_apply(list_t *head, list_func_t func, void *arg);

const list_t *list_search_by_key(const list_t *head, data_t *data, size_t *cmp);

int list_remove_by_key(list_t **head, data_t *data);

size_t list_size(const list_t *head);
void list_print(const list_t *list);

#endif