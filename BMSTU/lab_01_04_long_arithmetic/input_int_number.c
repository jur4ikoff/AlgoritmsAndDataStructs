#include "input_int_number.h"

// Функция реализует ввод целого числа в тип данных 
int input_int_in_struct(number_t *number, char *message)
{
    int rc = ERR_OK;
    char buffer[MAX_STRING_LEN];

    printf("%s\n", message);
    printf(">");
    if ((rc = input_string(buffer)) != ERR_OK)
        return rc;

    char *ptr = buffer;
    check_sign(number, &ptr);
    // printf("%s\n", ptr);
    int point_count = count_symbols(ptr, '.');
    if (point_count > 1)
        return ERR_POINTS_COUNT;
    if ((rc = find_exp(number, ptr)) != ERR_OK)
        return rc;
    if ((rc = process_number(number, ptr)) != ERR_OK)
        return rc;
    return rc;
}