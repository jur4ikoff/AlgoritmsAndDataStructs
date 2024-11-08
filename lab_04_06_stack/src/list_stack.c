#include "list_stack.h"
#include "constants.h"
#include "errors.h"
#include <stdlib.h>
#include <string.h>

void list_stack_init(list_stack_t *stack)
{
    stack->top = NULL;
    stack->count = 0;
}

int list_stack_push(list_stack_t *stack, const void *element, size_t size)
{
    int rc = ERR_OK;
    node_t *new_node = malloc(sizeof(node_t));
    new_node->next = NULL;
    void *new_data = malloc(size);

    if (!new_node || !new_data)
    {
        return ERR_MEMORY_ALLOCATION;
        free(new_node);
        free(new_data);
    }

    new_node->data = new_data;
    memcpy(new_node->data, element, size);

    if (stack->top == NULL)
    {
        stack->top = new_node;
    }
    else
    {
        new_node->next = stack->top;
        stack->top = new_node;
    }
    stack->count++;

    return rc;
}

void list_stack_print_char(const list_stack_t stack)
{
    node_t *cur = stack.top;
    if (cur == NULL)
    {
        printf("%sСтек пустой%s\n", YELLOW, RESET);
        return;
    }

    while (cur)
    {
        printf("%c ", *(char *)cur->data);
        cur = cur->next;
    }
    printf("\n");
}

void list_stack_free(list_stack_t *stack)
{
    while (stack->top)
    {
        node_t *node = stack->top;
        stack->top = stack->top->next;
        free(node->data);
        free(node);
    }
}
