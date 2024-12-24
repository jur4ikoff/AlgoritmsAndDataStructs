#include "bin_search_tree.h"
#include "constants.h"
#include "errors.h"
#include "menu.h"
#include "render.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

struct _binary_search_tree_t_
{
    data_t data;
    int is_search;                        // 1 - флаг активируется, после поиска
    struct _binary_search_tree_t_ *left;  // Левый потомок
    struct _binary_search_tree_t_ *right; // Правый потомок
};

static void calc_depth_sum(bst_tree_t *root, int current_depth, int *total_depth, int *total_nodes)
{
    if (root == NULL)
        return;

    *total_depth += current_depth;
    (*total_nodes)++;

    calc_depth_sum(root->left, current_depth + 1, total_depth, total_nodes);
    calc_depth_sum(root->right, current_depth + 1, total_depth, total_nodes);
}

float bin_tree_calc_avg_compare(bst_tree_t *root)
{
    if (root == NULL)
        return 0.0f;

    int total_depth = 0;
    int total_nodes = 0;

    calc_depth_sum(root, 1, &total_depth, &total_nodes);
    return (float)total_depth / total_nodes;
}

size_t bin_tree_calc_memory(bst_tree_t *root)
{
    if (root == NULL)
    {
        return 0;
    }
    // Суммируем размер текущего узла и размеры левого и правого поддеревьев
    return sizeof(bst_tree_t) + bin_tree_calc_memory(root->left) + bin_tree_calc_memory(root->right);
}

static void to_dot(bst_tree_t *tree, void *file)
{
    static int null_cnt = 0;
    if (tree->data.repeat != 0)
        fprintf(file, "  %c [color=\"red\"];\n", tree->data.value);

    if (tree->left)
        fprintf(file, "  %c -> %c;\n", tree->data.value, tree->left->data.value);
    else
    {
        fprintf(file, "  %c -> null_%d;\n", tree->data.value, null_cnt);
        fprintf(file, "  null_%d [shape=\"point\", color=\"red\"];\n", null_cnt);
        null_cnt++;
    }

    if (tree->right)
        fprintf(file, "  %c -> %c;\n", tree->data.value, tree->right->data.value);
    else
    {
        fprintf(file, "  %c -> null_%d;\n", tree->data.value, null_cnt);
        fprintf(file, "  null_%d [shape=\"point\", color=\"red\"];\n", null_cnt);
        null_cnt++;
    }
}

void bin_tree_convert_from_string(bst_tree_t **tree, char *string)
{
    char *ptr = (char *)string;

    while (*ptr != 0)
    {
        data_t data = {0};
        data.value = *ptr;
        if (*tree == NULL)
        {
            *tree = bin_tree_create_node(data);
            ptr++;
        }
        else
        {
            bin_tree_insert(tree, data);
            ptr++;
        }
    }
}

