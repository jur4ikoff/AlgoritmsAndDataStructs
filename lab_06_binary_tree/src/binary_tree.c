#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tree_t *tree_create_node(data_t *data)
{
    tree_t *node = malloc(sizeof(tree_t));
    if (!node)
        return NULL;

    node->data = strdup(data);
    node->is_repeated = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/**
 * @brief Функция вставляет элемент в дерево поиска
 * @param root Корень дерева
 * @param data Структура данных, которую нужно вставить
 * @param compare Компаратор
 */
tree_t *tree_insert(tree_t *root, data_t *data, int (*compare)(void *, void *))
{
    if (!data)
        return NULL;

    if (!root)
        return tree_create_node(data);

    int cmp = compare(data, root->data);
    if (cmp == 0)
    {
        root->is_repeated = 1;
    }
    else if (cmp > 0)
        root->right = tree_insert(root->right, data, compare);
    else
        root->left = tree_insert(root->left, data, compare);

    return root;
}

void tree_free(tree_t *tree)
{
    if (!tree)
        return;

    free(tree->data);
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
void inorder_traversal(const tree_t *root, int is_head)
{
    if (root != NULL)
    {
        inorder_traversal(root->left, 0);
        printf("%s ", root->data);
        inorder_traversal(root->right, 0);
    }

    if (is_head > 0)
        printf("\n");
}
