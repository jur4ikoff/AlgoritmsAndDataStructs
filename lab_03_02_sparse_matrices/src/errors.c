#include <stdio.h>
#include "errors.h"
#include "constants.h"

/**
 * @brief Вывод сообщения об ошибки
 * @param arg Код ошибки
 */
void print_error_message(short int arg)
{
    switch (arg)
    {
    case ERR_RANGE_OPERATION:
        printf("Ошибка, диапазона при выборе операции. Можно число от 0 до %d\n", MAX_OPERATION);
        break;
    case ERR_INPUT_STRING:
        printf("Ошибка при вводе строки\n");
        break;
    case ERR_STRING_OVERFLOW:
        printf("Ошибка, переполнение размеров строки\n");
        break;
    case ERR_EMPTY_STRING:
        printf("Ошибка, ввод пустой строки\n");
        break;
    case ERR_FILE_INPUT:
        printf("Ошибка, при чтении из файла\n");
        break;
    case ERR_RANGE_MATRIX_SIZE:
        printf("Ошибка, размер матрицы может быть от 1 до %d\n", MAX_SIZE);
        break;
    case ERR_FILENAME:
        printf("Ошибка, неверное имя файла\n");
        break;
    case ERR_INPUT_INTEGER_NUMBER:
        printf("Ошибка при вводе целого числа\n");
        break;
    case ERR_INPUT_INTEGER_NUMBER_RANGE:
        printf("Ошибка, введенное число выходит за диапазон разрешенных значений\n");
        break;
    case ERR_MATRIX_SIZE_NOT_EQ:
        printf("Ошибка, при сложении, матрицы должны быть одинакого размера");
        break;
    }
}