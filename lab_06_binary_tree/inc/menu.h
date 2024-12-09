#ifndef MENU_H__
#define MENU_H__

typedef enum __oper_t_
{
    OP_EXIT,
    OP_TREE_TEST,
    OP_INPUT_STRING,
    OP_BUILD_TREE,
    OP_CLEAN_TREE,
    OP_CLEAN_STRING,
    OP_PRINT_TREE,
    OP_TEST,
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
    TEST_PRINT,
    TEST_COUNT,
    TEST_UNKNOWN,
} test_menu_t;

void print_error_message(int arg);
void print_info(void);
void print_menu(void);
void test_menu(void);
operations_t input_operation(void);
test_menu_t input_test_operation(void);
#endif
