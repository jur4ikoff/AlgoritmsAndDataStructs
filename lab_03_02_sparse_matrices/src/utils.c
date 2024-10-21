#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "errors.h"
#include "constants.h"
#include "utils.h"

/*
// Получение длины целочисленного числа
int int_len(long long value)
{
    int count = 0;

    if (value == 0)
        return 1;

    while (value > 0)
    {
        count++;
        value /= 10;
    }

    return count;
}
*/

/**
 * @brief Функция для ввода строки
 */
int input_string(char *string, size_t max_len, char *message)
{
    printf("%s", message);
    if (!fgets(string, max_len, stdin))
        return ERR_INPUT_STRING;

    char *newline = strchr(string, '\n');
    if (!newline)
        return ERR_STRING_OVERFLOW;
    *newline = 0;

    if (strlen(string) < 1)
        return ERR_EMPTY_STRING;
    return ERR_OK;
}

/**
 * @brief Функция для вычисления вероятности
 */
bool random_chance(int percentage)
{

    if (percentage <= 0)
        return false;
    if (percentage >= 100)
        return true;

    int random_value = rand() % 100;
    return random_value < percentage;
}

/**
 * @brief Функция реализует ввод целого числа от пользователя
 */
int input_integer(int *number, char* message, int low_edge, int max_edge)
{
    printf("%s", message);
    if (scanf("%d", number) != 1)
        return ERR_INPUT_INTEGER_NUMBER;
    fgetc(stdin);
    
    if (*number < low_edge || *number > max_edge)
        return ERR_INPUT_INTEGER_NUMBER_RANGE;
    
    return ERR_OK;

}

/**
 * @brief Функция меняет местами элементы массива

static void swap(students_t *students, size_t index1, size_t index2)
{
    students_t temp = students[index1];
    students[index1] = students[index2];
    students[index2] = temp;
}*/

/**
 * @brief Функция удаяет элемент из массива по индексу

void delete_from_array(students_t *array, size_t index_to_delete, size_t *count)
{
    for (size_t i = index_to_delete; i < *count - 1; i++)
    {
        swap(array, i, i + 1);
    }
    (*count)--;
}*/