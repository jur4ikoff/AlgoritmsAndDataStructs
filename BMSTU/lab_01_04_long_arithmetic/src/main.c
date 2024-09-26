// Вариант 4
#include "const.h"
#include "long_types.h"
#include "input.h"
#include "utils.h"
#include "string.h"

int main(int argc, char **argv)
{
    // Инициализация переменных
    long_number first_number = {0}, second_number = {0}, answer = {0};
    int rc = ERR_OK;

    // Вывод информации о работе программы
    if (argc == 2)
    {
        if (strcmp(argv[1], "-h") == 0)
        {
            printf("Программа предназначена для деления целого числа на вещественное\n");
            printf("Целое число вводится в привычной форме. При вводе символов или числа в экспонениальной форме, программа выдаст ошибку\n");
            printf("Вещественное число можно ввести в любой форме. Максимальный размер обеих чисел - 40 знаков\n");
        }
    }

    // Ввод первого числа
    if ((rc = input_int_number(&first_number)) != ERR_OK)
    {
        print_error(rc);
        return rc;
    }

    // Ввод второго числа
    if ((rc = input_real_number(&second_number)) != ERR_OK)
    {
        print_error(rc);
        return rc;
    }

    // Проверка - Деление на ноль
    if (second_number.mantise[0] == 0)
    {
        print_error(ERR_DIVISION_ON_ZERO);
        return ERR_DIVISION_ON_ZERO;
    }

    // Вызов функции с делением двух чисел
    if ((rc = long_divisible(first_number, second_number, &answer)) != ERR_OK)
    {
        print_error(rc);
        return rc;
    }

    // Вывод на экран результат работы программы.
    printf("\nResult: ");
    print_number(answer);
    return rc;
}
