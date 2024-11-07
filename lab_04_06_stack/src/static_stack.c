#include "static_stack.h"
#include "errors.h"
#include <string.h>
#include "constants.h"

void static_stack_init(static_stack_t *stack)
{
    memset(stack->data, 0, sizeof(stack->data));
    stack->top = -1;
}

int static_stack_push(static_stack_t *stack, char element)
{
    if (stack->top >= MAX_STACK_SIZE)
        return ERR_STATIC_STACK_OVERFLOW;

    stack->data[++stack->top] = element;
    return ERR_OK;
}

char static_stack_pop(static_stack_t *stack, int *rc)
{
    *rc = ERR_OK;
    if (stack->top < 0)
    {
        *rc = ERR_STATIC_STACK_UNDERFLOW;
        return 0;
    }

    char element = stack->data[stack->top];
    stack->top--;

    return element;
}

void static_stack_print(const static_stack_t stack)
{
    if (stack.top < 0)
    {
        printf("%sСтек пустой%s\n", YELLOW, RESET);
        return;
    }

    for (int i = 0; i < stack.top + 1; i++)
    {
        printf("%c ", stack.data[i]);
    }
    printf("\n");
}

/**
 * @brief Функция определяет является ли содержимое стека паллиндромом
 * @param string Строка для определения
 * @return 0 - Если стек не является паллиндромом, иначе ненулевое значение
 */
int static_stack_is_palindrome(char *string)
{
    char *ptr = NULL;
    static_stack_t stack;
    static_stack_init(&stack);
    for (ptr = string; *ptr != 0; ptr++)
    {
        static_stack_push(&stack, *ptr);
    }

    int rc = 0;
    for (ptr = string; *ptr != 0; ptr++)
    {
        if (static_stack_pop(&stack, &rc) != *ptr)
            return 0;
    }

    return 1;
}
