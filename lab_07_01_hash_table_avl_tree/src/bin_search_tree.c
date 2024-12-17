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

struct _tree_t_
{
    data_t data;
    int repeated;        // 0 - not repeat; 1 - repeat
    int is_search;          // 1 - флаг активируется, после поиска
    struct _tree_t_ *left;  // Левый потомок
    struct _tree_t_ *right; // Правый потомок
};

void convert_string_to_tree(tree_t **tree, char *string)
{
    char *ptr = (char *)string;

    while (*ptr != 0)
    {
        if (*tree == NULL)
        {
            *tree = tree_create_node(*ptr);
            ptr++;
        }
        tree_insert(tree, *ptr);
        ptr++;
    }
}

tree_t *tree_create_node(data_t data)
{
    tree_t *node = malloc(sizeof(tree_t));

    if (!node)
        return NULL;

    node->data = data;
    node->repeated = 0;
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
int tree_insert(tree_t **root, data_t data)
{
    int rc = ERR_OK;
    if (!data)
        return ERR_DATA_INPUT;

    if (!(*root))
    {
        *root = tree_create_node(data);
        return ERR_OK;
    }

    int cmp = data - (*root)->data;

    if (cmp == 0)
    {
        (*root)->repeated = 1;
        return WARNING_REPEAT;
    }
    else if (cmp > 0)
        rc = tree_insert(&(*root)->right, data);
    else
        rc = tree_insert(&(*root)->left, data);

    return rc;
}

// Удалить ноду
int tree_remove(tree_t **root, data_t data)
{
    if (!(*root))
        return WARNING_TREE;

    int cmp = data - (*root)->data;
    if (cmp > 0)
    {
        return tree_remove(&(*root)->right, data);
    }
    else if (cmp < 0)
    {
        return tree_remove(&(*root)->left, data);
    }
    if (cmp == 0)
    {
        tree_t *temp = *root;
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
            tree_t *min_node = (*root)->right;
            while (min_node && min_node->left)
            {
                min_node = min_node->left;
            }

            (*root)->data = min_node->data;
            return tree_remove(&(*root)->right, min_node->data);
        }
    }
    else
        return WARNING_NO_EL;
    return ERR_OK;
}

tree_t *tree_search(tree_t *root, data_t data)
{
    if (root == NULL)
    {
        return root;
    }

    if (data == root->data)
    {
        root->is_search = 1;
        return root;
    }

    if (data > root->data)
    {
        return tree_search(root->right, data);
    }
    else
    {
        return tree_search(root->left, data);
    }

    return root;
}

void tree_free(tree_t *tree)
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
void tree_inorder_traversal(const tree_t *root, int is_head, int is_color)
{
    if (root != NULL)
    {
        tree_inorder_traversal(root->left, 0, is_color);
        if (is_color)
        {
            if (root->is_search)
                printf("%s%c%s ", GREEN, root->data, RESET);
            else if (root->repeated)
                printf("%s%c%s ", RED, root->data, RESET);
            else
                printf("%c ", root->data);
        }
        else
            printf("%c ", root->data);
        tree_inorder_traversal(root->right, 0, is_color);
    }

    if (is_head > 0)
        printf("\n");
}

// Функция очищает найденную ноду
void tree_search_reset(tree_t *root)
{
    if (root != NULL)
    {
        tree_search_reset(root->left);
        root->is_search = 0;
        tree_search_reset(root->right);
    }
}

static void to_dot(tree_t *tree, void *file)
{
    static int null_cnt = 0;

    if (tree->is_search)
        fprintf(file, "  %c [color=\"green\"];\n", tree->data);

    if (tree->repeated)
        fprintf(file, "  %c [color=\"red\"];\n", tree->data);

    if (tree->left)
        fprintf(file, "  %c -> %c;\n", tree->data, tree->left->data);
    else
    {
        fprintf(file, "  %c -> null_%d;\n", tree->data, null_cnt);
        fprintf(file, "  null_%d [shape=\"point\", color=\"red\"];\n", null_cnt);
        null_cnt++;
    }

    if (tree->right)
        fprintf(file, "  %c -> %c;\n", tree->data, tree->right->data);
    else
    {
        fprintf(file, "  %c -> null_%d;\n", tree->data, null_cnt);
        fprintf(file, "  null_%d [shape=\"point\", color=\"red\"];\n", null_cnt);
        null_cnt++;
    }
}

static void tree_apply_pre(tree_t *tree, tree_apply_fn_t apply_fn, void *arg)
{
    if (!tree)
        return;

    apply_fn(tree, arg);
    tree_apply_pre(tree->left, apply_fn, arg);
    tree_apply_pre(tree->right, apply_fn, arg);
}

void tree_to_graphviz(FILE *file, const char *tree_name, tree_t *tree)
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

        //     |> exec_name
        //     |       |> argv      |> it's necessary
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

int tree_in_picture(tree_t *tree)
{
    const char *gp = "temp.gp";
    const char *img = "tmp.png";

    FILE *file = fopen(gp, "w");
    if (!file)
        return ERR_FILE;

    tree_to_graphviz(file, "tree", tree);

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

#define MAX_INPUT_DATA_STRING_SIZE 3

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
    tree_test_menu_t test_operation = TEST_TREE_COUNT;
    struct timespec start, end;

    tree_t *tree = NULL;
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

            convert_string_to_tree(&tree, string_to_convert);
            free(string_to_convert);
        }
        else if (test_operation == TEST_TREE_SHOW)
        {
            if (tree_in_picture(tree) != ERR_OK)
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
        else if (test_operation == TEST_TREE_SEARCH)
        {
            data_t data = {0};
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
                tree_inorder_traversal(tree, 1, 1);
                tree_in_picture(tree);
                tree_search_reset(tree);
            }
            else
            {
                printf("%sЭлемент не найден%s\n", YELLOW, RESET);
            }
        }
        else if (test_operation == TEST_TREE_SHOW)
        {
            // Вывод дерева на экран
            tree_in_picture(tree);
        }
        else if (test_operation == TEST_TREE_INORDER)
        {
            // Инфиксный обход
            tree_inorder_traversal(tree, 1, 0);
        }
        else if (test_operation == TEST_TREE_STATS)
        {
            // Статистика
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

size_t calculate_tree_size(tree_t *root)
{
    if (root == NULL)
    {
        return 0; // Если узел пустой, память не занимает
    }

    // Суммируем размер текущего узла и размеры левого и правого поддеревьев
    return sizeof(tree_t) + calculate_tree_size(root->left) + calculate_tree_size(root->right);
}
