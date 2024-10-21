#include <stdlib.h>
#include <stdbool.h>
#include "default_matrix.h"
#include "constants.h"
#include "errors.h"
#include "utils.h"

/**
 * @brief Функция для считывания матрицы из файла
 */
int create_default_matrix(matrix_t *matrix, size_t row, size_t column)
{
    matrix->rows_count = (size_t)row;
    matrix->columns_count = (size_t)column;

    matrix->values = (int **)calloc(row, sizeof(int *));

    for (size_t i = 0; i < row; i++)
    {
        // Выделяем память для каждого ряда
        matrix->values[i] = calloc(column, sizeof(int));
    }

    return ERR_OK;
}

int fill_matrix_from_file(FILE *file, matrix_t *matrix)
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

int random_fill_default_matrix(matrix_t *matrix)
{
    int n, m, percentiage, rc = ERR_OK;
    if ((rc = input_integer(&n, "Введите количество строк в первой матрице: ", 0, MAX_SIZE)) != ERR_OK)
        return rc;

    if ((rc = input_integer(&m, "Введите количество столбцов в первой матрице: ", 0, MAX_SIZE)) != ERR_OK)
        return rc;

    if ((rc = input_integer(&percentiage, "Введите процент заполнения первой матрицы: ", 0, 100)) != ERR_OK)
        return rc;

    matrix->rows_count = (size_t)n;
    matrix->columns_count = (size_t)m;

    if ((rc = create_default_matrix(matrix, matrix->rows_count, matrix->columns_count)))
        return rc;

    for (size_t i = 0; i < matrix->rows_count; i++)
    {
        for (size_t j = 0; j < matrix->columns_count; j++)
        {
            if (random_chance(percentiage))
            {
                matrix->values[i][j] = rand() % 10000;
            }
        }
    }

    return rc;
}
