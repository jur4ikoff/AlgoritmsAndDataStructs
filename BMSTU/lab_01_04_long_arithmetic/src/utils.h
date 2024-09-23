#ifndef UTILS_H
#define UTILS_H
#include "const.h"
#include "long_types.h"

int int_len(long long value);
void print_mantise_t(mantise_t number);
int copy_to_number(long long int *value, long_number number, size_t start, size_t end);
void copy_to_struct(long long value, long_number *dest);
void print_number(long_number number);
int input_string(char *string);
void print_line(void);
size_t count_symbols(char *string);
size_t count_eq_symbols(char *string, char c);
void swap(char *string, size_t index1, size_t index2);
#endif
