#include "utils.h"
#include <string.h>
#include <assert.h>

// Получение порядка целочисленного числа
int int_len(long long value)
{
    int count = 0;
    while (value > 0)
    {
        count++;
        value /= 10;
    }

    return count;
}

// Вывод экранной линейки
void print_line(void)
{
    printf(">>----|----1----|----2----|----3----|----4\n");
}

/**
 * @brief Ввод строки из stdin
 */
int input_string(char *string)
{
    if (!fgets(string, MAX_STRING_LEN, stdin))
        return ERR_INPUT;

    char *newline = strchr(string, '\n');
    if (!newline)
        return ERR_OVERFLOW;

    *newline = 0;

    if (strlen(string) < 1)
        return ERR_EMPTY_INPUT;
    return ERR_OK;
}

// Функция подсчитывает количество символов в строке
size_t count_symbols(char *string)
{
    size_t count = 0;
    while (*string)
    {
        count++;
        string++;
    }

    return count;
}

// Функция считает количество символов в строке равных символу c
size_t count_eq_symbols(char *string, char c)
{
    size_t count = 0;
    char *ptr = string;
    while (*ptr != 0)
    {
        if (*ptr == c)
            count++;

        ptr++;
    }

    return count;
}

// Функция меняет местами 2 симвала в строке
void swap(char *string, size_t index1, size_t index2)
{
    char buffer = string[index1];
    string[index1] = string[index2];
    string[index2] = buffer;
}

void copy_to_struct(long long value, long_number *dest)
{
    // printf("%lld\n", value);
    dest->order = 0, dest->mantise_size = 0;
    char buffer[MAX_STRING_LEN];
    snprintf(buffer, sizeof(buffer), "%lld", value);

    for (size_t i = 0; i < (size_t)int_len(value); i++)
    {
        dest->mantise[dest->mantise_size] = buffer[i] - '0';
        dest->mantise_size++;
        dest->order++;
    }
}

void print_number(long_number number)
{

    // printf("mant_size = %hd order = %hd\n", number.mantise_size, number.order);
    if (number.sign == 0)
        printf("-");

    if (number.mantise[0] != 0)
        printf("0.");

    for (int i = 0; i < number.mantise_size; i++)
    {
        // if number.mantise[i] == 0;
        printf("%hd", number.mantise[i]);
    }
    printf("e%hd\n", number.order);
}

void copy_structs(long_number stream, long_number *dest, size_t start, size_t end)
{
    dest->mantise_size = 0;
    for (size_t i = start; i < end; i++)
    {
        if (i < stream.mantise_size)
            dest->mantise[dest->mantise_size] = stream.mantise[i];
        else
            dest->mantise[dest->mantise_size] = 0;

        dest->mantise_size++;
    }
}

void copy_to_variable(long_number number, long long *value, size_t start, size_t end)
{
    if (end > MANTISE_DEFINE)
        end = 0;
    *value = 0;
    for (size_t i = start; i < end; i++)
    {
        if (i < number.mantise_size)
        {
            *value = *value * 10 + number.mantise[i];
        }
        else
            *value *= 10;
    }
}
