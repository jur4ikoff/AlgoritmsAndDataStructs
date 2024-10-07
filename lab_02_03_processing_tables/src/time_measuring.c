#include "time_measuring.h"
#include <time.h>
#include "database_operations.h"
#include "table.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include "sort.h"

int compare_times()
{
    printf("Измерение времени выполнения программы с обычной сортировкой и сортировкой с помощью таблицы ключей\n"
           "Чтобы выйти и получить результат, нажмите 0\n"
           "Максимальное количество файлов - 10\n\n");

    measuring measure_data[MAX_EXP_FILES];
    students_t *array_students_1 = NULL, *array_students_2 = NULL;
    table_t *table_1 = NULL, *table_2 = NULL;
    struct timespec start, end;
    long long time;

    int rc = ERR_OK;
    size_t read_count = 0;

    array_students_1 = malloc(MAX_STUDENTS_COUNT * sizeof(students_t));
    if (array_students_1 == NULL)
        return ERR_MEMORY_ALLOCATION;

    array_students_2 = malloc(MAX_STUDENTS_COUNT * sizeof(students_t));
    if (array_students_2 == NULL)
        return ERR_MEMORY_ALLOCATION;

    table_1 = malloc(MAX_STUDENTS_COUNT * sizeof(table_t));
    if (table_1 == NULL)
        return ERR_MEMORY_ALLOCATION;

    table_2 = malloc(MAX_STUDENTS_COUNT * sizeof(table_t));
    if (table_2 == NULL)
        return ERR_MEMORY_ALLOCATION;

    while (read_count < MAX_EXP_FILES)
    {
        char filename[MAX_PATH_LEN];
        printf("Введите название файла: ");
        if ((rc = input_string(filename, MAX_PATH_LEN)) != ERR_OK)
        {
            free(array_students_1);
            free(table_1);
            return rc;
        }

        if (strcmp(filename, "0") == 0)
            break;

        FILE *file = fopen(filename, "r");
        if (file == NULL)
        {
            free(array_students_1);
            free(table_1);
            return ERR_FILENAME;
        }

        size_t count = 0;
        if ((rc = database_import_students(file, array_students_1, &count)) != ERR_OK)
        {
            free(array_students_1);
            free(table_1);
            return rc;
        }
        printf("%zu\n", count);
        rewind(file);
        if ((rc = database_import_students(file, array_students_2, &count)) != ERR_OK)
        {
            free(array_students_1);
            free(array_students_2);
            free(table_1);
            free(table_2);
            return rc;
        }

        create_key_table(table_1, array_students_1, count);
        create_key_table(table_2, array_students_1, count);

        printf("Таблица занимает в памяти - %lu байтов, Таблица ключей занимает в памяти - %lu байтов \n", sizeof(students_t) * count, sizeof(table_t) * count);
        measure_data[read_count].size = count;

        clock_gettime(CLOCK_REALTIME, &start);
        qsort(array_students_1, count, sizeof(students_t), compare_surnames);
        clock_gettime(CLOCK_REALTIME, &end);
        time = (long long)((end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec));
        measure_data[read_count].time_def_qsort = time;

        clock_gettime(CLOCK_REALTIME, &start);
        mysort(array_students_2, count, sizeof(students_t), compare_surnames);
        clock_gettime(CLOCK_REALTIME, &end);
        time = (long long)((end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec));
        measure_data[read_count].time_def_mysort = time;

        clock_gettime(CLOCK_REALTIME, &start);
        mysort(table_1, count, sizeof(table_t), compare_table);
        clock_gettime(CLOCK_REALTIME, &end);
        time = (long long)((end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec));
        measure_data[read_count].time_key_mysort = time;

        clock_gettime(CLOCK_REALTIME, &start);
        mysort(table_2, count, sizeof(table_t), compare_table);
        clock_gettime(CLOCK_REALTIME, &end);
        time = (long long)((end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec));
        measure_data[read_count].time_key_qsort = time;
        read_count++;
    }

    printf("Проведено эксперементов: %zu\n", read_count);
    printf("Вывод результатов эксперемента\n");
    printf("size  qsort_arr  mysort_arr  qsort_table  mysort_table\n");
    for (size_t i = 0; i < read_count; i++)
    {
        printf("%zu   ", measure_data[i].size);
        printf("%llu   ", measure_data[i].time_def_qsort);
        printf("%llu   ", measure_data[i].time_def_mysort);
        printf("%llu   ", measure_data[i].time_key_qsort);
        printf("%llu\n", measure_data[i].time_key_mysort);
    }

    free(array_students_1);
    free(array_students_2);
    free(table_1);
    free(table_2);
    return ERR_OK;
}