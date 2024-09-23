#include "division.h"

void find_part_divisible(long_number *part_divisible, long_number divisible, long_number divider)
{
    int i = 0;
    int size_mantise_to_copy = 0;
    if (divisible.mantise_size < divider.mantise_size)
    {
        size_mantise_to_copy = divider.mantise_size;
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
                size_mantise_to_copy = divider.mantise_size; // + i;
            else if (divisible.mantise[i] < divider.mantise[i])
                size_mantise_to_copy = divider.mantise_size + 1; // + i + 1;
            else
                i++;
        }
    }

    if (i == divider.mantise_size)
        size_mantise_to_copy = divider.mantise_size;

    part_divisible->mantise_size = size_mantise_to_copy;
    copy(divisible, part_divisible, 0, size_mantise_to_copy);
}

void calculate_sign(long_number divisible, long_number divider, long_number *result)
{
    // printf("signs = %u %u\n", divisible.order, divider.order);
    if (divisible.sign == divider.sign)
        result->sign = 1;
    else
        result->sign = 0;
}

void delete_nulls_from_divider(long_number *divisible, long_number *divider)
{
    while (divider->mantise_size != divider->order)
    {
        // divider->mantise[divider->mantise_size] = 0;
        // divider->mantise_size++;
        divider->order++;
        divisible->mantise[divisible->mantise_size] = 0;
        divisible->mantise_size++;
        divisible->order++;
    }
    // (void)*divisible;
}

int long_div(long_number divisible, long_number divider, long_number *result)
{
    // Вычисление нового порядка и знака
    // result->order = divisible.order - divider.order;
    calculate_sign(divisible, divider, result);
    // bool is_first_add = true;
    delete_nulls_from_divider(&divisible, &divider);
    // Получаем неполное делимое
    long_number part_divisible = {.sign = 1};
    find_part_divisible(&part_divisible, divisible, divider);
    int last_index = part_divisible.mantise_size;
    result->order = divisible.order - part_divisible.order + 1;

    //print_number(divisible);
    //print_number(divider);
    // print_number(part_divisible);
    long long int t1, t2, t;
    copy_to_number(&t2, divider, 0, divider.order - divider.mantise_size + 1);

    while (part_divisible.mantise[0] != 0 && result->mantise_size < MAX_MANTISE)
    {
        if (copy_to_number(&t1, part_divisible, 0, part_divisible.mantise_size - divider.mantise_size + 1) == 1)
        {
            t1 = 0;
        }
        if (t2 != 0)
            t = t1 / t2;
        else
            t = 1;

        long long int mantise_divider, mantise_part_divisible;              // TO DO МОЖЕТ БЫТЬ ПЕРЕПОЛНЕНИЕ
        copy_to_number(&mantise_divider, divider, 0, divider.mantise_size); // STATIC
        copy_to_number(&mantise_part_divisible, part_divisible, 0, part_divisible.mantise_size);
        long long int mult = t * mantise_divider;

        if (mantise_part_divisible - mult <= 0)
        {
            while (mantise_part_divisible - mult < 0)
            {
                t -= 1;
                mult = t * mantise_divider;
            }
        }

        // TO DO ПЕРЕПИСАТЬ

        result->mantise[result->mantise_size] = t;
        result->mantise_size++;
        // result->order++;

        copy_to_struct(mantise_part_divisible - mult, &part_divisible);
        if (last_index < divisible.mantise_size)
        {
            part_divisible.mantise[part_divisible.mantise_size] = divisible.mantise[last_index];
            part_divisible.mantise_size++;
            // result->order++;
            last_index++;
        }
        else
        {
            part_divisible.mantise[part_divisible.mantise_size] = 0;
            part_divisible.mantise_size++;
            // if (!is_first_add)
            //     ;
            //  result->order--;
            // else
            //     is_first_add = false;
            last_index++;
        }

        // printf("RES  ");
        // print_number(*result);
    }
    return ERR_OK;
}
