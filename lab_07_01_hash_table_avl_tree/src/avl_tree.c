#include "avl_tree.h"
#include "constants.h"
#include "errors.h"
#include "menu.h"
#include "render.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
Моя реализация типа данных AVL tree. В дереве хранится структурная переменная data_t
*/
struct _avl_tree_type_
{
    struct _avl_tree_type_ *left;  // Левый потомок
    struct _avl_tree_type_ *right; // Правый потомок

    int height;  // Высота
    data_t data; // Данные
};

// Вывод данных на экран
void print_data(avl_tree_t *subtree, void *arg)
{
    (void)arg;
    data_t data = subtree->data;
    printf("%d ", data.value);
}

/**
 * @brief Функция считает сбалансированность для узла
 * @param[in] root Указатель на узел
 * @return Сбалансирванность узла
 */
int avl_tree_get_height(const avl_tree_t *tree)
{
    if (tree == NULL)
        return 0;

    return tree->height;
}

static int avl_tree_calculate_balance_factor(const avl_tree_t *root)
{
    if (root == NULL)
        return 0;

    return avl_tree_get_height(root->left) - avl_tree_get_height(root->right);
}

/**
 * @brief Функция получает высоту узла АВЛ дерева
 * @param[in] tree Указатель на дерево
 */

/**
 * @brief Восстанавливает корректное значение высоты узла // высоты правого и левого поддерева должны быть также корректными
 * @param[in] head Указатель на узел
 */
static void avl_tree_fix_height(avl_tree_t *root)
{
    int left_height = avl_tree_get_height(root->left);
    int right_height = avl_tree_get_height(root->right);
    if (left_height > right_height)
        root->height = left_height + 1;
    else
        root->height = right_height + 1;
}

/**
 * @brief Функция для инициализации avl дерева
 * @param[in] data Данные в начальном узле
 * @return Проницилизированное дерево
 **/
avl_tree_t *avl_tree_create_node(data_t data)
{
    avl_tree_t *tree = NULL;
    tree = malloc(sizeof(*tree));
    if (tree == NULL)
        return NULL;

    // Определение полей
    tree->left = NULL;
    tree->right = NULL;
    tree->height = 1;
    tree->data = data;
    return tree;
}

/*
Функция для очистки памяти из-под одного элемента
Сделана для возможного расширения data_t
*/
static void avl_tree_free_node(avl_tree_t *node)
{
    free(node);
}

/**
 * @brief Функция поворачивает поддерево вправо
 * @param[in] head Указатель на поддерево
 * @return Указатель на новое поддерево
 */
static avl_tree_t *avl_tree_rotate_right(avl_tree_t *head)
{
    avl_tree_t *temp = head->left;
    head->left = temp->right;
    temp->right = head;

    avl_tree_fix_height(head);
    avl_tree_fix_height(temp);

    return temp;
}

/**
 * @brief Функция поворачивает поддерево влево
 * @param[in] head Указатель на поддерево
 * @return Указатель на новое поддерево
 */
static avl_tree_t *avl_tree_rotate_left(avl_tree_t *head)
{
    avl_tree_t *temp = head->right;
    head->right = temp->left;
    temp->left = head;

    avl_tree_fix_height(head);
    avl_tree_fix_height(temp);

    return temp;
}

/**
 * @brief Очистка памяти из-под всего дерева
 *@param[in] tree Указатель на дерево
 **/
void avl_tree_free(avl_tree_t *root)
{
    if (root == NULL)
        return;

    // Рекурсивая очистка
    avl_tree_free(root->left);
    avl_tree_free(root->right);

    avl_tree_free_node(root);
}

/**
 * @brief Функция для вставки элемента data_t в AVL дерево
 * @param[in] tree Указатель на AVL дерево
 * @param[in] data Структурная переменная data_t data
 * @return Код ошибки
 */
