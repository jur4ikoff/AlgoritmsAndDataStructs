#include "test.h"
#include "binary_tree.h"
#include "constants.h"
#include "errors.h"
#include "menu.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_INPUT_DATA_STRING_SIZE 5

static int input_data(data_t *data, char *message)
{
    int rc = ERR_OK;
    printf("%s ", message);
    char buffer[MAX_INPUT_DATA_STRING_SIZE];

    if ((!fgets(buffer, MAX_INPUT_DATA_STRING_SIZE, stdin)))
        return ERR_DATA_INPUT;

    char *newline = strchr(buffer, '\n');
    if (!newline)
        return ERR_DATA_INPUT;

    *newline = 0;

    if (strlen(buffer) != 1)
        return ERR_DATA_INPUT;

    *data = buffer[0];
    return rc;
}

void test_binary_tree(void)
{
    // Инициализация переменных
    printf("Подпрограмма для тестирования бинарного дерева\n");
    int test_itteration_count = 0, rc = ERR_OK;
    test_menu_t test_operation = TEST_COUNT;
    struct timespec start, end;

    tree_t *tree = NULL;
    int is_first = 1;

    // Запуск главного цикла
    while (test_operation != TEST_EXIT)
    {
        // Раз в 3 иттерации выводим меню
        if (test_itteration_count % 4 == 0)
        {
            test_menu();
        }
        test_itteration_count++;

        // Ввод операции
        printf(">>Введите тестовую операцию: ");
        test_operation = input_test_operation();
        if (test_operation == TEST_EXIT)
        {
            printf("%sУспешный выход из режима тестирования\n%s", GREEN, RESET);
            goto exit;
        }
        else if (test_operation == TEST_SHOW)
        {
            if (tree_in_picture(tree) != ERR_OK)
                printf("%sОшибка при открытии файла\n%s", YELLOW, RESET);
        }
        else if (test_operation == TEST_ADD)
        {
            data_t data = { 0 };
            if (input_data(&data, "Введите один символ для добавления в дерево:") != ERR_OK)
            {
                printf("%sОшибка ввода данных%s\n", YELLOW, RESET);
                continue;
            }

            // Если первый, то создаем дерево, иначе вставляем в нужное место
            if (is_first)
            {
                clock_gettime(CLOCK_MONOTONIC_RAW, &start);
                tree = tree_create_node(data);
                is_first = 0;
                clock_gettime(CLOCK_MONOTONIC_RAW, &end);
                float time = (end.tv_sec - start.tv_sec) * 1e6f + (end.tv_nsec - start.tv_nsec) / 1e3f;
                printf("%sДобавлен элемент %c в дерево. Время добавления: %.2f мкс%s\n", GREEN, data, time, RESET);
            }
            else
            {
                clock_gettime(CLOCK_MONOTONIC_RAW, &start);
                if (tree_insert(&tree, data) != ERR_OK)
                {
                    printf("%sОшибка при добавлении элемента%s\n", YELLOW, RESET);
                    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
                }
                else
                {
                    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
                    float time = (end.tv_sec - start.tv_sec) * 1e6f + (end.tv_nsec - start.tv_nsec) / 1e3f;
                    printf("%sДобавлен элемент %c в дерево. Время добавления: %.2f мкс%s\n", GREEN, data, time, RESET);
                }
            }
        }
        else if (test_operation == TEST_REMOVE)
        {
            // Удаление из дерева
            data_t data = { 0 };
            if (input_data(&data, "Введите один символ для удаления из дерева:") != ERR_OK)
            {
                printf("%sОшибка ввода данных%s\n", YELLOW, RESET);
                continue;
            }

            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
            if ((rc = tree_remove(&tree, data)) != ERR_OK)
            {
                print_warning_message(rc);
                clock_gettime(CLOCK_MONOTONIC_RAW, &end);
            }
            else
            {
                clock_gettime(CLOCK_MONOTONIC_RAW, &end);
                float time = (end.tv_sec - start.tv_sec) * 1e6f + (end.tv_nsec - start.tv_nsec) / 1e3f;
                printf("%sУдален элемент %c из дерева. Время удаления: %.2f%s\n", GREEN, data, time, RESET);
            }
        }
        else if (test_operation == TEST_SEARCH)
        {
            data_t data = { 0 };
            if (input_data(&data, "Введите один символ для поиска в дереве:") != ERR_OK)
            {
                printf("%sОшибка ввода данных%s\n", YELLOW, RESET);
                continue;
            }

            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
            tree_t *node = tree_search(tree, data);
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);
            float time = (end.tv_sec - start.tv_sec) * 1e6f + (end.tv_nsec - start.tv_nsec) / 1e3f;

            if (node)
            {
                printf("%sЭлемент найден. Время поиска: %.2f%s\n", GREEN, time, RESET);
                inorder_traversal(tree, 1, 1);
                tree_in_picture(tree);
                tree_search_reset(tree);
            }
            else
            {
                printf("%sЭлемент не найден%s\n", YELLOW, RESET);
            }
        }
        else if (test_operation == TEST_PREORDER)
        {
            preorder_traversal(tree, 1, 0);
        }
        else if (test_operation == TEST_INORDER)
        {
            inorder_traversal(tree, 1, 0);
        }
        else if (test_operation == TEST_POSTRDER)
        {
            postorder_traversal(tree, 1, 0);
        }
        else if (test_operation == TEST_UNKNOWN)
        {
            printf("%sНеизвестная операция\n%s", YELLOW, RESET);
        }
    }

    exit:
    tree_free(tree);
}


size_t calculate_tree_size(tree_t *root) {
    if (root == NULL) {
        return 0; // Если узел пустой, память не занимает
    }

    // Суммируем размер текущего узла и размеры левого и правого поддеревьев
    return sizeof(tree_t) + calculate_tree_size(root->left) + calculate_tree_size(root->right);
}
