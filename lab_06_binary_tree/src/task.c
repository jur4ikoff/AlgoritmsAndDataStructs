#include "task.h"
#include "binary_tree.h"
#include "errors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"

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

// Рекурсивная функция для обхода дерева и удаления дубликатов
void remove_duplicates(tree_t **node)
{
    if (*node == NULL)
    {
        return;
    }

    // Рекурсивно обходим левое и правое поддеревья
    remove_duplicates(&((*node)->left));
    remove_duplicates(&((*node)->right));

    // Проверяем на наличие дубликатов в левом поддереве
    tree_t *duplicate_node = tree_search((*node)->left, (*node)->data);
    if (duplicate_node)
    {
        // Удаляем найденный дубликат
        tree_remove(&((*node)->left), duplicate_node->data);
    }

    // Проверяем на наличие дубликатов в правом поддереве
    duplicate_node = tree_search((*node)->right, (*node)->data);
    if (duplicate_node)
    {
        // Удаляем найденный дубликат
        tree_remove(&((*node)->right), duplicate_node->data);
    }
}

void clean_tree(tree_t **tree)
{
    if (*tree == NULL)
    {
        return;
    }

    clean_tree(&(*tree)->left);
    clean_tree(&(*tree)->right);
    free(*tree);
    *tree = NULL;
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

void string_remove_duplicates(char *string)
{
    int hash[256] = {0}; // Массив для подсчета вхождений символов
    int len = strlen(string);

    // Первый проход: подсчет количества вхождений каждого символа
    for (int i = 0; i < len; i++)
    {
        unsigned char current_char = string[i];
        hash[current_char]++;
    }

    // Второй проход: создание новой строки с символами, встречающимися 1 раз
    int index = 0;
    for (int i = 0; i < len; i++)
    {
        unsigned char current_char = string[i];

        // Если символ встречается 1 раз, добавляем его в результат
        if (hash[current_char] == 1)
        {
            string[index++] = current_char;
        }
    }

    string[index] = '\0'; // Завершаем строку нулевым символом
}
