#ifndef AVL_TREE_H__
#define AVL_TREE_H__

#include "constants.h"

typedef struct _avl_tree_type_ avl_tree_t;

// Функция для тестирования avl дерева (из меню)
void avl_tree_test(void);

/**
 * @brief Функция для инициализации avl дерева
 * @param[in] data Данные в начальном узле
 * @return Проницилизированное дерево
 **/
avl_tree_t *avl_tree_create(data_t data);

/**
 * @brief Очистка памяти из-под всего дерева
 *@param[in] tree Указатель на дерево
 **/
void avl_tree_free(avl_tree_t *tree);

#endif
