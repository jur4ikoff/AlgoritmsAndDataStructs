#ifndef CONST_H
#define CONST_H
#include "errors.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include <errno.h>  
#include "math.h"

#define MAX_MANTISE 40
#define MAX_ORDER 5
#define MAX_STRING_LEN 64

typedef struct
{
    short sign;
    short mantise[MAX_MANTISE];
    short mantise_size;
    short order;

} number_t;
#endif
