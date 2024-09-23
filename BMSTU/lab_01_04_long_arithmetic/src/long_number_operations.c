#include "long_types.h"
#include <stdbool.h>
#include "utils.h"

// Вычисление знака результата
void calculate_sign(long_number divisible, long_number divider, long_number *result)
{
    if (divisible.sign == divider.sign)
        result->sign = 1;
    else
        result->sign = 0;
}

// Удаление дробной части из делителя
void delete_fractional_part_from_divider(long_number *divisible, long_number *divider)
{
    while (divider->mantise_size != divider->order)
    {
        divider->order++;
        divisible->mantise[divisible->mantise_size] = 0;
        divisible->mantise_size++;
        divisible->order++;
    }
}

// Вычисление неполного делимого
void find_part_divisible(mantise_t *part_divisible, long_number divisible, long_number divider)
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
                size_mantise_to_copy = divider.mantise_size;
            else if (divisible.mantise[i] < divider.mantise[i])
                size_mantise_to_copy = divider.mantise_size + 1;
            else
                i++;
        }
    }

    if (i == divider.mantise_size)
        size_mantise_to_copy = divider.mantise_size;

    copy_from_long_number_to_mantise_t(divisible, part_divisible, 0, size_mantise_to_copy);
}

int long_divisible(long_number divisible, long_number divider, long_number *result)
{
    // Нормализуем данные на входе
    calculate_sign(divisible, divider, result);
    delete_fractional_part_from_divider(&divisible, &divider);

    // Получаем неполное делимое
    mantise_t part_divisible = {.mantise_size = 0};
    find_part_divisible(&part_divisible, divisible, divider);
    // int last_index = part_divisible.mantise_size;

    // Вычисление порядка результата
    result->order = divisible.order - part_divisible.mantise_size + 1;
    
    // Служебные переменные
    mantise_t t1, t2;// t;
    copy_from_long_number_to_mantise_t(divider, &t2, 0, divider.order - divider.mantise_size + 1);

    while (part_divisible.mantise[0] != 0 && result->mantise_size < MAX_MANTISE)
    {
        struct_copy(part_divisible, &t1, 0, part_divisible.mantise_size - divider.mantise_size + 1); // TO DO ПРОВЕРИТЬ
        
        /*
        if (t2.mantise[0] != 0)
            t = t1 / t2;
        else
            t = 1;
        break;
        
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
        }*/
    }
    return ERR_OK;
}
