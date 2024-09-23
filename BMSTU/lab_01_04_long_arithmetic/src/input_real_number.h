#ifndef INPUT_NUMB_H
#define INPUT_NUMB_H
#include "const.h"
#include "ctype.h"
#include "utils.h"
#include "stdbool.h"
#include "input_int_number.h"

int find_exponent_part(long_number *number, char *string);
int process_real_number(long_number *number, char *string);
int input_real_number(long_number *number);
#endif
