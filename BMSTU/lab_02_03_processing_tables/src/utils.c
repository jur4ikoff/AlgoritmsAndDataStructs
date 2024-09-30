#include "utils.h"
#include <string.h>
#include "errors.h"

/**
 * @brief Функция для ввода строки
 */
int input_string(char *string, size_t max_len)
{
    if (!fgets(string, max_len, stdin))
        return ERR_INPUT;

    char *newline = strchr(string, '\n');
    if (!newline)
        return ERR_ADD_ORDER_STRING_OVERFLOW;

    *newline = 0;
    return ERR_OK;
}
