// Вариант 3
#include "errors.h"
#include "string.h"
#include "stdio.h"
#include "constants.h"

typedef enum
{
    EXIT,
    ADD_RECORD,
    DELETE_RECORD,
    PRINT_SORT_KEY_TABLE,
    PRINT_SORT_ORIGINAL_TABLE,
    PRINT_TABLE_WITH_KEYS,
    SORT_COMPLEXITY,
    SORT_COMPARE,
    PRINT_INFO
} operations_t;

// Меню программы
void print_menu(void)
{
    printf(">Возможности программы\n"
           " 0 - Выход\n"
           " 1 - Добавить запись в конец таблицы\n 2 - Удалить запись по ключу\n"
           " 3 - Просмотр отсортированной таблицы ключей\n 4 - Вывод упорядоченной исходной таблицы\n"
           " 5 - Вывод исходной таблицы в упорядоченном виде, используя упорядоченную таблицу ключей\n"
           " 6 - Вывод результатов использования различных алгоритмов сортировок\n"
           " 7 - Вывод результатов сравнения эффективности работы программы\n"
           " 8 - Вывести иформацию о программе\n");
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
            // Вывод результатов сравнения эффективности работы программы
        case 8:
            // Вывод информации о программе
            help();

            break;
        default:
            print_error_message(ERR_UNKNOWN);
            return ERR_UNKNOWN;
        }
        // break;
    }
    return rc;
}
