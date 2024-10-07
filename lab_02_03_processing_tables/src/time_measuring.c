#include "time_measuring.h"
#include <time.h>
#include <stdio.h>
#include "database_operations.h"
#include "table.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>

#define MAX_EXP_FILES 10
typedef struct
{
    int size;
    long long time_def;
    long long time_key;
} measuring;

int compare_times()
{
    printf("Измерение времени выполнения программы с обычной сортировкой и сортировкой с помощью таблицы ключей\n"
           "Чтобы выйти и получить результат, нажмите 0\n"
           "Максимальное количество файлов - 10\n\n");

    // measuring measure_data[MAX_EXP_FILES];
    students_t *array_students = NULL;
    table_t *table = NULL;

    int rc = ERR_OK;
    size_t read_count = 0;

    array_students = malloc(MAX_STUDENTS_COUNT * sizeof(students_t));
    if (array_students == NULL)
        return ERR_MEMORY_ALLOCATION;

    table = malloc(MAX_STUDENTS_COUNT * sizeof(table_t));
    if (table == NULL)
        return ERR_MEMORY_ALLOCATION;

    while (read_count < MAX_EXP_FILES)
    {
        char filename[MAX_PATH_LEN];
        printf("Введите название файла: ");
        if ((rc = input_string(filename, MAX_PATH_LEN)) != ERR_OK)
        {
            free(array_students);
            free(table);
            return rc;
        }

        if (strcmp(filename, "0") == 0)
            break;

        FILE *file = fopen(filename, "r");
        if (file == NULL)
        {
            free(array_students);
            free(table);
            return ERR_FILENAME;
        }

        size_t count = 0;
        if ((rc = database_import_students(file, array_students, &count)) != ERR_OK)
        {
            free(array_students);
            free(table);
            return rc;
        }

        create_key_table(table, array_students, count);
        printf("Таблица занимает в памяти - %lu байтов, Таблица ключей занимает в памяти - %lu байтов \n", sizeof(students_t) * count, sizeof(table_t) * count);


        read_count++;
    }

    printf("Read %zu", read_count);
    return ERR_OK;
}