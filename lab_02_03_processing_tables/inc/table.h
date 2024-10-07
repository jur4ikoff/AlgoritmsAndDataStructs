#ifndef TABLE_T_H
#define TABLE_T_H

#include <stdio.h>
#include "constants.h"
#include "errors.h"
#include "student_operations.h"

typedef struct
{
    size_t index_src;
    size_t index_table;
    char *surname[MAX_STRING_LEN];

} table_t;

void create_key_table(table_t *key_table, students_t *array, size_t count);
void key_table_sort(table_t table[], size_t count);
void key_table_print(table_t *key_table, size_t count);

#endif
