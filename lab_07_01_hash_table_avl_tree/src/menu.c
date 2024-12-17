#include "menu.h"
#include "constants.h"
#include "errors.h"
#include <stdio.h>
#include <string.h>

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

void print_test_tree_menu(void)
{
    printf("0 - Выход\n"
    "1 - Заполнить дерево из строчки\n"
    "2 - Добавить элемент в дерево\n"
    "3 - Удалить элемент из дерева\n"
    "4 - Поиск элемента в дереве\n"
    "5 - Вывод дерева на экран (картинкой)\n"
    "6 - Инфиксный обход дерева\n"
    "7 - Измеренее эффективности\n");
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
tree_test_menu_t input_test_tree_operation(void)
{
    int buffer;
    if (scanf("%d", &buffer) != 1)
    {
        while (fgetc(stdin) != '\n')
        {
            continue; // Возврат к началу цикла}
        }
        return TEST_TREE_ERROR;
    }

    fgetc(stdin);

    if (buffer < 0 || buffer >= TEST_TREE_COUNT)
        return TEST_TREE_UNKNOWN;

    return (tree_test_menu_t)buffer;
}

/**
 * @brief Функция для записи строки в переменную. Функция автоматически выделяет память под строку
 * @param string Указатель на строку
 * @param file Указатель на файловую переменную
 * @return Код возврата
 */
int input_line(char **string, FILE *file)
{
    ssize_t read = 0;
    size_t len = 0;

    if ((read = getline(string, &len, file)) == -1)
        return ERR_STRING;

    if (read > MAX_STRING_LEN)
        return ERR_STRING;

    char *newline = strchr(*string, '\n');
    if (!newline)
        return ERR_STRING;

    *newline = 0;
    return ERR_OK;
}