error_t avl_tree_insert(avl_tree_t **root, data_t data)
{
    int rc = ERR_OK;
    if (root == NULL)
        return ERR_MEMORY_ALLOCATION;

    if (*root == NULL)
    {
        avl_tree_t *new_node = avl_tree_create_node(data);
        *root = new_node;
        return ERR_OK;
    }

    int cmp = (*root)->data.value - data.value;
    if (cmp == 0)
        (*root)->data.repeat += 1;

    if (cmp > 0)
        rc = avl_tree_insert(&(*root)->left, data);
    else
        rc = avl_tree_insert(&(*root)->right, data);

    avl_tree_fix_height(*root);

    int balance_factor = avl_tree_calculate_balance_factor(*root);
    if (balance_factor > 1)
    {
        int left_cmp = data.value - (*root)->left->data.value;
        if (left_cmp < 0)
        {
            *root = avl_tree_rotate_right(*root);
            return ERR_OK;
        }
        else if (left_cmp > 0)
        {
            (*root)->left = avl_tree_rotate_left((*root)->left);
            *root = avl_tree_rotate_right(*root);
            return ERR_OK;
        }
    }
    else if (balance_factor < -1)
    {
        int right_cmp = data.value - (*root)->right->data.value;
        if (right_cmp > 0)
        {
            *root = avl_tree_rotate_left(*root);
            return ERR_OK;
        }
        else if (right_cmp < 0)
        {
            (*root)->right = avl_tree_rotate_right((*root)->right);
            *root = avl_tree_rotate_left(*root);
            return ERR_OK;
        }
    }

    return rc;
}

static void to_dot(avl_tree_t *tree, void *file)
{
    static int null_cnt = 0;
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

void avl_tree_apply_preorder(avl_tree_t *tree, avl_tree_apply_fn_t apply_func, void *arg)
{
    if (!tree)
        return;

    apply_func(tree, arg);
    avl_tree_apply_preorder(tree->left, apply_func, arg);
    avl_tree_apply_preorder(tree->right, apply_func, arg);
}

void avl_tree_apply_inorder(avl_tree_t *tree, avl_tree_apply_fn_t apply_func, void *arg)
{
    if (!tree)
        return;

    avl_tree_apply_inorder(tree->left, apply_func, arg);
    apply_func(tree, arg);
    avl_tree_apply_inorder(tree->right, apply_func, arg);
}

void avl_tree_apply_postorder(avl_tree_t *tree, avl_tree_apply_fn_t apply_func, void *arg)
{
    if (!tree)
        return;

    avl_tree_apply_postorder(tree->left, apply_func, arg);
    avl_tree_apply_postorder(tree->right, apply_func, arg);
    apply_func(tree, arg);
}

static void avl_tree_to_graphviz(FILE *file, const char *tree_name, avl_tree_t *tree)
{
    fprintf(file, "digraph %s {\n", tree_name);
    avl_tree_apply_preorder(tree, to_dot, file);
    fprintf(file, "}\n");
}

int avl_tree_show(avl_tree_t *tree)
{
    const char *gp_file = "./temp.gp", *img_file = "./tree.png";

    FILE *file = fopen(gp_file, "w");
    if (!file)
        return ERR_FILE;

    avl_tree_to_graphviz(file, "bin_tree", tree);
    fclose(file);
    render_graphviz(gp_file, img_file);
    return ERR_OK;
}

void avl_tree_convert_from_string(avl_tree_t **tree, char *string)
{
    char *ptr = string;
    while (*ptr)
    {
        data_t data = { .repeat = 0, .value = *ptr };
        avl_tree_insert(tree, data);
        ptr++;
    }
}

void avl_tree_test(void)
{
    // Инициализация переменных
    printf("\nПодпрограмма для тестирования бинарного дерева\n");
    int test_itteration_count = 0;
    error_t rc = ERR_OK;
    tree_test_menu_t test_operation = TEST_TREE_COUNT;
    struct timespec start, end;
    avl_tree_t *tree = NULL;
    bool is_first = 1;

    // Запуск главного цикла
    while (test_operation != TEST_TREE_EXIT && rc == ERR_OK)
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

            avl_tree_convert_from_string(&tree, string_to_convert);
            is_first = 0;
            free(string_to_convert);
        }
        else if (test_operation == TEST_TREE_ADD)
        {
            data_t data = { 0 };
            if (input_data(&data, ">>Введите один символ для добавления в дерево:") != ERR_OK)
            {
                printf("%sОшибка ввода данных%s\n", YELLOW, RESET);
                continue;
            }

            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
            rc = avl_tree_insert(&tree, data);
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);
            print_warning_message(rc);
            float time = (end.tv_sec - start.tv_sec) * 1e6f + (end.tv_nsec - start.tv_nsec) / 1e3f;
            printf("%sДобавлен элемент %c в дерево. Время добавления: %.2f мкс%s\n", GREEN, data.value, time, RESET);
        }
        else if (test_operation == TEST_TREE_REMOVE)
        {
            if (is_first)
                return;
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
            avl_tree_show(tree);
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
    avl_tree_free(tree);
}
