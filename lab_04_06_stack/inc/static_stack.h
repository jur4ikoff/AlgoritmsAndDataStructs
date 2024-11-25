#ifndef STATIC_STACK_H__
#define STATIC_STACK_H__
#include <stdio.h>
#include "constants.h"

typedef struct
{
    int top;
    char data[MAX_STACK_SIZE];
} static_stack_t;

void static_stack_init(static_stack_t *stack);
int static_stack_push(static_stack_t *stack, char element);
char static_stack_pop(static_stack_t *stack, int *rc);
void static_stack_print(const static_stack_t stack);
int static_stack_is_palindrome(char *string);
#endif
