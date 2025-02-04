#include <stdlib.h>
#include <stdbool.h>
#include "default_matrix.h"
#include "constants.h"
#include "errors.h"
#include "utils.h"
#include <time.h>

/**
 * @brief Функция для считывания матрицы из файла
 */
int create_default_matrix(matrix_t *matrix, size_t row, size_t column)
{
    matrix->rows_count = (size_t)row;
    matrix->columns_count = (size_t)column;

    matrix->values = (int **)calloc(row, sizeof(int *));
    if (matrix->values == NULL)
        return ERR_MEMORY_ALLOCATION;

    for (size_t i = 0; i < row; i++)
    {
        // Выделяем память для каждого ряда
        matrix->values[i] = calloc(column, sizeof(int));
        if (matrix->values[i] == NULL)
            return ERR_MEMORY_ALLOCATION;
    }

    return ERR_OK;
}

// Заполнение матрицы из файла
int fill_default_matrix_from_file(FILE *file, matrix_t *matrix)
{
    int el;

    for (size_t i = 0; i < matrix->rows_count; i++)
    {
        for (size_t j = 0; j < matrix->columns_count; j++)
        {
            if (fscanf(file, "%d", &el) != 1)
                return ERR_FILE_INPUT;

            matrix->values[i][j] = el;
        }
    }

    return ERR_OK;
}

// Заполнение матрицы из файла в координатном формате
int fill_coord_matrix_from_file(FILE *file, matrix_t *matrix)
{
    int i, j, el;
    size_t count = 0;

    while (fscanf(file, "%d %d %d", &i, &j, &el) == 3)
    {
        if (i < 0 || (size_t)i > matrix->rows_count)
            return ERR_FILE_INPUT;
        if (j < 0 || (size_t)j > matrix->columns_count)
            return ERR_FILE_INPUT;

        count++;
        matrix->values[i][j] = el;
    }
    if (!feof(file))
        return ERR_FILE_INPUT;

    if (count > matrix->rows_count * matrix->columns_count)
        return ERR_FILE_INPUT;
    return ERR_OK;
}

// Вывод матрицы на экран
void print_matrix(const matrix_t matrix)
{
    for (size_t i = 0; i < matrix.rows_count; i++)
    {
        for (size_t j = 0; j < matrix.columns_count; j++)
        {
            printf("%5d ", matrix.values[i][j]);
        }
        printf("\n");
    }
}

// Освобождение дефолтной матрицы
void free_default_matrix(matrix_t *matrix)
{
    for (size_t i = 0; i < matrix->rows_count; i++)
    {
        if (matrix->values[i])
            free(matrix->values[i]);
    }

    if (matrix->values)
        free(matrix->values);
}

// Рандомное заполнение обычной матрицы
int random_fill_default_matrix(matrix_t *matrix)
{
    int n, m, percentiage, rc = ERR_OK;
    if ((rc = input_integer(&n, "Введите количество строк и столбцов в матрице: ", 0, MAX_SIZE)) != ERR_OK)
        return rc;

    if ((rc = input_integer(&m, "", 0, MAX_SIZE)) != ERR_OK)
        return rc;

    if ((rc = input_integer(&percentiage, "Введите процент заполнения первой матрицы: ", 0, 100)) != ERR_OK)
        return rc;

    matrix->rows_count = (size_t)n;
    matrix->columns_count = (size_t)m;

    if ((rc = create_default_matrix(matrix, matrix->rows_count, matrix->columns_count)))
        return rc;

    srand(time(NULL));
    size_t test_count = 0;
    size_t all_count = 0;
    for (size_t i = 0; i < matrix->rows_count; i++)
    {
        for (size_t j = 0; j < matrix->columns_count; j++)
        {
            if (random_chance(percentiage))
            {
                test_count++;
                matrix->values[i][j] = rand() % 10000;
            }
            all_count++;
        }
    }
    // printf("%zu\n", test_count);
    printf("Заполненность %2.f%%\n", (double)test_count / (double)all_count * 100);

    return rc;
}

// Сложение обычных матриц
int add_matrix_t(matrix_t matrix_1, matrix_t matrix_2, matrix_t *res)
{
    int rc = ERR_OK;

    if (matrix_1.columns_count != matrix_2.columns_count || matrix_1.rows_count != matrix_2.rows_count)
        return ERR_MATRIX_SIZE_NOT_EQ;

    if ((rc = create_default_matrix(res, matrix_1.rows_count, matrix_1.columns_count)) != ERR_OK)
        return rc;

    res->rows_count = matrix_1.rows_count;
    res->columns_count = matrix_1.columns_count;

    for (size_t i = 0; i < res->rows_count; i++)
    {
        for (size_t j = 0; j < res->columns_count; j++)
        {
            res->values[i][j] = matrix_1.values[i][j] + matrix_2.values[i][j];
        }
    }

    return rc;
}
