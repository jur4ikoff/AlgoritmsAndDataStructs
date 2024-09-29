// Вариант 3
#include "errors.h"
#include "string.h"
#include "stdio.h"
#include "constants.h"

typedef enum
{
    EXIT,
    PRINT_INFO,
    ADD_RECORD,
    DELETE_RECORD,
    PRINT_SORT_KEY_TABLE,
    PRINT_SORT_ORIGINAL_TABLE,
    PRINT_TABLE_WITH_KEYS,
    SORT_COMPLEXITY,
    SORT_COMPARE
} operations_t;

// Меню программы
void print_menu(void)
{
    printf(">Возможности программы\n"
           " 0 - Выход"
           " 1 - Вывести иформацию о программе\n 2 - Добавить запись в конец таблицы\n 3 - Удалить запись по ключу"
           "\n 4 - Просмотр отсортированной таблицы ключей\n 5 - Вывод упорядоченной исходной таблицы;"
           "\n 6 - Вывод исходной таблицы в упорядоченном виде, используя упорядоченную таблицу ключей"
           "\n 7 - Вывод результатов использования различных алгоритмов сортировок"
           "\n 8 - Вывод результатов сравнения эффективности работы программы\n");
}

// TO DO
void help(void)
{
    printf("Программа предназначена для работы с таблицами\n");
    printf("Формат ввода: \n");
}

int input_operation(operations_t *operation)
{
    int operation_number;
    printf(">Выберите действие: ");
    if (scanf("%d", &operation_number) != 1)
        return ERR_OPERATION_INPUT;

    if (operation_number < 0 || operation_number > OPERATIONS_COUNT)
        return ERR_OPERATION_COUNT;

    *operation = (operations_t)operation_number;
    return ERR_OK;
}

int main(int argc, char **argv)
{
    int rc = ERR_OK;
    operations_t operation_number;
    if (argc == 2)
    {
        if (strcmp(argv[1], "-h") == 0)
            help();
    }

    
    print_menu();
    while (1)
    {
        if ((rc = input_operation(&operation_number)) != ERR_OK)
        {
            print_error_message(rc);
            return rc;
        }

        switch (operation_number)
        {
        case 1:
            // Вывести иформацию о программе
            break;
        case 2:
            // Добавить запись в конец таблицы
            break;
        case 3:
            // Удалить запись по ключу
            break;
        case 4:
            // Просмотр отсортированной таблицы ключей
            break;
        case 5:
            // Вывод упорядоченной исходной таблицы
            break;
        case 6:
            // Вывод исходной таблицы в упорядоченном виде, используя упорядоченную таблицу ключей
            break;
        case 7:
            // Вывод результатов использования различных алгоритмов сортировок
        case 8:
            // Вывод результатов сравнения эффективности работы программы
            break;
        default:
            print_error_message(ERR_UNKNOWN);
            return ERR_UNKNOWN;
        }
        // break;
    }
    return rc;
}
