#ifndef INPUT_NUMB_H
#define INPUT_NUMB_H
#include "const.h"
#include "ctype.h"
#include "utils.h"
#include "stdbool.h"
#include "input_int_number.h"

int find_exp(long_number *number, char *string);
int count_symbols(char *string, char c);
int process_number(long_number *number, char *string);
int validate_number(long_number number);
int input_number(long_number *number, char *message);
#endif
