#ifndef INPUT_NUMB_H
#define INPUT_NUMB_H
#include "const.h"
#include "ctype.h"
#include "stdbool.h"

int find_exp(number_t *number, char *string);
int count_symbols(char *string, char c);
int process_number(number_t *number, char *string);
int validate_number(number_t number);
void check_sign(number_t *number, char **string);

#endif
