// Вариант 3

#include <string.h>
#include <stdio.h>
#include "errors.h"
#include "constants.h"
#include "database_operations.h"
#include "menu_operations.h"
#include <stdlib.h>
#include "student_operations.h"

int main(int argc, char **argv)
{
    int rc = ERR_OK;
    char db_path[MAX_PATH_LEN], default_db_path[MAX_STRING_LEN] = {"./database.txt"};
    FILE *file;
    operations_t operation_number;
    size_t count = 0;

    // Выбор имени файла
    if (argc == 2)
    {
        if ((rc = database_choose_name(argv[1])) == 0)
            strncpy(db_path, argv[1], strlen(argv[1]));
        else
        {
            print_error_message(rc);
            return rc;
        }
    }
    else
        strncpy(db_path, default_db_path, strlen(default_db_path));
    printf("Выбран файл: %s\n", db_path);

    if ((rc = database_open(&file, db_path, "r+")) != ERR_OK)
    {
        print_error_message(rc);
        return rc;
    }

    students_t *array_students = NULL;
    array_students = malloc(MAX_STUDENTS_COUNT * sizeof(students_t));
    if (array_students == NULL)
    {
        print_error_message(ERR_MEMORY_ALLOCATION);
        return ERR_MEMORY_ALLOCATION;
    }

    if ((rc = database_import_students(file, array_students, count)) != ERR_OK)
    {
        print_error_message(rc);
        return rc;
    }

    while (rc)

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
        case EXIT:
            printf("Программа завершилась успешно\n");
            return ERR_OK;
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
        case PRINT_INFO:
            // Вывод информации о программе
            help();
            break;
        default:
            // Ошибка при выборе операции
            print_error_message(ERR_UNKNOWN);
            return ERR_UNKNOWN;
        }
    }
    return rc;
}
