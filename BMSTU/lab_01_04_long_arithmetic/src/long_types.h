#ifndef LONG_TYPES_H
#define LONG_TYPES_H

#include "const.h"
#include "utils.h"

int long_divisible(long_number divisible, long_number divider, long_number *result);
void copy_from_long_number_to_mantise_t(long_number stream, mantise_t *destination, int start, int end);
int struct_copy(mantise_t stream, mantise_t *destination, size_t start, size_t end);
int equivalent(long long value, mantise_t number);

#endif
