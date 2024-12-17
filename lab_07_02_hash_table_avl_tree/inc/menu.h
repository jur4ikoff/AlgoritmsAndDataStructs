#ifndef MENU_H__
#define MENU_H__

typedef enum __main_oper_t_
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

typedef enum _tree_test_oper_t_
{
    TEST_EXIT,
    TEST_LOAD,
    TEST_ADD,
    TEST_REMOVE,
    TEST_SEARCH,
    TEST_SHOW,
    TEST_PREORDER,
    TEST_INORDER,
    TEST_POSTRDER,
    TEST_COUNT,
    TEST_UNKNOWN,
} tree_test_menu_t;

typedef enum _hash_test_oper_t_
{
    TEST_EXIT,
    TEST_LOAD,
    TEST_ADD,
    TEST_REMOVE,
    TEST_SEARCH,
    TEST_SHOW,
    TEST_PREORDER,
    TEST_INORDER,
    TEST_POSTRDER,
    TEST_COUNT,
    TEST_UNKNOWN,
} hash_test_menu_t;

void print_error_message(int arg);
void print_warning_message(int arg);
void print_info(void);
void print_menu(void);
void test_menu(void);
main_operations_t input_operation(void);
test_menu_t input_test_operation(void);
#endif
