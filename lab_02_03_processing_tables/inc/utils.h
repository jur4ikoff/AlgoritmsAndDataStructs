#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include "student_operations.h"

int int_len(long long value);
int input_string(char *string, size_t max_len);
void delete_from_array(students_t *array, size_t index_to_delete, size_t *count);
#endif
