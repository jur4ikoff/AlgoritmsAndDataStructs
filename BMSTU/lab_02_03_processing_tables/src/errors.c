#include "errors.h"
#include "stdio.h"

void print_error_message(short int arg)
{
    switch (arg)
    {
    case ERR_INPUT:
        printf("Ошибка ввода\n");
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
    case ERR_MEMORY_ALLOCATION:
        printf("Ошибка при выделении памяти\n");
        break;
    case ERR_FILE_ORDER_INPUT:
        printf("Ошибка в чтении строки файла\n");
        break;
    case ERR_FILE_ORDER_OVERFLOW:
        printf("Ошибка, переполнение записи. Возможно, нужно добавить '\\n' в конец строки\n");
        break;
    case ERR_TOO_LONG_FIELD:
        printf("Ошибка, одно из полей слишком длинное\n");
        break;
    case ERR_CONVERTATION_DOUBLE:
        printf("Ошибка, неверно введен средний балл\n");
        break;
    case ERR_UNKNOWN_TYPE:
        printf("Ошибка в типе, можно вводить только: F - flat, H - hostel, R - rental\n");
        break;
    case ERR_UNKNOWN_GENDER:
        printf("Ошибка в написании пола. Можно указать только M - Мужской и F - Женский");
        break;
    case ERR_TOO_MANY_STUDENTS:
        printf("Ошибка, введено больше 1000 студентов - переполнение\n");
        break;
    case ERR_FILE_SAVE:
        printf("Ошибка при сохранении файла\n");
        break;
    case ERR_ADD_ORDER_INPUT:
        printf("Ошибка при вводе новой записи\n");
        break;
    case ERR_ADD_ORDER_STRING_OVERFLOW:
        printf("Ошибка, переполнение при вводе новой записи\n");
        break;
    }
}
