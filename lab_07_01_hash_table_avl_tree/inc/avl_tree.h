#ifndef AVL_TREE_H__
#define AVL_TREE_H__

#include "constants.h"
#include "errors.h"

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


// обходы дерева
void avl_tree_apply_preorder(avl_tree_t *tree, avl_tree_apply_fn_t apply_fn, void *arg);
void avl_tree_apply_inorder(avl_tree_t *tree, avl_tree_apply_fn_t apply_func, void *arg);
void avl_tree_apply_postorder(avl_tree_t *tree, avl_tree_apply_fn_t apply_func, void *arg);
#endif
