#include "long_types.h"
#include <stdbool.h>
#include "utils.h"
#include "inttypes.h"

/**  Проверяет, является ли все числа массива одинаковыми
 * @param array массив целочисленных цифр
 * @param n Длина массива
 * @param out 1 - Все цифры одинаковы, 0 - в ином случае
 */
int is_array_digits_equivalent(short array[], size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = i + 1; j < n; j++)
        {
            if (array[i] != array[j])
                return 0;
        }
    }
    return 1;
}

// Округление мантисы
void rounding(long_number *number)
{
    if (number->mantise_size == 39)
        printf("1");
    if (is_array_digits_equivalent(number->mantise, number->mantise_size) == 1)
        number->mantise[number->mantise_size - 1] += 1;
}

/*int rounding(long_number *result, int current_number)
{
    // Остановка функции в случае если 41-ая цифра меньше 5
    if (current_number < 5)
    {
        return 0;
    }
    int i = 39;
    // Цикл округления
    while (i >= 0)
    {
        // Увеличение первой цифры, не являющеся девяткой, на единицу и остановка округления
        if (result->mantise[i] != '9')
        {
            result->mantise[i] += 1;
            return 0;
        }
        // В случае если несколько последних цифр ялвяются двеятками - уменьшение длины мантиссы и переход к более ранней цифре
        else
        {
            result->mantise[i--] = '\0';
            result->mantise_size -= 1;
        }
    }
    // Резервная проверка случае числа 0.(9); в теории делением в данном варианте недостижима
    // Устанавливает мантиссу на 0.1, её длину на 1 и увеличивает экспоненту на 1
    if (i < 0)
    {
        result->mantise[0] = '1';
        result->order += 1;
        result->mantise_size += 1;
    }
    return 0;
}*/

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
                size_mantise_to_copy = divider.mantise_size;
            else if (divisible.mantise[i] < divider.mantise[i])
                size_mantise_to_copy = divider.mantise_size + 1;
            else
                i++;
        }
    }

    if (i == divider.mantise_size)
        size_mantise_to_copy = divider.mantise_size;

    copy_structs(divisible, part_divisible, 0, size_mantise_to_copy);
}

int long_divisible(long_number divisible, long_number divider, long_number *result)
{
    // Нормализуем данные на входе
    calculate_sign(divisible, divider, result);
    delete_fractional_part_from_divider(&divisible, &divider);

    // Получаем неполное делимое
    long_number part_divisible = {.sign = 1, .mantise_size = 0};
    find_part_divisible(&part_divisible, divisible, divider);
    int last_index = part_divisible.mantise_size;

    // Вычисление порядка результата
    result->order = divisible.order - part_divisible.mantise_size + 1;

    // Служебные переменные
    long long t1, t2, t;
    copy_to_variable(divider, &t2, 0, divider.order - divider.mantise_size + 1);

    while (part_divisible.mantise[0] != 0 && result->mantise_size < MAX_MANTISE)
    {
        copy_to_variable(part_divisible, &t1, 0, part_divisible.mantise_size - divider.mantise_size + 1);
        if (t2 != 0)
            t = t1 / t2;
        else
            t = 1;

        long long int mantise_divider, mantise_part_divisible;
        copy_to_variable(divider, &mantise_divider, 0, divider.mantise_size);
        copy_to_variable(part_divisible, &mantise_part_divisible, 0, part_divisible.mantise_size);

        long long int mult = t * mantise_divider;
        if (mantise_part_divisible - mult <= 0)
        {
            while (mantise_part_divisible - mult < 0 && t >= 10)
            {
                t -= 1;
                mult = t * mantise_divider;
            }
        }

        if (t < 0)
            mult = 0;

        result->mantise[result->mantise_size] = t;
        result->mantise_size++;

        copy_to_struct(mantise_part_divisible - mult, &part_divisible);

        if (last_index < divisible.mantise_size)
        {
            part_divisible.mantise[part_divisible.mantise_size] = divisible.mantise[last_index];
            part_divisible.mantise_size++;
            last_index++;
        }
        else
        {
            part_divisible.mantise[part_divisible.mantise_size] = 0;
            part_divisible.mantise_size++;
            last_index++;
        }
    }

    rounding(result);
    return ERR_OK;
}
