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

#include "avl_tree.h"
#include "bin_search_tree.h"
#include "constants.h"
#include "errors.h"
#include "hash_t_close.h"
#include "hash_t_open.h"
#include "menu.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

size_t g_max_collisions = 4;

int main(void)
{
    print_info();
    int rc = ERR_OK;
    main_operations_t operation = OP_COUNT;
    while (operation != OP_EXIT && rc == ERR_OK)
    {
        print_menu();
        operation = input_operation();
        if (operation == OP_EXIT)
        {
            printf("%sУспешный выход из программы\n%s", GREEN, RESET);
        }
        else if (operation == OP_TEST_BIN_TREE)
        {
            // Тестирование двоичного дерева поиска
            binary_tree_test();
        }
        else if (operation == OP_TEST_AVL_TREE)
        {
            // Тестирование авл дерева
            avl_tree_test();
        }
        else if (operation == OP_TEST_OPEN_HASH)
        {
            // Реализация хэш таблицы с открытой адрессацией
            open_ht_test();
        }
        else if (operation == OP_TEST_CLOSE_HASH)
        {
            // Реализация хэш таблицы с закрытой адрессацией. Метод цепочек
            close_ht_test();
        }
        else if (operation == OP_TASK)
        {
            // Решение задачи
            if ((rc = solve_task()) != ERR_OK)
            {
                print_error_message(rc);
                return rc;
            }
        }
        else if (operation == OP_UNKNOWN)
        {
            printf("%sВыбрана неверная операция%s\n", YELLOW, RESET);
        }
        else if (operation == OP_ERROR)
        {
            rc = ERR_OPERATION;
            print_error_message(rc);
            return rc;
        }
    }
    return rc;
}
