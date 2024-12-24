#ifndef AVL_TREE_H__
#define AVL_TREE_H__

#include "constants.h"
#include "errors.h"
#include <stdio.h>

typedef struct _avl_tree_type_ avl_tree_t;
typedef void (*avl_tree_apply_fn_t)(avl_tree_t *subtree, void *arg);

// Функция для тестирования avl дерева (из меню)
void avl_tree_test(void);

// Функции для создания элемента
avl_tree_t *avl_tree_create_node(data_t data);

// Очистка памяти из-под всего дерева
void avl_tree_free(avl_tree_t *root);

// Функции для работы с деревом
// Вставка элемента в дерево
error_t avl_tree_insert(avl_tree_t **tree, data_t data);
// Удаление элемента из AVL дерева
avl_tree_t *avl_tree_remove(avl_tree_t *tree, data_t element);
// Поиск элемента в AVL дереве
avl_tree_t *avl_tree_search(avl_tree_t *root, data_t element);

// обходы дерева
void avl_tree_apply_preorder(avl_tree_t *tree, avl_tree_apply_fn_t apply_fn, void *arg);
void avl_tree_apply_inorder(avl_tree_t *tree, avl_tree_apply_fn_t apply_func, void *arg);
void avl_tree_apply_postorder(avl_tree_t *tree, avl_tree_apply_fn_t apply_func, void *arg);

// Подсчет статистики
size_t avl_tree_calc_memory(avl_tree_t *root);
float avl_tree_calc_avg_compare(avl_tree_t *root);
int avl_tree_show(avl_tree_t *tree, char *img_file);
float avl_calculte_search_time(char *filename, size_t exp_count, float *cmp);

avl_tree_t *avl_tree_search_with_cmp(avl_tree_t *root, data_t element, size_t *cmp);

#endif
