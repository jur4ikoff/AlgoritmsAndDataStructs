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

// Сортировка вставками
void sort_key_table(table_t *key_table, size_t count)
{
    char key[MAX_SURNAME_LEN], temp[MAX_STRING_LEN];
    for (size_t i = 1; i < count; i++)
    {
        strcpy(key_table[i], key);
        int j = i - 1;
        while (j >= 0 && strcmp(key_table[j], key) > 0)
        {
            if (srcmp(key_table[j], key) > 0)
            {
                j--;
                strcpy(key_table[j + 1], key_table[j]);
            }
            strcpy(key, key_table[j + 1]);
        }
    }
}
