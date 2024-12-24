#ifndef MENU_H__
#define MENU_H__

#include "constants.h"
#include <stdio.h>

typedef enum
{
    OP_EXIT,
    OP_TEST_BIN_TREE,
    OP_TEST_AVL_TREE,
    OP_TEST_OPEN_HASH,
    OP_TEST_CLOSE_HASH,
    OP_TASK,
    OP_EFFICIENCY,
    OP_COUNT,
    OP_UNKNOWN,
    OP_ERROR
} main_operations_t;

typedef enum
{
    TEST_TREE_EXIT,
    TEST_TREE_LOAD,
    TEST_TREE_ADD,
    TEST_TREE_REMOVE,
    TEST_TREE_SEARCH,
    TEST_TREE_SHOW,
    TEST_TREE_INORDER,
    TEST_TREE_STATS,
    TEST_TREE_COUNT,
    TEST_TREE_UNKNOWN,
    TEST_TREE_ERROR
} tree_test_menu_t;

typedef enum
{
    TEST_HASH_EXIT,
    TEST_HT_LOAD,
    TEST_HT_ADD,
    TEST_HT_REMOVE,
    TEST_HT_SEARCH,
    TEST_HT_SHOW,
    TEST_HT_STATS,
    TEST_HT_COUNT,
    TEST_HT_UNKNOWN,
    TEST_HT_ERROR
} hash_test_menu_t;

// Вывод ошибок
void print_error_message(int arg);
void print_warning_message(int arg);

// Вывод меню
void print_info(void);
void print_menu(void);
void print_test_tree_menu(void);
void print_hash_table_menu(void);

// Ввод операций
main_operations_t input_operation(void);
tree_test_menu_t input_test_tree_operation(void);
hash_test_menu_t input_test_ht_operation(void);

// Инпуты
int input_line(char **string, FILE *file);
int input_data(data_t *data, char *message);

// Подсчет следующего простого числа
int calc_next_prime(size_t prev);
int input_string_from_file(char *filename, char *string);
#endif
