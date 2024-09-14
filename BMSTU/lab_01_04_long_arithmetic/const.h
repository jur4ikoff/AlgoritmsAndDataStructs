#ifndef CONST_H
#define CONST_H
#include "errors.h"
#include "stdio.h"
#include "string.h"

#define MAX_MANTISE 40
#define MAX_ORDER 5

typedef struct
{
    short sign;
    char mantise[MAX_MANTISE];
    short order;

} number_t;
#endif