#include "utils.h"

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

// Вывод линейки
void print_line(void)
{
    printf(">>---------1---------2---------3---------4\n");
}

// Ввод строки
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

void copy(long_number stream, long_number *destination, int start, int end)
{

    for (int i = start; i < end; i++)
    {
        if (i < stream.mantise_size)
        {
            destination->mantise[i] = stream.mantise[i];
            destination->order++;
        }
        else
        {
            destination->mantise[i] = 0;
            destination->order++;
        }
    }
}

int copy_to_number(long long int *value, long_number number, size_t start, size_t end)
{
    if (start > MAX_MANTISE || end > MAX_MANTISE)
        return 1;

    *value = 0;
    // printf("%zu %zu\n", start, end);
    for (size_t i = start; i < end; i++)
    {
        *value = *value * 10 + number.mantise[i];
    }
    return ERR_OK;
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
    printf("mant_size = %hd order = %hd\n", number.mantise_size, number.order);
    if (number.sign == 0)
        printf("-");
    // else
    //      printf("+");
    printf("0.");
    for (int i = 0; i < number.mantise_size; i++)
    {
        // if number.mantise[i] == 0;
        printf("%hd", number.mantise[i]);
    }
    printf("e%hd\n", number.order);
}
