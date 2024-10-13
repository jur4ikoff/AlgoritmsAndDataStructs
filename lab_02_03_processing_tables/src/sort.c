#include "sort.h"
#include <string.h>

int compare_surnames(const void *a, const void *b)
{
    students_t *students_a = (students_t *)a;
    students_t *students_b = (students_t *)b;
    // Сравнение по полю surname
    return strcmp(students_a->surname, students_b->surname);
}

int compare_table(const void *a, const void *b)
{
    table_t *table_a = (table_t *)a;
    table_t *table_b = (table_t *)b;

    return strcmp(table_a->surname, table_b->surname);
}

// Сортировка модифицированная пузырьком
void mysort(void *arr, size_t number, size_t width, int (*compare)(const void *, const void *))
{
    if (number < 2)
        return; // Если массив пуст или содержит один элемент, ничего не делаем

    char *array = (char *)arr;
    int swapped;
    size_t last_swap_index;

    do
    {
        swapped = 0;
        last_swap_index = 0; // Сброс последнего индекса обмена

        for (size_t i = 0; i < number - 1; i++)
        {
            // Сравниваем элементы с учётом их ширины
            if (compare(array + i * width, array + (i + 1) * width) > 0)
            {
                // Обмен элементов
                for (size_t j = 0; j < width; j++)
                {
                    char temp = array[i * width + j];
                    array[i * width + j] = array[(i + 1) * width + j];
                    array[(i + 1) * width + j] = temp;
                }
                swapped = 1;
                last_swap_index = i + 1; // Обновляем последний индекс обмена
            }
        }

        // Уменьшаем число сравнений в следующем проходе
        number = last_swap_index;

    } while (swapped);
}

/**
 * @brief Вывод таблицы с помощью таблицы ключей
 */
void print_table_with_keys(students_t *students_arr, table_t *table, size_t count)
{
    printf("|———|————————————————————————|————————————————————|——————————|—|————————————|————————————————|—————————————————————————————————\n");
    printf("| № |        Фамилия         |        Имя         |  Группа  |G|Средний балл|Год поступления | Вариантная часть                \n");
    printf("|———|————————————————————————|————————————————————|——————————|—|————————————|————————————————|—————————————————————————————————\n");
    for (size_t i = 0; i < count; i++)
    {
        int padding = (3 - 1) / 2;
        if (i < 10 || i >= 100)
        {
            printf("|%*s%zu%*s|", padding, "", i, 3 - padding - 1, "");
            student_print(students_arr[table[i].index_src]);
        }
        else
        {
            printf("| %zu|", i);
            student_print(students_arr[table[i].index_src]);
        }
    }
    printf("|———|————————————————————————|————————————————————|——————————|—|————————————|————————————————|—————————————————————————————————\n");
}
