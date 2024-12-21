#ifndef AVL_TREE_H__
#define AVL_TREE_H__

#include "constants.h"
#include "errors.h"

typedef struct _avl_tree_type_ avl_tree_t;

// Функция для тестирования avl дерева (из меню)
void avl_tree_test(void);


// Функции для создания и очистки памяти из-под дерева и ноды
/**
 * @brief Функция для инициализации avl дерева
 * @param[in] data Данные в начальном узле
 * @return Проницилизированное дерево
 **/
avl_tree_t *avl_tree_create_node(data_t data);

/**
 * @brief Очистка памяти из-под всего дерева
 *@param[in] tree Указатель на дерево
 **/
void avl_tree_free(avl_tree_t *root);

error_t avl_tree_insert(avl_tree_t **tree, data_t data);
#endif