bst_tree_t *bin_tree_create_node(data_t data)
{
    bst_tree_t *node = malloc(sizeof(bst_tree_t));

    if (!node)
        return NULL;

    node->data = data;
    node->data.repeat = 0;
    node->is_search = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/**
 * @brief Функция вставляет элемент в дерево поиска
 * @param root Корень дерева
 * @param data Структура данных, которую нужно вставить
 */
int bin_tree_insert(bst_tree_t **root, data_t data)
{
    int rc = ERR_OK;
    /*if (data == NULL)
        return ERR_DATA_INPUT;*/

    if (!(*root))
    {
        *root = bin_tree_create_node(data);
        return ERR_OK;
    }

    int cmp = data.value - (*root)->data.value;

    if (cmp == 0)
    {
        (*root)->data.repeat += 1;
        return WARNING_REPEAT;
    }
    else if (cmp > 0)
        rc = bin_tree_insert(&(*root)->right, data);
    else
        rc = bin_tree_insert(&(*root)->left, data);

    return rc;
}

// Удалить ноду
int bin_tree_remove(bst_tree_t **root, data_t data)
{
    if (!(*root))
        return WARNING_TREE;

    int cmp = data.value - (*root)->data.value;
    if (cmp > 0)
    {
        return bin_tree_remove(&(*root)->right, data);
    }
    else if (cmp < 0)
    {
        return bin_tree_remove(&(*root)->left, data);
    }
    if (cmp == 0)
    {
        bst_tree_t *temp = *root;
        if (!(*root)->left && !(*root)->right)
        {
            free(*root);
            *root = NULL;
        }
        else if ((*root)->left == NULL)
        {
            *root = (*root)->right;
            free(temp);
        }
        else if ((*root)->right == NULL)
        {
            *root = (*root)->left;
            free(temp);
        }
        else
        {
            bst_tree_t *min_node = (*root)->right;
            while (min_node && min_node->left)
            {
                min_node = min_node->left;
            }

            (*root)->data = min_node->data;
            return bin_tree_remove(&(*root)->right, min_node->data);
        }
    }
    else
        return WARNING_ELEMENT_NOT_FOUND;
    return ERR_OK;
}

bst_tree_t *bin_tree_search(bst_tree_t *root, data_t data)
{
    if (root == NULL)
    {
        return root;
    }

    if (data.value == root->data.value)
    {
        root->is_search = 1;
        return root;
    }

    if (data.value > root->data.value)
    {
        return bin_tree_search(root->right, data);
    }
    else
    {
        return bin_tree_search(root->left, data);
    }

    return root;
}

bst_tree_t *bst_tree_search_with_cmp(bst_tree_t *root, data_t data, size_t *cmp)
{
    if (root == NULL)
    {
        return root;
    }

    if (data.value == root->data.value)
    {
        root->is_search = 1;
        return root;
    }
    (*cmp)++;

    if (data.value > root->data.value)
    {
        return bst_tree_search_with_cmp(root->right, data, cmp);
    }
    else
    {
        return bst_tree_search_with_cmp(root->left, data, cmp);
    }

    return root;
}

void bin_tree_free(bst_tree_t *tree)
{
    if (!tree)
        return;

    bin_tree_free(tree->left);
    bin_tree_free(tree->right);
    free(tree);
}

/**
 * @brief Функция для инфиксного обхода дерева
 * @param root Указатель на корень
 * @param is_head Специальный флаг, нужен для того, чтобы вовремя вывести \n
 * @return
 */
void bin_tree_inorder_traversal(const bst_tree_t *root, int is_head, int is_color)
{
    if (root != NULL)
    {
        bin_tree_inorder_traversal(root->left, 0, is_color);
        if (is_color)
        {
            if (root->is_search)
                printf("%s%c%s ", GREEN, root->data.value, RESET);
            else if (root->data.repeat)
                printf("%s%c%s ", RED, root->data.value, RESET);
            else
                printf("%c ", root->data.value);
        }
        else
            printf("%c ", root->data.value);
        bin_tree_inorder_traversal(root->right, 0, is_color);
    }

    if (is_head > 0)
        printf("\n");
}

// Функция очищает найденную ноду
void bin_tree_search_reset(bst_tree_t *root)
{
    if (root != NULL)
    {
        bin_tree_search_reset(root->left);
        root->is_search = 0;
        bin_tree_search_reset(root->right);
    }
}

static void bin_tree_apply_pre(bst_tree_t *tree, bst_tree_apply_fn_t apply_fn, void *arg)
{
    if (!tree)
        return;

    apply_fn(tree, arg);
    bin_tree_apply_pre(tree->left, apply_fn, arg);
    bin_tree_apply_pre(tree->right, apply_fn, arg);
}

static void bin_tree_to_graphviz(FILE *file, const char *tree_name, bst_tree_t *tree)
{
    fprintf(file, "digraph %s {\n", tree_name);
    bin_tree_apply_pre(tree, to_dot, file);
    fprintf(file, "}\n");
}
float bst_calculte_search_time(char *filename, size_t exp_count, float *cmp)
{
    struct timespec start, end;
    float time_del = 0.0;
    char *result = malloc(MAX_STRING_LEN * sizeof(char));
    int rc = ERR_OK;
    if ((rc = input_string_from_file(filename, result)) != ERR_OK)
    {
        free(result);
        return rc;
    }

    bst_tree_t *tree = NULL;
    bin_tree_convert_from_string(&tree, result);
    if (!tree)
    {
        bin_tree_free(tree);
        free(result);
        return ERR_STRING;
    }

    *cmp = bin_tree_calc_avg_compare(tree);
    size_t count = 0;
    for (size_t i = 0; i < exp_count; i++)
    {
        char *ptr = result;
        while (*ptr)
        {
            data_t data = {.repeat = 0, .value = *ptr};
            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
            bin_tree_search(tree, data);
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);
            time_del += (end.tv_sec - start.tv_sec) * 1e6f + (end.tv_nsec - start.tv_nsec) / 1e3f;
            count++;
            ptr++;
        }
    }

    free(result);
    return time_del / count;
}

