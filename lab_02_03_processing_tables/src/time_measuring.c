#include "time_measuring.h"
#include <time.h>
#include "database_operations.h"
#include "table.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include "sort.h"
#include "utils.h"

// Выделение динамической памяти под массивы
static int memory_allocation(students_t **array_students_1, students_t **array_students_2, table_t **table_1, table_t **table_2)
{
    *array_students_1 = malloc(MAX_STUDENTS_COUNT * sizeof(students_t));
    if (array_students_1 == NULL)
        return ERR_MEMORY_ALLOCATION;

    *array_students_2 = malloc(MAX_STUDENTS_COUNT * sizeof(students_t));
    if (array_students_2 == NULL)
        return ERR_MEMORY_ALLOCATION;

    *table_1 = malloc(MAX_STUDENTS_COUNT * sizeof(table_t));
    if (table_1 == NULL)
        return ERR_MEMORY_ALLOCATION;

    *table_2 = malloc(MAX_STUDENTS_COUNT * sizeof(table_t));
    if (table_2 == NULL)
        return ERR_MEMORY_ALLOCATION;

    return ERR_OK;
}

static void print_table(measuring_t *measure_data, size_t read_count)
{
    printf("Проведено эксперементов: %zu\n", read_count);
    printf("Вывод результатов эксперемента в наносекундах\n");
    printf("|____|____________|_____________|_________________|__________________|\n");
    printf("|size| qsort main | mysort main | qsort key table | mysort key table |\n");
    printf("|____|____________|_____________|_________________|__________________|\n");
    int padding = 0;
    for (size_t i = 0; i < read_count; i++)
    {
        printf("|%*s%zu%*s|", 0, "", measure_data[i].size, 4 - (int)int_len(measure_data[i].size), "");

        // printf("$s ")
        padding = (12 - (int)int_len(measure_data[i].time_def_qsort)) / 2;
        printf("%*s%lld%*s|", padding, "", measure_data[i].time_def_qsort, 12 - padding - (int)int_len(measure_data[i].time_def_qsort), "");

        padding = (13 - (int)int_len(measure_data[i].time_def_mysort)) / 2;
        printf("%*s%lld%*s|", padding, "", measure_data[i].time_def_mysort, 13 - padding - (int)int_len(measure_data[i].time_def_mysort), "");

        padding = (17 - (int)int_len(measure_data[i].time_key_qsort)) / 2;
        printf("%*s%lld%*s|", padding, "", measure_data[i].time_key_qsort, 17 - padding - (int)int_len(measure_data[i].time_key_qsort), "");

        padding = (18 - (int)int_len(measure_data[i].time_key_mysort)) / 2;
        printf("%*s%lld%*s|\n", padding, "", measure_data[i].time_key_mysort, 18 - padding - (int)int_len(measure_data[i].time_key_mysort), "");
    }
    printf("|____|____________|_____________|_________________|__________________|\n");
}

