#ifndef CONSTANTS_H__
#define CONSTANTS_H__

// Определение кодов для цветного принта
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"

#define MAX_INPUT_DATA_SIZE 3

typedef struct _data_type_
{
    char value;
    int repeat;
} data_t;

#define MAX_STRING_LEN 2000
#define HT_INIT_SIZE 1

#endif
