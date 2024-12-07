#ifndef MENU_H__
#define MENU_H__

typedef enum
{
    OP_EXIT,
    OP_INPUT_STRING,
    OP_BUILD_TREE,
    OP_CLEAN_TREE,
    OP_CLEAN_STRING,
    OP_PRINT_TREE,
    OP_TEST,
    OP_COUNT,
    OP_UNKNOWN
} operations_t;

void print_error_message(int arg);
void print_info(void);
void print_menu(void);
operations_t input_operation(void);
#endif
