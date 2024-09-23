#ifndef LONG_TYPES_H
#define LONG_TYPES_H

#include "const.h"
#include "utils.h"

int long_divisible(long_number divisible, long_number divider, long_number *result);
void copy_to_part_divisible(long_number stream, mantise_t *destination, int start, int end);

#endif
