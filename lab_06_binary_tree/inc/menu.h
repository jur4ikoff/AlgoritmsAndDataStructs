#ifndef MENU_H__
#define MENU_H__

typedef enum
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

typedef enum __test_menu_op_t
{
    TEST_EXIT,
    TEST_ADD,
    TEST_REMOVE,
    TEST_SEARCH,
    TEST_SHOW,
    TEST_PRINT,
    TEST_MENU_COUNT,
    TEST_MENU_UNKNOWN,
} test_menu_t;

void print_error_message(int arg);
void print_info(void);
void print_menu(void);
operations_t input_operation(void);
#endif
