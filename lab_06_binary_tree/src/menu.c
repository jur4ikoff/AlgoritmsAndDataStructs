#include "menu.h"
#include "errors.h"
#include "constants.h"
#include <stdio.h>

void print_error_message(int arg)
{
    printf("%s", RED);
    switch (arg)
    {
    case ERR_STRING:
        printf("Ошибка в введенной строке\n");
        break;
    case ERR_OPERATION:
        printf("Выбрана неверная операция\n");
        break;
    case ERR_MEMORY_ALLOCATION:
        printf("Ошибка выделения памяти\n");
        break;
    }
    printf("%s", RESET);
}

void print_info(void)
{
    printf("Программа строит бинарное дерево из символов введенной строки, а после этого удаляет повторяющиеся символы\n");
}

void print_menu(void)
{
    printf("0 - Выход\n"
           "1 - Ввести строку для работы с ней\n"
           "2 - Построить дерево\n"
           "3 - Очистить дерево от повторяющихся символов\n"
           "4 - Очистить строку от повторяющихся символов\n"
           "5 - Вывести оставшиеся элементы дерева при постфиксном его обходе\n"
           "6 - Сравнение эффективности\n");
}

/**
 * @brief Функция принимает у пользователя операцию
 * @return Структурную переменную, обозначающую операцию
 */
operations_t input_operation(void)
{
    int buffer;
    if (scanf("%d", &buffer) != 1)
        return OP_UNKNOWN;

    fgetc(stdin);

    if (buffer < 0 || buffer >= OP_COUNT)
        return OP_UNKNOWN;

    return (operations_t)buffer;
}
