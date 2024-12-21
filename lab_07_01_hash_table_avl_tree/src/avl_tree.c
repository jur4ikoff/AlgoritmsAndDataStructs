#include "avl_tree.h"
#include "constants.h"
#include "errors.h"
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include "menu.h"
#include <stdlib.h>

struct _avl_tree_type
{
    int a;
};

void test_binary_tree(void)
{
    // Инициализация переменных
    printf("Подпрограмма для тестирования бинарного дерева\n");
    int test_itteration_count = 0; // rc = ERR_OK;
    tree_test_menu_t test_operation = TEST_TREE_COUNT;
    // struct timespec start, end;
    avl_tree_t *tree = NULL;
    // bool is_first = 1;

    // Запуск главного цикла
    while (test_operation != TEST_TREE_EXIT)
    {
        // Раз в 4 иттерации выводим меню
        if (test_itteration_count % 4 == 0)
        {
            print_test_tree_menu();
        }
        test_itteration_count++;
        // Ввод операции
        test_operation = input_test_tree_operation();
        if (test_operation == TEST_TREE_EXIT)
        {
            // Тестовая операция выход
            printf("%sУспешный выход из режима тестирования\n%s", GREEN, RESET);
            goto exit;
        }
        else if (test_operation == TEST_TREE_LOAD)
        {
            /*
            char *string_to_convert = malloc(MAX_STRING_LEN * sizeof(char));
            printf("Введите строку для записи в дерево: ");
            fgets(string_to_convert, MAX_STRING_LEN - 1, stdin);

            char *newline = strchr(string_to_convert, '\n');
            if (newline)
                *newline = 0;

            // convert_string_to_bin_tree(&tree, string_to_convert);
            is_first = 0;
            free(string_to_convert);*/
        }
        else if (test_operation == TEST_TREE_SHOW)
        {
            // if (bin_tree_in_picture(tree) != ERR_OK)
            //     printf("%sОшибка при открытии файла\n%s", YELLOW, RESET);
        }
        else if (test_operation == TEST_TREE_ADD)
        {
            /*data_t data = {0};
            if (input_data(&data, "Введите один символ для добавления в дерево:") != ERR_OK)
            {
                printf("%sОшибка ввода данных%s\n", YELLOW, RESET);
                continue;
            }

            // Если первый, то создаем дерево, иначе вставляем в нужное место
            if (is_first)
            {
                clock_gettime(CLOCK_MONOTONIC_RAW, &start);
                tree = bin_tree_create_node(data);
                is_first = 0;
                clock_gettime(CLOCK_MONOTONIC_RAW, &end);
                float time = (end.tv_sec - start.tv_sec) * 1e6f + (end.tv_nsec - start.tv_nsec) / 1e3f;
                printf("%sДобавлен элемент %c в дерево. Время добавления: %.2f мкс%s\n", GREEN, data.value, time, RESET);
        }
        else
        {
            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
            if (bin_tree_insert(&tree, data) != ERR_OK)
            {
                printf("%sОшибка при добавлении элемента%s\n", YELLOW, RESET);
                clock_gettime(CLOCK_MONOTONIC_RAW, &end);
            }
            else
            {
                clock_gettime(CLOCK_MONOTONIC_RAW, &end);
                float time = (end.tv_sec - start.tv_sec) * 1e6f + (end.tv_nsec - start.tv_nsec) / 1e3f;
                printf("%sДобавлен элемент %c в дерево. Время добавления: %.2f мкс%s\n", GREEN, data.value, time, RESET);*/
        }
        else if (test_operation == TEST_TREE_REMOVE)
        {
            // Удаление из дерева
            /*data_t data = {0};
            if (input_data(&data, "Введите один символ для удаления из дерева:") != ERR_OK)
            {
                printf("%sОшибка ввода данных%s\n", YELLOW, RESET);
                continue;
            }

            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
            if ((rc = bin_tree_remove(&tree, data)) != ERR_OK)
            {
                print_warning_message(rc);
                clock_gettime(CLOCK_MONOTONIC_RAW, &end);
            }
            else
            {
                clock_gettime(CLOCK_MONOTONIC_RAW, &end);
                float time = (end.tv_sec - start.tv_sec) * 1e6f + (end.tv_nsec - start.tv_nsec) / 1e3f;
                printf("%sУдален элемент %c из дерева. Время удаления: %.2f%s\n", GREEN, data.value, time, RESET);
            }*/
        }
        else if (test_operation == TEST_TREE_SEARCH)
        {
            /* data_t data = {0};
             if (input_data(&data, "Введите один символ для поиска в дереве:") != ERR_OK)
             {
                 printf("%sОшибка ввода данных%s\n", YELLOW, RESET);
                 continue;
             }

             clock_gettime(CLOCK_MONOTONIC_RAW, &start);
             bst_tree_t *node = bin_tree_search(tree, data);
             clock_gettime(CLOCK_MONOTONIC_RAW, &end);
             float time = (end.tv_sec - start.tv_sec) * 1e6f + (end.tv_nsec - start.tv_nsec) / 1e3f;

             if (node)
             {
                 printf("%sЭлемент найден. Время поиска: %.2f%s\n", GREEN, time, RESET);
                 bin_tree_inorder_traversal(tree, 1, 1);
                 bin_tree_in_picture(tree);
                 bin_tree_search_reset(tree);
             }
             else
             {
                 printf("%sЭлемент не найден%s\n", YELLOW, RESET);
             }*/
        }
        else if (test_operation == TEST_TREE_SHOW)
        {
            // Вывод дерева на экран
            // bin_tree_in_picture(tree);
        }
        else if (test_operation == TEST_TREE_INORDER)
        {
            // Инфиксный обход
            // bin_tree_inorder_traversal(tree, 1, 0);
        }
        else if (test_operation == TEST_TREE_STATS)
        {
            // Статистика о дереве
            // printf("Дерево занимает в памяти %zu байт\n", bin_tree_calc_memory(tree));
            // printf("Среднее количество сравнений %.3f\n", bin_tree_calc_avg_compare(tree));
        }
        else if (test_operation == TEST_TREE_UNKNOWN)
        {
            // Операция неизвестна
            // printf("%sНеизвестная операция\n%s", YELLOW, RESET);
        }
        else if (test_operation == TEST_TREE_ERROR)
        {
            // printf("%sВыбор неверной операции%s\n", RED, RESET);
            goto exit;
        }
    }
exit:
    printf("1\n");
    // tree_free(tree);
}
