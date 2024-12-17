#ifndef MENU_H__
#define MENU_H__

typedef enum
{
    OP_EXIT,
    OP_TEST_BIN_TREE,
    OP_TEST_AVL_TREE,
    OP_TEST_OPEN_HASH,
    OP_TEST_CLOSE_HASH,
    OP_EFFICIENCY,
    OP_COUNT,
    OP_UNKNOWN
} main_operations_t;

typedef enum
{
    TEST_TREE_EXIT,
    TEST_TREE_LOAD,
    TEST_TREE_ADD,
    TEST_TREE_REMOVE,
    TEST_TREE_SEARCH,
    TEST_TREE_SHOW,
    TEST_TREE_NORDER,
    TEST_TREE_STATS,
    TEST_TREE_COUNT,
    TEST_TREE_UNKNOWN,
} tree_test_menu_t;

typedef enum
{
    TEST_HASH_EXIT,
    TEST_HT_LOAD,
    TEST_HT_ADD,
    TEST_HT_REMOVE,
    TEST_HT_STATS,
    TEST_HT_SHOW,
    TEST_COUNT,
    TEST_UNKNOWN,
} hash_test_menu_t;

// Вывод ошибок
void print_error_message(int arg);
void print_warning_message(int arg);

// Вывод меню
void print_info(void);
void print_menu(void);

// Ввод операций
main_operations_t input_operation(void);

#endif
