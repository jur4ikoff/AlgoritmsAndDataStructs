#include "static_stack.h"
#include "errors.h"
#include <string.h>

void static_stack_init(static_stack_t *stack)
{
    memset(stack->data, 0, sizeof(stack->data));
    stack->top = -1;
}

int static_stack_push(static_stack_t *stack, char element)
{
    if (stack->top >= MAX_STACK_SIZE)
        return ERR_STATIC_STACK_OVERFLOW;

    stack->data[stack->top++] = element;
    return ERR_OK;
}

int static_stack_pop(static_stack_t *stack, char *element)
{
    if (stack->top < 0)
        return ERR_STATIC_STACK_UNDERFLOW;

    *element = stack->data[stack->top--];
    return ERR_OK;
}

int static_stack_peek(static_stack_t *stack, char *element)
{
    if (stack->top < 0)
        return ERR_STATIC_STACK_UNDERFLOW;

    *element = stack->data[stack->top];
    return ERR_OK;
}

void print_static_stack(const static_stack_t stack)
{
    for (int i = 0; i < stack.top; i++)
    {
        printf("%c ", stack.data[i]);
    }
    printf("\n");
}