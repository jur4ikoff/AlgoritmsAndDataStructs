#ifndef INPUT_INT_H
#define INPUT_INT_H
#include "const.h"
#include "input_real_number.h"
#include "utils.h"

int sign_defenition(long_number *number, char **string);
int input_int_number(long_number *number);
int checking_for_non_digits(char *string);
void long_number_normalization(long_number *number);

#endif