#include "task.h"
#include "avl_tree.h"
#include "bin_search_tree.h"
#include "hash_t_close.h"
#include "hash_t_open.h"
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>

struct _binary_search_tree_t_
{
    data_t data;
    int is_search;                        // 1 - флаг активируется, после поиска
    struct _binary_search_tree_t_ *left;  // Левый потомок
    struct _binary_search_tree_t_ *right; // Правый потомок
};

#define TEMP 2

void convert_bst_to_avl(avl_tree_t **avl_root, bst_tree_t *tree)
{
    /*avl_tree_t *new;
    while (tree)
    {
        data_t element = tree->data;
        bin_tree_remove(&tree, element);
        new = avl_tree_insert(&new, element);
    }

    return new;*/

    if (tree == NULL)
    {
        return; // Если узел пустой, выходим из функции
    }

    // Вставляем текущий элемент в AVL дерево
    avl_tree_insert(avl_root, tree->data);

    // Рекурсивно обходим левое и правое поддеревья
    convert_bst_to_avl(avl_root, tree->left);
    convert_bst_to_avl(avl_root, tree->right);
}

int solve_task(void)
{
    int rc = ERR_OK;
    char *filename = NULL;
    printf(">>Введите путь к файлу с данными: ");
    fgetc(stdin);
    if ((rc = input_line(&filename, stdin)) != ERR_OK)
    {
        free(filename);
        return rc;
    }

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        free(filename);
        return ERR_FILE;
    }

    char *string = NULL;
    if ((rc = input_line(&string, file)) != ERR_OK)
    {
        free(string);
    }

    printf(">> Введите символ для поиска в деревьях: ");
    char to_find = getchar();
    data_t data = {.repeat = 0, .value = to_find};
    bst_tree_t *bst_tree = NULL;
    bin_tree_convert_from_string(&bst_tree, string);
    size_t cmp_bst = 0;
    printf("\nИсходное дерево\n");
    bin_tree_show(bst_tree);

    fgetc(stdin);
    printf(">>Нажмите enter");
    char buffer[TEMP];
    fgets(buffer, 2, stdin);
    printf("______________________\nУдаление дубликатов из исходной строки в дереве\n");
    tree_remove_repeat(&bst_tree);
    bin_tree_show(bst_tree);
    if (bst_tree_search_with_cmp(bst_tree, data, &cmp_bst) != NULL)
        printf("Элемент %c найден за %zu сравнений\n", data.value, cmp_bst);
    else
        printf("Элемент не найден\n");
    
    printf("Дерево занимает в памяти %zu байт\n", bin_tree_calc_memory(bst_tree));
    float cmp = 0;
    printf("Среднее количество сравнений %.3f Среднее время поиска: %.3f мкс\n", bin_tree_calc_avg_compare(bst_tree), bst_calculte_search_time(filename, 10, &cmp));
    printf(">>Нажмите enter");
    fgets(buffer, 2, stdin);

    printf("\n______________________\nКонвертация в АВЛ дерево\n");
    avl_tree_t *avl_tree = NULL;
    cmp_bst = 0;
    convert_bst_to_avl(&avl_tree, bst_tree);
     if (avl_tree_search_with_cmp(avl_tree, data, &cmp_bst) != NULL)
        printf("Элемент %c найден за %zu сравнений\n", data.value, cmp_bst);
    else
        printf("Элемент не найден\n");
    avl_tree_show(avl_tree);
    printf("Дерево занимает в памяти %zu байт\n", avl_tree_calc_memory(avl_tree));
    printf("Среднее количество сравнений %.3f Среднее время поиска: %.3f мкс\n", avl_tree_calc_avg_compare(avl_tree), avl_calculte_search_time(filename, 10, &cmp));

    free(filename);
    bin_tree_free(bst_tree);
    avl_tree_free(avl_tree);

    return ERR_OK;
}
