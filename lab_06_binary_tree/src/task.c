#include "task.h"
#include "binary_tree.h"
#include "errors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convert_string_to_tree(tree_t **tree, const char *string)
{
    char *ptr = (char *)string;

    while (*ptr)
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

// Удаление узлов с is_repeated != 0
void tree_delete_repeat(tree_t **tree)
{
    if (*tree == NULL)
    {
        return;
    }

    // Рекурсивно обходим левое и правое поддерево
    tree_delete_repeat(&(*tree)->left);
    tree_delete_repeat(&(*tree)->right);

    // Проверяем текущий узел
    if ((*tree)->is_repeated != 0)
    {
        tree_t *temp = *tree;
        if ((*tree)->left == NULL && (*tree)->right == NULL)
        {
            free(*tree);
            *tree = NULL; // Узел без детей
        }
        else if ((*tree)->left == NULL)
        {
            *tree = (*tree)->right; // Узел с одним правым ребенком
            free(temp);
        }
        else if ((*tree)->right == NULL)
        {
            *tree = (*tree)->left; // Узел с одним левым ребенком
            free(temp);
        }
        else
        {
            // Найти минимальный узел в правом поддереве
            tree_t *min_node = (*tree)->right;
            while (min_node && min_node->left)
            {
                min_node = min_node->left;
            }
            // Заменить данные текущего узла данными минимального узла
            (*tree)->data = min_node->data;
            (*tree)->is_repeated = min_node->is_repeated; // Копируем флаг
            // Удаляем минимальный узел
            tree_delete_repeat(&(*tree)->right);
        }
    }
}
