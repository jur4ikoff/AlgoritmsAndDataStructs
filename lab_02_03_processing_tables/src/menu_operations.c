#include "errors.h"
#include <stdio.h>
#include "constants.h"
#include "menu_operations.h"

// Меню программы
void print_menu(void)
{
    printf(">>Возможности программы\n"
           " 0 - Выход\n"
           " 1 - Вывод текущей таблицы\n"
           " 2 - Добавить запись в конец таблицы\n"
           " 3 - Удалить запись по ключу\n"
           " 4 - Поиск информации по вариантному полю\n"
           " 5 - Просмотр отсортированной таблицы ключей\n"
           " 6 - Вывод упорядоченной исходной таблицы (Сортировка qsort)\n"
           " 7 - Вывод упорядоченной исходной таблицы\n"
           " 8 - Вывод исходной таблицы в упорядоченном виде, используя упорядоченную таблицу ключей\n"
           " 9 - Вывод результатов использования различных алгоритмов сортировок\n"
           " 10 - Вывод результатов сравнения эффективности работы программы\n"
           " 11 - Сохранить\n"
           " 12 - Вывести иформацию о программе\n");
}

int input_operation(operations_t *operation)
{
    int operation_number;
    printf(">>Выберите действие: ");
    if (scanf("%d", &operation_number) != 1)
        return ERR_OPERATION_INPUT;
    fgetc(stdin);

    if (operation_number < 0 || operation_number > OPERATIONS_COUNT)
        return ERR_OPERATION_COUNT;

    *operation = (operations_t)operation_number;
    return ERR_OK;
}

// TO DO
void help(void)
{
    printf("Программа предназначена для работы с таблицами\n"
           "Разделителем в файле выступает символ - ;"
           "Сортировка по ключу фамилия");
}