// Функция реализует сравнение времени
int compare_times(void)
{
    printf("Измерение времени выполнения программы с обычной сортировкой и сортировкой с помощью таблицы ключей\n"
           "Чтобы выйти и получить результат, нажмите 0\n"
           "Максимальное количество файлов - 10\n\n");

    // Инициализация переменных
    measuring_t measure_data[MAX_EXP_FILES];
    students_t *array_students_1 = NULL, *array_students_2 = NULL;
    table_t *table_1 = NULL, *table_2 = NULL;
    struct timespec start, end;
    long long time, sum = 0;
    int rc = ERR_OK;
    size_t read_count = 0, count = 0;

    if ((rc = memory_allocation(&array_students_1, &array_students_2, &table_1, &table_2)) != ERR_OK)
        return rc;

    // Запуск основного цикла
    while (read_count < MAX_EXP_FILES)
    {
        // Получение имени файла
        char filename[MAX_PATH_LEN];
        printf("Введите название файла: ");
        if ((rc = input_string(filename, MAX_PATH_LEN)) != ERR_OK)
        {
            free(array_students_1);
            free(table_1);
            return rc;
        }

        // 0 - Если выход
        if (strcmp(filename, "0") == 0)
            break;

        // Открытие файла для чтения
        FILE *file = fopen(filename, "r");
        if (file == NULL)
        {
            free(array_students_1);
            free(table_1);
            return ERR_FILENAME;
        }
        measure_data[read_count].size = count;

        // Запуск эксперементов
        for (size_t i = 0; i < EXP_COUNT; i++)
        {
            rewind(file);
            if ((rc = database_import_students(file, array_students_1, &count)) != ERR_OK)
            {
                free(array_students_1);
                free(table_1);
                return rc;
            }

            clock_gettime(CLOCK_REALTIME, &start);
            qsort(array_students_1, count, sizeof(students_t), compare_surnames);
            clock_gettime(CLOCK_REALTIME, &end);
            time = (long long)((end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec));
            sum += time;
            measure_data[read_count].time_def_qsort = sum / EXP_COUNT;
            sum = 0;
        }

        for (size_t i = 0; i < EXP_COUNT; i++)
        {
            rewind(file);
            if ((rc = database_import_students(file, array_students_2, &count)) != ERR_OK)
            {
                free(array_students_1);
                free(array_students_2);
                free(table_1);
                free(table_2);
                return rc;
            }

            clock_gettime(CLOCK_REALTIME, &start);
            mysort(array_students_2, count, sizeof(students_t), compare_surnames);
            clock_gettime(CLOCK_REALTIME, &end);
            time = (long long)((end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec));
            sum += time;
            measure_data[read_count].time_def_mysort = sum / EXP_COUNT;
            sum = 0;
        }

        for (size_t i = 0; i < EXP_COUNT; i++)
        {
            rewind(file);
            if ((rc = database_import_students(file, array_students_1, &count)) != ERR_OK)
            {
                free(array_students_1);
                free(table_1);
                return rc;
            }
            create_key_table(table_1, array_students_1, count);

            clock_gettime(CLOCK_REALTIME, &start);
            mysort(table_1, count, sizeof(table_t), compare_table);
            clock_gettime(CLOCK_REALTIME, &end);
            time = (long long)((end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec));
            sum += time;
            measure_data[read_count].time_key_mysort = sum / EXP_COUNT;
            sum = 0;
        }

        for (size_t i = 0; i < EXP_COUNT; i++)
        {
            rewind(file);
            if ((rc = database_import_students(file, array_students_2, &count)) != ERR_OK)
            {
                free(array_students_1);
                free(array_students_2);
                free(table_1);
                free(table_2);
                return rc;
            }
            create_key_table(table_2, array_students_1, count);

            clock_gettime(CLOCK_REALTIME, &start);
            qsort(table_2, count, sizeof(table_t), compare_table);
            clock_gettime(CLOCK_REALTIME, &end);
            time = (long long)((end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec));
            sum += time;
            measure_data[read_count].time_key_qsort = sum / EXP_COUNT;
            sum = 0;
        }

        // Вывод
        printf("Таблица занимает в памяти - %lu байтов, Таблица ключей занимает в памяти - %lu байтов \n", sizeof(students_t) * count, sizeof(table_t) * count);

        measure_data[read_count].size = count;
        printf("В случае qsort, использование таблиц эффективнее на %.2f\n", (double)(measure_data[read_count].time_def_qsort - measure_data[read_count].time_key_qsort) / (double)measure_data[read_count].time_def_qsort * 100);
        // printf("qsort, эффективнее модернизированного bubble sort на %.2f%% (Для таблицы ключей)\n", (double)(measure_data[read_count].time_key_mysort - measure_data[read_count].time_key_qsort) / (double)measure_data[read_count].time_key_mysort * 100);
        // printf("qsort, эффективнее модернизированного bubble sort на %.2f%%\n", (double)(measure_data[read_count].time_def_mysort - measure_data[read_count].time_def_qsort) / (double)measure_data[read_count].time_def_mysort * 100);
        printf("Отношение быстрой сортировки основной таблицы к таблице ключей %.3f\n", (double)measure_data[read_count].time_def_qsort / (double)measure_data[read_count].time_key_qsort);
        printf("Отношение cортировки пузырьком основной таблицы к таблице ключей %.3f\n", (double)measure_data[read_count].time_def_mysort / (double)measure_data[read_count].time_key_mysort);
        read_count++;
    }

    // Вывод результатов
    print_table(measure_data, read_count);

    // Освобождение памяти
    free(array_students_1);
    free(array_students_2);
    free(table_1);
    free(table_2);
    return ERR_OK;
}
