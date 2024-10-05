#ifndef OPER_H
#define OPER_H

typedef enum
{
    EXIT,
    PRINT_SOURCE,
    ADD_RECORD,
    DELETE_RECORD,
    SEARCH_RECORD,
    SORT_KEY_TABLE,
    PRINT_SORT_ORIGINAL_TABLE,
    PRINT_TABLE_WITH_KEYS,
    SORT_COMPLEXITY,
    SORT_COMPARE,
    SAVE,
    PRINT_INFO

} operations_t;

void print_menu(void);
int input_operation(operations_t *operation);
void help(void);

#endif
