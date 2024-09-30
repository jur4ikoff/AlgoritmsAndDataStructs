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
        printf("Ошибка в имени файла. Возможно файла не существует\n");
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
    case ERR_STRING_OVERFLOW:
        printf("Ошибка, переполнение при вводе строки\n");
        break;
    case ERR_EMPTY_DATABASE:
        printf("Ошибка, выбранный файл - пустой\n");
        break;
    }
}

// TO DO
void help(void)
{
    printf("Программа предназначена для работы с таблицами\n"
           "Разделителем в файле выступает символ - ;");
    printf("Формат ввода: \n");
}
