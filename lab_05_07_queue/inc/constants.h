#ifndef __CONST__H__
#define __CONST__H__

#define MAX_STRING_SIZE 128
#define MAX_QUEUE_SIZE 10000

#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"

#include <stdio.h>

typedef struct __request_t
{
    size_t processing_count;
    float arrival_time;
} request_t;

typedef struct __data_t
{
    request_t request_data;
    char element;
} data_t;
#endif
