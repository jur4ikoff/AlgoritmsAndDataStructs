#ifndef MENU_H__
#define MENU_H__

typedef enum __oper_t_
{
    OP_EXIT,
    OP_TEST_TREE,
    OP_INPUT_STRING,
    OP_BUILD_TREE,
    OP_SHOW_TREE,
    OP_CLEAN_TREE,
    OP_CLEAN_STRING,
    OP_PREORDER_TREE,
    OP_INORDER_TREE,
    OP_POSTORDER_TREE,
    OP_EFFICIENCY,
    OP_COUNT,
    OP_UNKNOWN
} operations_t;

typedef enum __test_oper_t_
{
    TEST_EXIT,
    TEST_SHOW,
    TEST_ADD,
    TEST_REMOVE,
    TEST_SEARCH,
    TEST_PREORDER,
    TEST_INORDER,
    TEST_POSTRDER,
    TEST_COUNT,
    TEST_UNKNOWN,
} test_menu_t;

void print_error_message(int arg);
void print_warning_message(int arg);
void print_info(void);
void print_menu(void);
void test_menu(void);
operations_t input_operation(void);
test_menu_t input_test_operation(void);
#endif
