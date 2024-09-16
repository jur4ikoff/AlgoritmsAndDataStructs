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

    if (strlen(string) < 1)
        return ERR_EMPTY_INPUT;
    return ERR_OK;
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

void print_number(number_t number)
{
    printf("%hd %hd %hd\n", number.sign, number.mantise_size, number.order);
    for (int i = 0; i < number.mantise_size; i++)
    {
        printf("%hd", number.mantise[i]);
    }
    printf("\n");
}
