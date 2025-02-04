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
    if (stack->count >= MAX_STACK_SIZE)
        return ERR_STACK_OVERFLOW;
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

int list_stack_pop(list_stack_t *stack, void *element, size_t size)
{
    if (stack->top == NULL)
        return ERR_STACK_EMPTY;

    node_t *node_to_delete = stack->top;

    stack->top = stack->top->next;
    stack->count--;

    if (element)
    {
        memcpy(element, node_to_delete->data, size);
    }

    free(node_to_delete->data);
    free(node_to_delete);

    return ERR_OK;
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

/**
 * @brief Функция определяет является ли содержимое стека паллиндромом
 * @param string Строка для определения
 * @return 0 - Если стек не является паллиндромом, иначе ненулевое значение
 */
int list_stack_is_palindrome(char *string)
{
    list_stack_t stack;
    list_stack_init(&stack);

    for (char *ptr = string; *ptr != 0; ptr++)
    {
        list_stack_push(&stack, ptr, sizeof(*ptr));
    }

    for (char *ptr = string; *ptr != 0; ptr++)
    {
        char element;
        list_stack_pop(&stack, &element, sizeof(element));

        if (*ptr != element)
        {
            list_stack_free(&stack);
            return 0;
        }
    }

    list_stack_free(&stack);
    return 1;
}
