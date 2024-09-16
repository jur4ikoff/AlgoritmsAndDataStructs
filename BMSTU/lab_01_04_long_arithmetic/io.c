#include "io.h"
#include "input_number.h"

int input_string(char *string)
{
    if (!fgets(string, MAX_STRING_LEN, stdin))
        return ERR_INPUT;

    char *newline = strchr(string, '\n');
    if (!newline)
        return ERR_OVERFLOW;

    *newline = 0;

    return ERR_OK;
}

void print_error(int arg)
{
    switch (arg)
    {
    case ERR_INPUT_CHAR:
        printf("Error, number must not contain any characters\n");
        break;
    case ERR_MANTISE_SIZE:
        printf("Error in mantise size. It's must be short then 40 digits\n");
        break;
    case ERR_ORDER_SIZE:
        printf("Error in order size. It's must be short then 5 digits\n");
        break;
    case ERR_OVERFLOW:
        printf("Error, overflow\n");
        break;
    case ERR_INPUT:
        printf("Error while input\n");
        break;
    case ERR_NOT_FLOAT:
        printf("Error, input number not a real number\n");
        break;
    case ERR_ORDER_CHAR:
        printf("Error, order contain char\n");
        break;
    case ERR_POINTS_COUNT:
        printf("Error, point must be only one\n");
        break;
    }
}

int input_number(number_t *number)
{
    int rc = ERR_OK;
    char buffer[MAX_STRING_LEN];

    if ((rc = input_string(buffer)) != ERR_OK)
        return rc;

    int point_count = count_symbols(buffer, '.');
    if (point_count > 1)
        return ERR_POINTS_COUNT;

    if ((rc = find_exp(number, buffer)) != ERR_OK)
        return rc;

    if ((rc = process_number(number, buffer)) != ERR_OK)
        return rc;

    return rc;
}
