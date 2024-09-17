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

int input_number(number_t *number, char *message)
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

void print_number(number_t number)
{
    printf("sign - %hd mant_size = %hd order = %hd\n", number.sign, number.mantise_size, number.order);
    printf("0.");
    for (int i = 0; i < number.mantise_size; i++)
    {
        // if number.mantise[i] == 0;
        printf("%hd", number.mantise[i]);
    }
    printf("e%hd\n", number.order);
}
