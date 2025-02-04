#include "menu.h"
#include "constants.h"
#include "errors.h"
#include <stdbool.h>
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
    case ERR_HEAD:
        printf("Ошибка при передаче параметров в функцию\n");
    }
    printf("%s", RESET);
}

void print_warning_message(int arg)
{
    printf("%s", YELLOW);
    switch (arg)
    {
    case WARNING_TREE:
        printf("Пустой объект\n");
        break;
    case WARNING_ELEMENT_NOT_FOUND:
        printf("Такого элемента нет в объекте\n");
        break;
    case WARNING_OPERATION:
        printf("Неверный выбор операции\n");
        break;
    case WARNING_REPEAT:
        printf("Элемент существует\n");
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
    printf("\n0 - Выход\n"
           "1 - Тестирование двоичного дерева поиска\n"
           "2 - Тестирование AVL дерева\n"
           "3 - Тестирование хэш таблицы с открытой адресацией\n"
           "4 - Тестирование хэш таблицы с закрытой (цепочной) адресацией\n"
           "5 - Решение задачи\n"
           "6 - Тестирование эффективности\n");
    printf("Введите операцию: ");
}

// Вывод меню для дерева
void print_test_tree_menu(void)
{
    printf("\n0 - Выход\n"
           "1 - Заполнить дерево из строчки\n"
           "2 - Добавить элемент в дерево\n"
           "3 - Удалить элемент из дерева\n"
           "4 - Поиск элемента в дереве\n"
           "5 - Вывод дерева на экран (картинкой)\n"
           "6 - Инфиксный обход дерева\n"
           "7 - Замер памяти и среднего количество сравнений\n");
}

// Вывод меню для хэш таблицы
void print_hash_table_menu(void)
{
    printf("\n0 - Выход\n"
           "1 - Заполнить хэш таблицу из строки\n"
           "2 - Добавить элемент в хэш таблицу\n"
           "3 - Удалить элемент из хэш таблицы\n"
           "4 - Поиск элемента в хэш таблице\n"
           "5 - Вывод на экран хэш таблицы\n"
           "6 - Замер памяти и среднего количества сравнений\n");
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
        return OP_ERROR;
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
    printf(">>Введите тестовую операцию: ");
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
 * @brief Функция принимает у пользователя операцию
 * @return Структурную переменную, обозначающую операцию
 */
hash_test_menu_t input_test_ht_operation(void)
{
    int buffer;
    printf(">>Введите тестовую операцию: ");
    if (scanf("%d", &buffer) != 1)
    {
        while (fgetc(stdin) != '\n')
        {
            continue; // Возврат к началу цикла}
        }
        return TEST_HT_ERROR;
    }

    fgetc(stdin);

    if (buffer < 0 || buffer >= TEST_HT_COUNT)
        return TEST_HT_UNKNOWN;

    return (hash_test_menu_t)buffer;
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

/**
 * @brief Ввод символа и его запись в переменную data_t
 */
int input_data(data_t *data, char *message)
{
    int rc = ERR_OK;
    printf("%s ", message);
    char buffer[MAX_INPUT_DATA_SIZE];

    if ((!fgets(buffer, MAX_INPUT_DATA_SIZE, stdin)))
        return ERR_DATA_INPUT;

    char *newline = strchr(buffer, '\n');
    if (!newline)
        return ERR_DATA_INPUT;

    *newline = 0;

    if (strlen(buffer) != 1)
        return ERR_DATA_INPUT;

    data->value = buffer[0];
    return rc;
}

// Подсчет следующего целого числа
int calc_next_prime(size_t min)
{
    size_t new_num = min + 1;
    while (true)
    {
        bool is_prime = true;
        for (size_t i = 2; is_prime && i < new_num / 2 + 1; i++)
        {
            if (new_num % i == 0)
                is_prime = false;
        }
        if (is_prime)
            return new_num;

        new_num++;
    }
}

int input_string_from_file(char *filename, char *string)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return ERR_FILE;
    }
    fgets(string, MAX_STRING_LEN - 1, file);

    char *newline = strchr(string, '\n');
    if (newline)
        *newline = 0;
    fclose(file);
    return ERR_OK;
}
