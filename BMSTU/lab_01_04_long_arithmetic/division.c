#include "division.h"

void copy(number_t stream, number_t *destination, int start, int end)
{

    for (int i = start; i < end; i++)
    {
        if (i < stream.mantise_size)
            destination->mantise[i] = stream.mantise[i];
        // else
        // destination->mantise_size++;
        destination->order++;
    }
}

void copy_to_number(long long int *value, number_t number, size_t start, size_t end)
{
    *value = 0;
    // printf("%zu %zu\n", start, end);
    for (size_t i = start; i < end; i++)
    {
        *value = *value * 10 + number.mantise[i];
    }
}

void copy_to_number_t(long long value, number_t *dest)
{
    dest->order = 0;
    short mantise_index = 0;
    while (value > 0)
    {
        dest->mantise[mantise_index] = value % 10;
        value /= 10;
        mantise_index++;
    }
}

/*

int find_part_devisible(number_t divisible, number_t divider, int *part_divisible, int *part_len, number_t *result)
{
    int rc = ERR_OK;
    size_t i = 0;
    *part_len = 0;

    do
    {
        if (divisible.mantise[i] > divider.mantise[i])
            *part_len = divider.mantise_size;
        else if (divisible.mantise[i] == divider.mantise[i])
            i++;
        else
            *part_len = divider.mantise_size + 1;
    } while (*part_len == 0 && (int)i < divisible.mantise_size);

    if ((int)i == divisible.mantise_size)
        *part_len = i;

    if (*part_len == 0)
        *part_len = divisible.mantise_size + 1;

    if (divider.mantise_size > divisible.mantise_size)
        *part_len += divisible.mantise_size - divider.mantise_size;

    if ((rc = copy(part_divisible, divisible, 0, *part_len)) != ERR_OK)
        return rc;

    if ((int)*part_len > divisible.mantise_size)
    {
        printf("SRABOTALO\n");
        result->order -= (divisible.mantise_size - *part_len);
    }
    // *part_len = len_part;
    return ERR_OK;
}
int long_div(number_t divisible, number_t divider, number_t *result)
{
    result->order = divisible.order - divider.order;
    int rc = ERR_OK, part_divisible = 0, part_len = 0;
    if ((rc = find_part_devisible(divisible, divider, &part_divisible, &part_len, result)) != ERR_OK)
        return rc;
    short result_mantise_size = 0;

    int divider_value = 0;
    if ((rc = copy(&divider_value, divider, 0, divider.mantise_size)) != ERR_OK)
        return rc;

    printf("%d\n", part_divisible);
    printf("%d\n", divider_value);

    do
    {
        // int t1 = part_divisible / pow(10, part_len - 1);
        // int t2 = devider_value/ pow(10, part_len - 1);
        break;
    } while (result_mantise_size < MAX_MANTISE);

    // while (result_mantise_size < MAX_MANTISE)
    return ERR_OK;
}
*/

int find_part_divisible(number_t *part_divisible, number_t divisible, number_t divider, number_t *result)
{
    int i = 0; // rc = ERR_OK;
    do
    {
        if (divisible.mantise[i] > divider.mantise[i])
            part_divisible->mantise_size = divider.mantise_size;
        else if (divisible.mantise[i] < divider.mantise[i])
            part_divisible->mantise_size = divider.mantise_size + 1;
        else
            i++;

    } while (part_divisible->mantise_size == 0 && i < divisible.mantise_size && i < divider.mantise_size);

    if (i == divisible.mantise_size)
        part_divisible->mantise_size = i;

    if (part_divisible->mantise_size == 0)
        part_divisible->mantise_size = divisible.mantise_size + 1;

    if (divider.mantise_size > divisible.mantise_size)
        part_divisible->mantise_size += divider.mantise_size - divisible.mantise_size;

    copy(divisible, part_divisible, 0, part_divisible->mantise_size);
    if (part_divisible->mantise_size > divisible.mantise_size)
    {
        printf("SRABOTALO\n");
        part_divisible->mantise_size++;
        part_divisible->order++;
        result->order -= (divisible.mantise_size - part_divisible->mantise_size);
    }
    return ERR_OK;
}

void calculate_sign(number_t divisible, number_t divider, number_t *result)
{
    if (divisible.order == divider.order)
        result->order = 1;
    else
        result->order = 0;
}

int long_div(number_t divisible, number_t divider, number_t *result)
{
    result->order = divisible.order - divider.order;
    calculate_sign(divisible, divider, result);
    int rc = ERR_OK;
    number_t part_divisible = {0};
    if ((rc = find_part_divisible(&part_divisible, divisible, divider, result)) != ERR_OK)
        return rc;

    do
    {
        print_number(part_divisible);
        long long int t1, t2, t;
        copy_to_number(&t1, part_divisible, 0, part_divisible.order - divider.mantise_size + 1);
        copy_to_number(&t2, divider, 0, divider.order - divider.mantise_size + 1);
        t = t1 / t2;

        long long int mantise_divider, mantise_part_divisible; // TO DO МОЖЕТ БЫТЬ ПЕРЕПОЛНЕНИЕ
        copy_to_number(&mantise_divider, divider, 0, divider.mantise_size);
        copy_to_number(&mantise_part_divisible, part_divisible, 0, part_divisible.mantise_size);
        long long int mult = t * mantise_divider;
        // printf("mult = %lld mantise_divider = %lld, t = %lld, mant_div = %lld\n", mult, mantise_divider, t, mantise_part_divisible);
        if (mantise_part_divisible - mult > 0)
        {
            printf("%lld\n", mantise_part_divisible - mult);
        }
        else
        {
            t -= 1;
            mult = t * mantise_divider;
            printf("%lld\n", mantise_part_divisible - mult);
        }

        break;
    } while (part_divisible.mantise[0] != 0 /*&& Остаток не равен нулю*/ && result->mantise_size < MAX_MANTISE);

    return ERR_OK;
}
