#ifndef INPUT_H
#define INPUT_H
#include "const.h"
#include "utils.h"

int find_exponent_part(long_number *number, char *string);
int process_real_number(long_number *number, char *string);
int input_real_number(long_number *number);
int sign_defenition(long_number *number, char **string);
int input_int_number(long_number *number);
int checking_for_non_digits(char *string);
void long_number_normalization(long_number *number);

#endif