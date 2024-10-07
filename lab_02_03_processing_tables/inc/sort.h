#ifndef SORT_H__
#define SORT_H__
#include <stdio.h>
#include "student_operations.h"
#include "table.h"

int compare_surnames(const void *a, const void *b);
void mysort(void *base, size_t number, size_t width, int (*compare)(const void *, const void *));
void print_table_with_keys(students_t *students_arr, table_t *table, size_t count);
#endif
