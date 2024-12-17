#include "menu.h"
#include "constants.h"
#include "errors.h"
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
    case ERR_DATA_INPUT:
        printf("Ошибка при вводе данных\n");
        break;
    case ERR_FILE:
        printf("Ошибка при чтении или создании файла\n");
        break;
    }
    printf("%s", RESET);
}

void print_warning_message(int arg)
{
    printf("%s", YELLOW);
    switch (arg)
    {
    case WARNING_TREE:
        printf("Пустое дерево\n");
        break;
    case WARNING_NO_EL:
        printf("Нет такого элемента в дереве\n");
        break;
    }
    printf("%s", RESET);
}

void print_info(void)
{
    printf("Программа стоит двоичное дерево поиска, авл дерево, хеш-таблицу (используя открытую и закрытую адресацию) из чисел файла.\n"
           "Реализованы операции добавления, удаления и поиска введенного числа во всех структурах.\n"
           "Можно сравнить время поиска, объем памяти и количество сравнений при использовании различных структур данных\n");
}

void print_menu(void)
{
    printf("0 - Выход\n"
           "1 - Тестирование двоичного дерева поиска\n"
           "2 - Тестирование AVL дерева\n"
           "3 - Тестирование хэш таблицы с открытой адресацией\n"
           "4 - Тестирование хэш таблицы с открытой адресацией\n"
           "5 - Тестирование эффективности\n");
    printf("Введите операцию: ");
}

/**
 * @brief Функция принимает у пользователя операцию
 * @return Структурную переменную, обозначающую операцию
 */
main_operations_t input_operation(void)
{
    int buffer;
    if (scanf("%d", &buffer) != 1)
    {
        while (fgetc(stdin) != '\n')
        {
            continue;
        }
        return OP_UNKNOWN;
    }

    if (buffer < 0 || buffer >= OP_COUNT)
        return OP_UNKNOWN;

    return (main_operations_t)buffer;
}

/**
 * @brief Функция принимает у пользователя операцию
 * @return Структурную переменную, обозначающую операцию
 */
/*test_menu_t input_test_operation(void)
{
    int buffer;
    if (scanf("%d", &buffer) != 1)
    {
        while (fgetc(stdin) != '\n')
        {
            continue; // Возврат к началу цикла}
        }
        return TEST_UNKNOWN;
    }

    fgetc(stdin);

    if (buffer < 0 || buffer >= TEST_COUNT)
        return TEST_UNKNOWN;

    return (test_menu_t)buffer;
}
*/