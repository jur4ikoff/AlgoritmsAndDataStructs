#include "table.h"
#include "student_operations.h"

void create_key_table(table_t *key_table, students_t *array, size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        key_table[i].index_src = i;
        key_table[i].index_table = i;
        strcpy(key_table[i].surname, array[i].surname);
    }
}

void sort_key_table(table_t *key_table, size_t count)
{
    for (size_t i = 0)
}