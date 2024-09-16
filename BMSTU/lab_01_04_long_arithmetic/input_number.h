#ifndef INPUT_NUMB_H
#define INPUT_NUMB_H
#include "const.h"
#include "ctype.h"

int find_exp(number_t *number, char *string);
int count_symbols(char *string, char c);
int process_number(number_t *number, char *string);

#endif
