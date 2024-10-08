#include "table.h"
#include "student_operations.h"
#include <string.h>
#include "utils.h"

void create_key_table(table_t *key_table, students_t *array, size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        key_table[i].index_src = i;
        key_table[i].surname = &array[i].surname[0];
    }
}

// Сортировка вставками
void key_table_sort(table_t table[], size_t count)
{
    table_t key;
    for (size_t i = 1; i < count; i++)
    {
        key = table[i];
        int j = i - 1;
        while (j >= 0 && strcmp(table[j].surname, key.surname) > 0)
        {
            table[j + 1] = table[j];
            j--;
        }
        table[j + 1] = key;
    }
}

void key_table_print(table_t *key_table, size_t count)
{
    printf("|———|———|————————————————————————|\n");
    printf("|src|tab|         Фамилия        |\n");
    printf("|———|———|————————————————————————|\n");

    // int padding = (3 - (int)strlen(key_table.index)) / 2;
    for (size_t i = 0; i < count; i++)
    {
        printf("|%*s%zu%*s|", 0, "", key_table[i].index_src, 3 - int_len(key_table[i].index_src), "");
        printf("%*s%zu%*s|", 0, "", i, 3 - int_len(i), "");

        int padding = (MAX_SURNAME_LEN - (int)strlen(key_table[i].surname)) / 2;
        printf("%*s%s%*s|\n", padding, "", key_table[i].surname, MAX_SURNAME_LEN - padding - (int)strlen(key_table[i].surname), "");
    }
    printf("|___|___|________________________|\n");
}
