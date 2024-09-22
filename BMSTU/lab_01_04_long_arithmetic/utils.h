#ifndef UTILS_H
#define UTILS_H
#include "const.h"

int i_len(long long value);
void copy(number_t stream, number_t *destination, int start, int end);
int copy_to_number(long long int *value, number_t number, size_t start, size_t end);
void copy_to_struct(long long value, number_t *dest);
void print_number(number_t number);
int input_string(char *string);
#endif
