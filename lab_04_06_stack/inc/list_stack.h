#ifndef __LIST__STACK__H__
#define __LIST__STACK__H__
#include <stdio.h>
#include "constants.h"

typedef struct
{
    list_stack_t *next = NULL;
    void *data;
} list_stack_t;

#endif
