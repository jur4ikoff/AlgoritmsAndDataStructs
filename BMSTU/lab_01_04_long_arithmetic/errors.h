#ifndef ERR_H
#define ERR_H
#include "const.h"

#define ERR_OK 0
#define ERR_INPUT_CHAR 1
#define ERR_MANTISE_SIZE 2
#define ERR_ORDER_SIZE 3
#define ERR_OVERFLOW 4
#define ERR_INPUT 5
#define ERR_NOT_FLOAT 6
#define ERR_ORDER_CHAR 7
#define ERR_POINTS_COUNT 8
#define ERR_EMPTY_INPUT 9

void print_error(int arg);
#endif
