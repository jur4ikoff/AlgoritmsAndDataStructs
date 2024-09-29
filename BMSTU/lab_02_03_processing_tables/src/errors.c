#include "errors.h"
#include "stdio.h"

void print_error_message(short int arg)
{
    switch (arg)
    {
    case ERR_INPUT:
        printf("Ошибка в таблице\n");
        break;
    case ERR_FILENAME:
        printf("Ошибка в имени файла\n");
        break;
    case ERR_UNKNOWN:
        printf("Неизвестная ошибка\n");
        break;
    case ERR_OPERATION_INPUT:
        printf("Ошибка при выборе операции\n");
        break;
    case ERR_OPERATION_COUNT:
        printf("Ошибка, введите число от 1 до 8\n");
        break;
    }
}
