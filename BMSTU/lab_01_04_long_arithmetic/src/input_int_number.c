#include "input.h"
#include <ctype.h>

// Определение знака введенного числа
int sign_defenition(long_number *number, char **string)
{
    if (**string == '-')
    {
        number->sign = 0;
        (*string)++;
    }
    else if (**string == '+')
    {
        number->sign = 1;
        (*string)++;
    }
    else if (isdigit(**string) != 0)
        number->sign = 1;
    else
        return ERR_INPUT_CHAR;
    return ERR_OK;
}

/*Функция проверяет строку на наличие нецифроврых символов
0 - Символов нет, иначе - 1*/
int checking_for_non_digits(char *string)
{
    while (*string)
    {
        if (*string < '0' || *string > '9')
            return 1;
        string++;
    }
    return 0;
}

// Функция реализует ввод целого числа в тип данных
int input_int_number(long_number *number)
{
    // Определение переменных
    int rc = ERR_OK;
    char buffer[MAX_STRING_LEN];

    // Приглашение к вводу
    printf(">Input long integer number\n");
    print_line();
    printf(">");

    // Получаем строку с числом
    if ((rc = input_string(buffer)) != ERR_OK)
        return rc;

    // Валидируем ввод
    char *ptr = buffer;
    if ((rc = sign_defenition(number, &ptr)) != ERR_OK)
        return rc;

    // Проверяем на содержание символов
    if ((rc = (checking_for_non_digits(ptr))) != ERR_OK)
        return rc;

    // Запись в структуру
    while (*ptr)
    {
        number->mantise[number->mantise_size] = *ptr - '0';
        number->mantise_size++;
        number->order++;
        ptr++;
    }
    return rc;
}
