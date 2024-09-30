#include "database_operations.h"
#include <stdio.h>
#include "errors.h"
#include "constants.h"
#include <string.h>
#include "student_operations.h"

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

    if (strlen(string) > MAX_PATH_LEN)
        return ERR_STRING_OVERFLOW;

    /*char *newline = strchr(string, '\n');
    if (!newline)
        return ERR_STRING_OVERFLOW;
    *newline = '\0';*/

    // Проверка файла на существование
    if ((rc = database_open(&file, string, "r")) != ERR_OK)
        return rc;
    fclose(file);

    return ERR_OK;
}

int database_import_students(FILE *file, students_t *students, size_t *count)
{
    *count = 0;
    int rc = ERR_OK;
    while (rc != END_OF_FILE)
    {
        if ((rc = student_input(file, students, *count)) == ERR_OK)
        {
            (*count)++;
            if (*count > MAX_STUDENTS_COUNT)
                return ERR_TOO_MANY_STUDENTS;
        }
        else if (rc == END_OF_FILE)
            return ERR_OK;
        else
            return rc;
    }

    return rc;
}

int database_save(char *filename, students_t *students, size_t count)
{
    FILE *file;
    int rc = ERR_OK;
    if ((rc = database_open(&file, filename, "w")) != ERR_OK)
        return rc;

    for (size_t i = 0; i < count; i++)
    {
        student_save(file, students[i]);
    }

    printf(">>Изменения сохранены\n");
    return rc;
}

/**
 * @brief Функция вывода таблицы студентов на экран
 */
void database_print(students_t *array_students, size_t count)
{
    for (size_t i = 0; i < count; i++)
    {
        student_print(array_students[i]);
    }
}