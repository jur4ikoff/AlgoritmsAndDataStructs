#include "division.h"

int i_len(long long value)
{
    int count = 0;
    while (value > 0)
    {
        count++;
        value /= 10;
    }

    return count;
}
void copy(number_t stream, number_t *destination, int start, int end)
{

    for (int i = start; i < end; i++)
    {
        if (i < stream.mantise_size)
        {
            destination->mantise[i] = stream.mantise[i];
            destination->order++;
        }
        else
        {
            destination->mantise[i] = 0;
            destination->order++;
        }
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

void copy_to_struct(long long value, number_t *dest)
{
    // printf("%lld\n", value);
    dest->order = 0, dest->mantise_size = 0;
    char buffer[MAX_STRING_LEN];
    snprintf(buffer, sizeof(buffer), "%lld", value);

    for (size_t i = 0; i < (size_t)i_len(value); i++)
    {
        dest->mantise[dest->mantise_size] = buffer[i] - '0';
        dest->mantise_size++;
        dest->order++;
    }
}

void find_part_divisible(number_t *part_divisible, number_t divisible, number_t divider, number_t *result)
{
    int i = 0; // rc = ERR_OK;
    int size_mantise_to_copy = 0;
    if (divisible.mantise_size < divider.mantise_size)
    {
        size_mantise_to_copy = divider.mantise_size; // TO DO
        bool is_only_zero = true;
        for (size_t j = divisible.mantise_size; j < (size_t)divider.mantise_size; j++)
        {
            if (divider.mantise[j] != 0)
                is_only_zero = false;
        }
        if (!is_only_zero)
            size_mantise_to_copy += 1;
    }
    else
    {
        while (i < divider.mantise_size && size_mantise_to_copy == 0)
        {
            if (divisible.mantise[i] > divider.mantise[i])
                size_mantise_to_copy = divider.mantise_size + i;
            else if (divisible.mantise[i] < divider.mantise[i])
                size_mantise_to_copy = divider.mantise_size + i + 1;
            else
                i++;
        }
    }

    if (i == divider.mantise_size)
        size_mantise_to_copy = divider.mantise_size;

    part_divisible->mantise_size = size_mantise_to_copy;
    copy(divisible, part_divisible, 0, size_mantise_to_copy);

    /*do
    {
        printf("%d %d", divisible.mantise[i], divider.mantise[i]);
        if (divisible.mantise[i] > divider.mantise[i])
            part_divisible->mantise_size = divider.mantise_size + i;
        else if (divisible.mantise[i] < divider.mantise[i])
            part_divisible->mantise_size = divider.mantise_size + i + 1;
        else
            i++;

    } while (part_divisible->mantise_size == 0 && i < divisible.mantise_size && i < divider.mantise_size);

    if (i == divider.mantise_size && divisible.mantise[i - 1], divider.mantise[i - 1])
    */
    // printf("part_divisible->mantise_size = %d\n", part_divisible->mantise_size);

    /*if (i == divisible.mantise_size)
        part_divisible->mantise_size = i;

    if (part_divisible->mantise_size == 0)
        part_divisible->mantise_size = divisible.mantise_size + 1;

    if (divider.mantise_size > divisible.mantise_size)
        part_divisible->mantise_size += divider.mantise_size - divisible.mantise_size;*/

    // copy(divisible, part_divisible, 0, part_divisible->mantise_size);
    /*if (part_divisible->mantise_size > divisible.mantise_size)
    {
        printf("SRABOTALO\n");
        part_divisible->mantise_size++;
        part_divisible->order++;
        result->order -= (divisible.mantise_size - part_divisible->mantise_size);
    }*/
    (void)*result;
    // return ERR_OK;
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
    // int rc = ERR_OK;
    number_t part_divisible = {0};
    find_part_divisible(&part_divisible, divisible, divider, result);
    print_number(part_divisible);

    return 0;
    int last_index = part_divisible.mantise_size;
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
        // number_t remains = {0};
        if (mantise_part_divisible - mult > 0)
        {
            ;
        }
        else
        {
            while (mantise_part_divisible - mult < 0)
            {
                t -= 1;
                mult = t * mantise_divider;
            }

            // printf("%lld\n", mantise_part_divisible - mult);
        }
        printf("mult = %lld, t = %lld, part_mant_div = %lld\n", mult, t, mantise_part_divisible);
        // printf("%lld\n", t);
        result->mantise[result->mantise_size] = t;
        result->mantise_size++;
        result->order++;
        copy_to_struct(mantise_part_divisible - mult, &part_divisible);
        if (last_index < divisible.mantise_size)
        {
            part_divisible.mantise[part_divisible.mantise_size] = divisible.mantise[last_index];
            part_divisible.mantise_size++;
            part_divisible.order++;
            last_index++;
        }
        else
        {
            part_divisible.mantise[part_divisible.mantise_size] = 0;
            part_divisible.mantise_size++;
            result->order--;
            last_index++;
        }

        print_number(part_divisible);
        // break;
        print_number(*result);
    } while (part_divisible.mantise[0] != 0 && result->mantise_size < MAX_MANTISE);

    return ERR_OK;
}
