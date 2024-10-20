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
    case ERR_INPUT_OPERATION:
        printf("Ошибка ввода операции\n");
        break;
    case ERR_RANGE_OPERATION:
        printf("Ошибка, диапазона при выборе операции. Можно число от 0 до %d\n", MAX_OPERATION);
        break;
    }
}