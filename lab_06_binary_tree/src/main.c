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

#include "binary_tree.h"
#include "constants.h"
#include "errors.h"
#include "menu.h"
#include "task.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include "time_calc.h"
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
    char *string = NULL;
    operations_t operation = OP_COUNT;
    int itteration_count = 0;
    int is_string = 0;
    int is_tree = 0;
    tree_t *tree = NULL;
    struct timespec start, end;

    while (operation != OP_EXIT && rc == ERR_OK)
    {
        // Раз в 3 запроса выводим меню
        if (itteration_count % 3 == 0)
            print_menu();
        itteration_count++;

        // Принимаем операцию
        printf(">>Введите операцию: ");
        operation = input_operation();

        if (operation == OP_EXIT)
        {
            // Выход из программы
            printf("%sВыход из программы%s\n", GREEN, RESET);
            goto exit;
        }
        else if (operation == OP_TEST_TREE)
        {
            // тестирование дерева
            // Запуск подпрограммы для тестирования дерева
            test_binary_tree();
            itteration_count = 0;
        }
        else if (operation == OP_INPUT_STRING)
        {
            if (is_tree)
            {
                printf("%sОчистка предыдущего дерева\n%s", YELLOW, RESET);
                tree_free(tree);
                free(string);
                string = NULL;
                tree = NULL;
            }
            printf("Введите строку для обработки: ");
            if ((rc = input_line(&string, stdin)) != ERR_OK)
            {
                goto exit;
            }
            is_string = 1;
        }
        else if (operation == OP_BUILD_TREE)
        {
            if (!is_string)
            {
                printf("%sОшибка, сначала нужно ввести строку%s\n", YELLOW, RESET);
                continue;
            }

            convert_string_to_tree(&tree, string);
            if (!tree)
            {
                rc = ERR_MEMORY_ALLOCATION;
                goto exit;
            }
            is_tree = 1;
            printf("Дерево занимает: %zu байт\n", calculate_tree_size(tree));
            tree_in_picture(tree);
        }
        else if (operation == OP_SHOW_TREE)
        {
            if (!is_tree)
            {
                printf("%sОшибка, сначала нужно построить дерево%s\n", YELLOW, RESET);
                continue;
            }
            tree_in_picture(tree);
        }
        else if (operation == OP_CLEAN_TREE)
        {
            if (!is_tree)
            {
                printf("%sОшибка, сначала нужно построить дерево%s\n", YELLOW, RESET);
                continue;
            }
            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
            // tree_delete_repeat(&tree);
            tree_repeat_test(&tree);
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);
            tree_repeat_reset(tree);
            // remove_duplicates(&tree); // Это
            tree_in_picture(tree);

            float time = (end.tv_sec - start.tv_sec) * 1e6f + (end.tv_nsec - start.tv_nsec) / 1e3f;
            printf("%sДубликаты удалены из дерева за %.2f мкс%s\n", GREEN, time, RESET);
        }
        else if (operation == OP_CLEAN_STRING)
        {
            if (!is_string)
            {
                printf("%sОшибка, сначала нужно ввести строку%s\n", YELLOW, RESET);
                continue;
            }

            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
            string_remove_duplicates(string);
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);
            float time = (end.tv_sec - start.tv_sec) * 1e6f + (end.tv_nsec - start.tv_nsec) / 1e3f;
            printf("%sСтрока после очистки: %s. Скорость удаления: %.2f мкс%s\n", GREEN, string, time, RESET);
        }
        else if (operation == OP_PREORDER_TREE)
        {
            if (!is_tree)
            {
                printf("%sДерево пустое%s\n", YELLOW, RESET);
                continue;
            }
            preorder_traversal(tree, 1, 0);
        }
        else if (operation == OP_INORDER_TREE)
        {
            if (!is_tree)
            {
                printf("%sДерево пустое%s\n", YELLOW, RESET);
                continue;
            }
            inorder_traversal(tree, 1, 0);
        }
        else if (operation == OP_POSTORDER_TREE)
        {
            postorder_traversal(tree, 1, 0);
        }
        else if (operation == OP_EFFICIENCY)
        {
            float time_rand_07, time_lin_07, time_lin_15, time_rand_15, time_lin_40, time_rand_40;
            calc_inorder("./data/random_07.txt", &time_rand_07);
            calc_inorder("./data/linear_07.txt", &time_lin_07);

            calc_inorder("./data/random_15.txt", &time_rand_15);
            calc_inorder("./data/linear_15.txt", &time_lin_15);

            calc_inorder("./data/random_40.txt", &time_rand_40);
            calc_inorder("./data/linear_40.txt", &time_lin_40);

            float search_time_rand_07, search_time_lin_07, search_time_rand_15, search_time_lin_15, search_time_rand_40, search_time_lin_40;
            calculte_search_time("./data/random_07.txt", &search_time_rand_07, 20);
            calculte_search_time("./data/linear_07.txt", &search_time_lin_07, 20);
            calculte_search_time("./data/random_15.txt", &search_time_rand_15, 20);
            calculte_search_time("./data/linear_15.txt", &search_time_lin_15, 20);
            calculte_search_time("./data/random_40.txt", &search_time_rand_40, 20);
            calculte_search_time("./data/linear_40.txt", &search_time_lin_40, 20);

            printf(GREEN);
            printf("Время обхода сбалансированного дереве из 7 элементов %.2f на вырожденном дереве %.2f\n", time_rand_07, time_lin_07);
            printf("Время обхода сбалансированного дереве из 15 элементов %.2f на вырожденном дереве %.2f\n", time_rand_15, time_lin_15);
            printf("Время обхода сбалансированного дереве из 40 элементов %.2f на вырожденном дереве %.2f\n", time_rand_40, time_lin_40);
            printf("\n");
            printf("Время поиска в сбалансировванном дереве из 7 элементов %.2f на вырожденном дереве %.2f\n", search_time_rand_07, search_time_lin_07);
            printf("Время поиска в сбалансировванном дереве из 15 элементов %.2f на вырожденном дереве %.2f\n", search_time_rand_15, search_time_lin_15);
            printf("Время поиска в сбалансировванном дереве из 40 элементов %.2f на вырожденном дереве %.2f\n", search_time_rand_40, search_time_lin_40);
            printf(RESET);
        }
        else if (operation == OP_UNKNOWN)
        {
            printf("%sВыбрана неверная операция%s\n", YELLOW, RESET);
        }
    }

exit:
    if (rc)
        print_error_message(rc);
    free(string);
    tree_free(tree);
    return rc;
}
