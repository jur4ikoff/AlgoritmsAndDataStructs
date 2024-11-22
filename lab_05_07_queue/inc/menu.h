#ifndef __MENU__H__
#define __MENU__H__

// Перечислячемый тип данных для определения операций, доступных из главного меню программы, в виде строковых литералов
typedef enum
{
    OP_EXIT,
    OP_TEST_STATIC,
    OP_TEST_LIST,
    OP_SIMULATION,
    OP_EFFICIENCY,
    OP_COUNT,
    OP_INIT

} operations_t;

typedef enum
{
    TEST_EXIT,
    TEST_PRINT,
    TEST_ADD,
    TEST_POP,
    TEST_COUNT,
    TEST_INIT
} test_operations_t;

void print_menu(void);
void print_test_menu(void);
void print_error_message(int arg);

int input_menu_operation(operations_t *operation);
int input_test_operation(test_operations_t *operation);
#endif
