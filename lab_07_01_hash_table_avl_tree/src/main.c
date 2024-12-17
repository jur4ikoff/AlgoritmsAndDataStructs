/*
## Задание:
Построить дерево в соответствии со своим вариантом задания.
Вывести его на экран в виде дерева. Реализовать основные операции
работы с деревом: обход дерева, включение, исключение и поиск узлов.
Сравнить эффективность алгоритмов сортировки и поиска в зависимости от высоты деревьев и степени их ветвления.

## Вариант
Построить двоичное дерево поиска из букв вводимой строки. Вывести его на экран в виде
дерева. Выделить цветом все буквы, встречающиеся более одного раза. Удалить из дерева эти
буквы. Вывести оставшиеся элементы дерева при постфиксном его обходе. Сравнить время
удаления повторяющихся букв из дерева и из строки.
*/

#include "bin_search_tree.h"
#include "constants.h"
#include "errors.h"
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

int main(void)
{
    print_info();
    int rc = ERR_OK;
    main_operations_t operation = OP_COUNT;
    while (operation != OP_EXIT && rc == ERR_OK)
    {
        void print_menu(void);
        operation = input_operation();

        if (operation == OP_EXIT)
        {
            printf("%sУспешный выход из программы\n%s");
        }
        else if (operation == OP_UNKNOWN)
        {
            printf("%sВыбрана неверная операция%s\n", YELLOW, RESET);
        }
    }
    return rc;
}
