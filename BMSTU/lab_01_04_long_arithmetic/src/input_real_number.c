#include "input.h"
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

// Функция проверяет, является ли символ спецсимволов или буквой
// 1 - Является, иначе 0
int is_symbol(char c)
{
    // Является ли символ буквой
    if (isalpha(c))
        return 1;

    // Проверяем, является ли символ знаком операции
    switch (c)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '=':
    case '<':
    case '>':
    case '&':
    case '|':
    case '^':
    case '!':
        return 1;
    default:
        return 0;
    }
}

// Функция нормализует чило к стандартному виду
void long_number_normalization(long_number *number)
{
    size_t i = 0, shift = 0;
    bool is_start = true;
    // Поиск количества незначащих нулей
    while (i < (size_t)number->mantise_size)
    {
        if (is_start && number->mantise[i] == 0)
            shift++;
        else if (is_start && number->mantise[i] != 0)
            is_start = false;

        i++;
    }

    // Изменение порядка
    number->order -= shift;

    // Удаление незначащих нулей
    for (size_t i = shift; i < (size_t)number->mantise_size; i++)
    {
        number->mantise[i - shift] = number->mantise[i];
    }
    number->mantise_size -= shift;
}

// Поиск экспоненциальной части числа
int find_exponent_part(long_number *number, char *string)
{
    size_t len = strlen(string);
    for (size_t i = 0; i < len; i++)
    {
        if (is_symbol(string[i]) != 0)
        {
            if (string[i] == 'e' || string[i] == 'E')
            {
                char *ptr = string + i + 1;
                if (*ptr == 0)
                    return ERR_ORDER_CHAR;

                errno = 0;
                char *endptr;
                int value = (int)strtol(ptr, &endptr, 10);

                if (errno == ERANGE || *endptr != '\0')
                    return ERR_INPUT_CHAR;

                if (abs((int)value) > MAX_ORDER)
                    return ERR_ORDER_SIZE;
                number->order = value;

                ptr = string + i;
                *ptr = '\0';

                return ERR_OK;
            }
            else
                return ERR_INPUT_CHAR;
        }
    }

    return ERR_OK;
}

// Запись числа в структуру
int process_real_number(long_number *number, char *string)
{
    size_t len = strlen(string);
    bool is_start = true;

    for (size_t i = 0; i < len; i++)
    {
        if (number->mantise_size > MAX_MANTISE)
            return ERR_MANTISE_SIZE;

        if (string[i] != '.')
        {
            if (string[i] != '0')
            {
                is_start = false;
            }
            if (!is_start)
            {
                number->mantise[number->mantise_size] = string[i] - '0';
                number->mantise_size++;
                number->order++;
            }
        }
        else
        {
            char *ptr = string + i + 1;
            while (*ptr != 0)
            {
                if (string[i] != '0')
                {
                    is_start = false;
                }
                if (!is_start)
                {
                    number->mantise[number->mantise_size] = *ptr - '0';
                    number->mantise_size++;
                }
                ptr++;
            }
            return ERR_OK;
        }
    }

    return ERR_OK;
}

int input_real_number(long_number *number)
{
    // Определение переменных
    int rc = ERR_OK;
    char buffer[MAX_STRING_LEN];

    // Приглашение к вводу
    printf(">Input long real number\n");
    print_line();
    printf(">");

    // Получаем строку с числом
    if ((rc = input_string(buffer)) != ERR_OK)
        return rc;

    char *ptr = buffer;

    // Определение знака
    if ((rc = sign_defenition(number, &ptr)) != ERR_OK)
    {
        if (*ptr == '.')
        {
            number->sign = 1;
            ptr++;
        }
        else
            return rc;
    }

    // Проверка на то что число существует
    int point_count = count_eq_symbols(ptr, '.');
    if (point_count > 1)
        return ERR_POINTS_COUNT;
    if (count_symbols(ptr) == 0)
        return ERR_EMPTY_INPUT;

    // Поиск части, стоящей за экспонентой и ее обработка
    if ((rc = find_exponent_part(number, ptr)) != ERR_OK)
        return rc;

    if (count_symbols(ptr) > MAX_MANTISE)
        return ERR_OVERFLOW;

    // Обработка мантисы
    if ((rc = process_real_number(number, ptr)) != ERR_OK)
        return rc;

    
    // Нормализация числа
    long_number_normalization(number);
    return rc;
}
