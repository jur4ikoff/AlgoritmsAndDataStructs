#include "binary_tree.h"
#include "errors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

tree_t *tree_create_node(data_t data)
{
    tree_t *node = malloc(sizeof(tree_t));
    if (!node)
        return NULL;

    node->data = data;
    node->is_repeated = 0;
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
        (*root)->is_repeated = 1;
        return WARNING_REPEAT;
    }
    else if (cmp > 0)
        tree_insert(&(*root)->right, data);
    else
        tree_insert(&(*root)->left, data);

    return ERR_OK;
}

// Удалить ноду
int tree_remove(tree_t **root, data_t data)
{
    if (!(*root))
        return WARNING_TREE;

    int cmp = data - (*root)->data;
    if (cmp > 0)
    {
        tree_remove(&(*root)->right, data);
    }
    else if (cmp < 0)
    {
        tree_remove(&(*root)->left, data);
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
void inorder_traversal(const tree_t *root, int is_head)
{
    if (root != NULL)
    {
        inorder_traversal(root->left, 0);
        printf("%c ", root->data);
        inorder_traversal(root->right, 0);
    }

    if (is_head > 0)
        printf("\n");
}
