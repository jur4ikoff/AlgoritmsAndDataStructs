#include "bin_search_tree.h"
#include "constants.h"
#include "errors.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include <time.h>
#include <sys/wait.h>
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

static float bin_tree_calc_avg_compare(bst_tree_t *root)
{
    if (root == NULL)
        return 0.0f;

    int total_depth = 0;
    int total_nodes = 0;

    calc_depth_sum(root, 1, &total_depth, &total_nodes);
    return (float)total_depth / total_nodes;
}

static size_t bin_tree_calc_memory(bst_tree_t *root)
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

    if (tree->is_search)
        fprintf(file, "  %c [color=\"green\"];\n", tree->data.value);

    if (tree->data.repeat)
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

void convert_string_to_bin_tree(bst_tree_t **tree, char *string)
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
        return WARNING_NO_EL;
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

void tree_free(bst_tree_t *tree)
{
    if (!tree)
        return;

    tree_free(tree->left);
    tree_free(tree->right);
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

static void tree_apply_pre(bst_tree_t *tree, tree_apply_fn_t apply_fn, void *arg)
{
    if (!tree)
        return;

    apply_fn(tree, arg);
    tree_apply_pre(tree->left, apply_fn, arg);
    tree_apply_pre(tree->right, apply_fn, arg);
}

void bin_tree_to_graphviz(FILE *file, const char *tree_name, bst_tree_t *tree)
{
    fprintf(file, "digraph %s {\n", tree_name);
    tree_apply_pre(tree, to_dot, file);
    fprintf(file, "}\n");
}

static int open_img(const char *img)
{
    pid_t pid = fork();
    if (pid == -1)
        return ERR_FORK;

    if (pid == 0)
    {
        int stdout_file = open("/dev/null", O_RDWR);
        if (dup2(stdout_file, STDERR_FILENO) == -1) // redirect fork'ed process stderr to /dev/null
            goto err;
        execlp("open", "open", img, NULL);

    err:
        close(stdout_file);

        perror("execlp");
        _exit(EXIT_FAILURE);
    }
    else
    {
        int ret_code;
        waitpid(pid, &ret_code, 0);
        if (WEXITSTATUS(ret_code) != 0)
            return ERR_FORK;
    }
    return ERR_OK;
}

int bin_tree_in_picture(bst_tree_t *tree)
{
    const char *gp = "temp.gp";
    const char *img = "tmp.png";

    FILE *file = fopen(gp, "w");
    if (!file)
        return ERR_FILE;

    bin_tree_to_graphviz(file, "tree", tree);

    fclose(file);

    pid_t pid = fork();
    if (pid == -1)
        return ERR_FORK;

    if (pid == 0)
    {
        execlp("dot", "dot", "-Tpng", gp, "-o", img, NULL);
        perror("execlp");
        _exit(EXIT_FAILURE);
    }
    else
    {
        int ret_code;
        waitpid(pid, &ret_code, 0);
        if (WEXITSTATUS(ret_code) != 0)
            return ERR_FORK;
    }
    return open_img(img);
}

void test_binary_tree(void)
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
        printf(">>Введите тестовую операцию: ");
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
            ЭТО ВВОД ФАЙЛА
            char *filename = NULL;
            printf("Введите путь к файлу: ");
            if ((rc = input_line(&filename, stdin)) != ERR_OK)
            {
                printf("%sОшибка при получении строки%s\n", YELLOW, RESET);
                free(filename);
                continue;
            }
            FILE *file = fopen(filename, "r");
            if (!file)
            {
                printf("%sОшибка при открытии файла%s\n", YELLOW, RESET);
                free(filename);
                continue;
            }

            char *result = malloc(MAX_STRING_LEN * sizeof(char));
            fgets(result, MAX_STRING_LEN - 1, file);
            fclose(file);
            free(filename);

            char *newline = strchr(result, '\n');
            if (newline)
                *newline = 0;

            convert_string_to_tree(&tree, result);
            free(result);*/
            char *string_to_convert = malloc(MAX_STRING_LEN * sizeof(char));
            printf("Введите строку для записи в дерево: ");
            fgets(string_to_convert, MAX_STRING_LEN - 1, stdin);

            char *newline = strchr(string_to_convert, '\n');
            if (newline)
                *newline = 0;

            convert_string_to_bin_tree(&tree, string_to_convert);
            is_first = 0;
            free(string_to_convert);
        }
        else if (test_operation == TEST_TREE_SHOW)
        {
            if (bin_tree_in_picture(tree) != ERR_OK)
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
                bin_tree_in_picture(tree);
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
            bin_tree_in_picture(tree);
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
            printf("%sНеизвестная операция\n%s", YELLOW, RESET);
        }
        else if (test_operation == TEST_TREE_ERROR)
        {
            printf("%sВыбор неверной операции%s\n", RED, RESET);
            goto exit;
        }
    }
exit:
    tree_free(tree);
}
