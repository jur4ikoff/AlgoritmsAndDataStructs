#include "utils.h"
#include <string.h>
#include "errors.h"

/**
 * @brief Функция для ввода строки
 */
int input_string(char *string, size_t max_len)
{
    if (!fgets(string, max_len, stdin))
        return ERR_ADD_ORDER_INPUT;

    char *newline = strchr(string, '\n');
    if (!newline)
        return ERR_ADD_ORDER_STRING_OVERFLOW;
    *newline = 0;

    if (strlen(string) < 1)
        return ERR_ADD_ORDER_INPUT;
    return ERR_OK;
}

/**
 * @brief Функция меняет местами элементы массива
 */
void swap(students_t *students, size_t index1, size_t index2, size_t count)
{
    students_t temp = students[index1];
    students[index1] = students[index2];
    students[index2] = temp;
}

void delete_from_array(students_t *array, size_t index_to_delete, size_t *count)
{
    for (size_t i = index_to_delete; i < *count - 1; i++)
    {
        swap(array, i, i + 1, *count);
    }
    (*count)--;
}
