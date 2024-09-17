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
    dest->order = 0, dest->mantise_size = 0;
    char buffer[MAX_STRING_LEN];
    snprintf(buffer, sizeof(buffer), "%lld", value);

    for (size_t i = 0; i < 20; i++)
    {
        printf("%c", buffer[i]);
    }
    /*
short mantise_index = 0;
while (value > 0)
{
    dest->mantise[mantise_index] = value % 10;
    value /= 10;
    mantise_index++;
    dest->order++;
    dest->mantise_size++;
}*/
}

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
        // print_number(part_divisible);
        long long int t1, t2, t;
        copy_to_number(&t1, part_divisible, 0, part_divisible.order - divider.mantise_size + 1);
        copy_to_number(&t2, divider, 0, divider.order - divider.mantise_size + 1);
        t = t1 / t2;

        long long int mantise_divider, mantise_part_divisible; // TO DO МОЖЕТ БЫТЬ ПЕРЕПОЛНЕНИЕ
        copy_to_number(&mantise_divider, divider, 0, divider.mantise_size);
        copy_to_number(&mantise_part_divisible, part_divisible, 0, part_divisible.mantise_size);
        long long int mult = t * mantise_divider;
        // printf("mult = %lld mantise_divider = %lld, t = %lld, mant_div = %lld\n", mult, mantise_divider, t, mantise_part_divisible);
        number_t remains = {0};
        if (mantise_part_divisible - mult > 0)
        {
            // result->mantise[result->mantise_size] = t;
            // result->mantise_size++;
            // result->order++;
            // copy_to_number_t(mantise_part_divisible - mult, &remains);
            // print_number(remains);
            // printf("%lld\n", mantise_part_divisible - mult);
            ;
        }
        else
        {
            t -= 1;
            mult = t * mantise_divider;

            // printf("%lld\n", mantise_part_divisible - mult);
        }
        // printf("%lld\n", t);
        result->mantise[result->mantise_size] = t;
        result->mantise_size++;
        result->order++;
        copy_to_number_t(mantise_part_divisible - mult, &remains);
        print_number(remains);
        break;
    } while (part_divisible.mantise[0] != 0 /*&& Остаток не равен нулю*/ && result->mantise_size < MAX_MANTISE);

    return ERR_OK;
}
