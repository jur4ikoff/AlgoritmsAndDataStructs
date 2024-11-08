#ifndef __LIST__STACK__H__
#define __LIST__STACK__H__
#include <stdio.h>
#include "constants.h"

typedef struct __node_t
{
    struct __node_t *next;
    void *data;
} node_t;

typedef struct
{
    size_t count;
    node_t *top;
} list_stack_t;


void list_stack_init(list_stack_t *stack);
int list_stack_push(list_stack_t *stack, const void *element, size_t size);
void list_stack_print_char(const list_stack_t stack);
void list_stack_free(list_stack_t *stack);


#endif
