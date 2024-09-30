// Вариант 3
#include "errors.h"
#include "string.h"
#include "stdio.h"
#include "constants.h"
#include "students_struct.h"
#include "operations.h"

int database_open(FILE **file, char *filename, char *mode)
{
    *file = fopen(filename, mode);

    if (*file == NULL)
        return ERR_FILENAME;

    return ERR_OK;
}

int database_choose_name(char *string)
{
    FILE *file;
    int rc;

    // Ввод имени файла
    printf("> Введите относительный путь к файлу с таблицей:\n");
    if (!fgets(string, MAX_STRING_LEN, stdin))
        return ERR_INPUT;
    char *newline = strchr(string, '\n');
    if (!newline)
        return ERR_STRING_OVERFLOW;
    *newline = '\0';

    // Проверка файла на существование
    if ((rc = database_open(&file, string, "r")) != ERR_OK)
        return rc;
    fclose(file);

    return ERR_OK;
}

int main(int argc, char **argv)
{
    int rc = ERR_OK;
    char db_path[] = {"./database.txt"};
    operations_t operation_number;

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
        case CHOOSE_DB:
            // Выбор имени базы данных
            if ((rc = database_choose_name(db_path)) != ERR_OK)
            {
                print_error_message(rc);
                return rc;
            }
            printf(">Выбран файл: %s\n", db_path);
            break;
        case PRINT_INFO:
            // Вывод информации о программе
            help();
            break;
        default:
            print_error_message(ERR_UNKNOWN);
            return ERR_UNKNOWN;
        }
    }
    return rc;
}
