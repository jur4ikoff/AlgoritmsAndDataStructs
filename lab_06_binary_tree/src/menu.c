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
    case WARNING_ELEMENT_NOT_FOUND:
        printf("Нет такого элемента в дереве\n");
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
           "1 - Тестирование дерева\n"
           "2 - Ввести строку для обработки\n"
           "3 - Построить дерево\n"
           "4 - Вывести дерево (картинкой)\n"
           "5 - Очистить дерево от повторяющихся символов\n"
           "6 - Очистить строку от повторяющихся символов\n"
           "7 - Префиксный обход\n"
           "8 - Инфиксный обход\n"
           "9 - Постфиксный обход\n"
           "10 - Тест эффективности\n");
}

void test_menu(void)
{
    printf("0 - Выход\n"
           "1 - Вывод дерева на экран (картинкой)\n"
           "2 - Добавить элемент в дерево\n"
           "3 - Удалить элемент дерева\n"
           "4 - Поиск элемента в дереве\n"
           "5 - Префиксный обход дерева\n"
           "6 - Инфиксный обход дерева\n"
           "7 - Постфикный обход дерева\n");
}

/**
 * @brief Функция принимает у пользователя операцию
 * @return Структурную переменную, обозначающую операцию
 */
operations_t input_operation(void)
{
    int buffer;
    if (scanf("%d", &buffer) != 1)
    {
        while (fgetc(stdin) != '\n')
        {
            continue; // Возврат к началу цикла}
        }
        return OP_UNKNOWN;
    }

    fgetc(stdin);

    if (buffer < 0 || buffer >= OP_COUNT)
        return OP_UNKNOWN;

    return (operations_t)buffer;
}

/**
 * @brief Функция принимает у пользователя операцию
 * @return Структурную переменную, обозначающую операцию
 */
test_menu_t input_test_operation(void)
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
