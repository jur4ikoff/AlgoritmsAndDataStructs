#include "const.h"
#include "long_types.h"
#include "assert.h"

// Копирование числа из одной структуры в другую
void copy_from_long_number_to_mantise_t(long_number stream, mantise_t *destination, int start, int end)
{
    destination->mantise_size = 0;
    for (int i = start; i < end; i++)
    {
        if (i < stream.mantise_size)
        {
            destination->mantise[i] = stream.mantise[i];
            destination->mantise_size++;
        }
        else
        {
            destination->mantise[i] = 0;
            destination->mantise_size++;
        }
    }
}

// Функция копирует переменную
int struct_copy(mantise_t stream, mantise_t *destination, size_t start, size_t end)
{
    if (start > MAX_MANTISE || end > MAX_MANTISE)
        return ERR_INPUT;

    destination->mantise_size = 0;
    for (size_t i = start; i < end; i++)
    {
        destination->mantise[i] = stream.mantise[i];
        destination->mantise_size++;
    }
    return ERR_OK;
}

// Функция для сравнения значения value и mantise_t number
int equivalent(long long value, mantise_t number) {  
    long long number_value = 0;  

    // Составление целого числа из массива коротких целых чисел  
    for (int i = 0; i < number.mantise_size; i++) {  
        number_value = (number_value << 16) | (unsigned short)(number.mantise[i] & 0xFFFF);  
    }  

    // Сравнение результатов  
    if (number_value == value) {  
        return 1; // Значения равны  
    } else {  
        return 0; // Значения равны  
    }  
}  

int mantise_subtraction(mantise_t first, mantise_t second)
{
    
}

// Деление нацело
int divide_mantise(mantise_t first, mantise_t second)
{

}