#ifndef __CONST__H__
#define __CONST__H__
#include <stdio.h>

#define MAX_STRING_SIZE 128

#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"

typedef struct __request_t
{
    size_t processing_count;
    float arival_time;
    float service_time;
} request_t;

typedef struct __data_t
{
    char element;
    request_t request_data;
} data_t;
#endif