// Удаление узлов с is_repeated != 0
void tree_remove_repeat(bst_tree_t **tree)
{
    if (*tree == NULL)
    {
        return;
    }

    // Рекурсивно обходим левое и правое поддерево
    tree_remove_repeat(&(*tree)->left);
    tree_remove_repeat(&(*tree)->right);

    // Проверяем текущий узел
    if ((*tree)->data.repeat != 0)
    {
        bin_tree_remove(tree, (*tree)->data);
    }
}

void binary_tree_test(void)
{
    // Инициализация переменных
    printf("Подпрограмма для тестирования бинарного дерева\n");
    int test_itteration_count = 0, rc = ERR_OK;
    tree_test_menu_t test_operation = TEST_TREE_COUNT;
    struct timespec start, end;

    bst_tree_t *tree = NULL;
    int is_first = 1;

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
            char *string_to_convert = malloc(MAX_STRING_LEN * sizeof(char));
            printf("Введите строку для записи в дерево: ");
            fgets(string_to_convert, MAX_STRING_LEN - 1, stdin);

            char *newline = strchr(string_to_convert, '\n');
            if (newline)
                *newline = 0;

            bin_tree_convert_from_string(&tree, string_to_convert);
            is_first = 0;
            free(string_to_convert);
        }
        else if (test_operation == TEST_TREE_SHOW)
        {
            if (bst_tree_show(tree, "tree.png") != ERR_OK)
                printf("%sОшибка при открытии файла\n%s", YELLOW, RESET);
        }
        else if (test_operation == TEST_TREE_ADD)
        {
            data_t data = {0};
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
                    printf("%sДобавлен элемент %c в дерево. Время добавления: %.2f мкс%s\n", GREEN, data.value, time, RESET);
                }
            }
        }
        else if (test_operation == TEST_TREE_REMOVE)
        {
            // Удаление из дерева
            data_t data = {0};
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
            }
        }
        else if (test_operation == TEST_TREE_SEARCH)
        {
            data_t data = {0};
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
                bst_tree_show(tree, "tree.png");
                bin_tree_search_reset(tree);
            }
            else
            {
                printf("%sЭлемент не найден%s\n", YELLOW, RESET);
            }
        }
        else if (test_operation == TEST_TREE_SHOW)
        {
            // Вывод дерева на экран
            bst_tree_show(tree, "tree.png");
        }
        else if (test_operation == TEST_TREE_INORDER)
        {
            // Инфиксный обход
            bin_tree_inorder_traversal(tree, 1, 0);
        }
        else if (test_operation == TEST_TREE_STATS)
        {
            // Статистика о дереве
            printf("Дерево занимает в памяти %zu байт\n", bin_tree_calc_memory(tree));
            printf("Среднее количество сравнений %.3f\n", bin_tree_calc_avg_compare(tree));
        }
        else if (test_operation == TEST_TREE_UNKNOWN)
        {
            // Операция неизвестна
            print_warning_message(WARNING_OPERATION);
        }
        else if (test_operation == TEST_TREE_ERROR)
        {
            printf("%sВыбор неверной операции%s\n", RED, RESET);
            goto exit;
        }
    }
exit:
    bin_tree_free(tree);
}

int bst_tree_show(bst_tree_t *tree, char *img_file)
{
    const char *gp_file = "./temp.gp";

    FILE *file = fopen(gp_file, "w");
    if (!file)
        return ERR_FILE;

    bin_tree_to_graphviz(file, "bin_tree", tree);
    fclose(file);
    render_graphviz(gp_file, img_file);
    return ERR_OK;
}
