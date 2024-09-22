#ifndef CONST_H
#define CONST_H
#include "errors.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include <errno.h>
#include "math.h"
#include "stdbool.h"

#define MAX_MANTISE 40
#define MANTISE_DEFINE 60
#define MAX_ORDER 10000
#define MAX_STRING_LEN 64
#define ERR_EPS = 10e-40

typedef struct
{
    unsigned short sign; // 0 - минус, 1 - плюс
    short mantise_size;
    short mantise[MANTISE_DEFINE];
    short order;

} long_number;

#endif
