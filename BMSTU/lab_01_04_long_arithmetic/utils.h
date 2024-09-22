#ifndef UTILS_H
#define UTILS_H
#include "const.h"

int i_len(long long value);
void copy(long_number stream, long_number *destination, int start, int end);
int copy_to_number(long long int *value, long_number number, size_t start, size_t end);
void copy_to_struct(long long value, long_number *dest);
void print_number(long_number number);
int input_string(char *string);
#endif
