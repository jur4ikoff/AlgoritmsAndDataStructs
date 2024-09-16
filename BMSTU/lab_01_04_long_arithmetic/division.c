#include "division.h"

int copy(int *value, number_t number, size_t start, size_t end)
{
    // if ((int)end > number.mantise_size)
    //     return UNKNOWN_ERROR;

    *value = 0;
    for (size_t i = start; i < end; i++)
    {
        if ((int)i < number.mantise_size)
            *value = (*value * 10) + number.mantise[i];
        else
            *value = (*value * 10) + 0;
    }

    return ERR_OK;
}

int find_part_devider(number_t divisible, number_t divider, int *part_divisible, number_t *result)
{
    int rc = ERR_OK;
    size_t len_part = 0, i = 0;

    do
    {
        if (divisible.mantise[i] > divider.mantise[i])
            len_part = divider.mantise_size;
        else if (divisible.mantise[i] == divider.mantise[i])
            i++;
        else
            len_part = divider.mantise_size + 1;
    } while (len_part == 0 && (int)i < divisible.mantise_size);

    if ((int)i == divisible.mantise_size)
        len_part = i;

    if (len_part == 0)
        len_part = divisible.mantise_size + 1;

    if (divider.mantise_size > divisible.mantise_size)
        len_part += divisible.mantise_size - divider.mantise_size;

    if ((rc = copy(part_divisible, divisible, 0, len_part)) != ERR_OK)
        return rc;

    if (len_part > divisible.mantise_size)
    {
        printf("SRABOTALO");
        result->order -= (divisible.mantise_size - len_part);
    }
    return ERR_OK;
}
int long_div(number_t divisible, number_t divider, number_t *result)
{
    result->order = divisible.order - divider.order;
    int rc = ERR_OK, part_divisible = 0;
    if ((rc = find_part_devider(divisible, divider, &part_divisible, result)) != ERR_OK)
        return rc;
    short result_mantise_size = 0;

    do
    {

        break;
    } while (result_mantise_size < MAX_MANTISE);

    // while (result_mantise_size < MAX_MANTISE)
    return ERR_OK;
}
