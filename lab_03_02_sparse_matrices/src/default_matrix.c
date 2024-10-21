#include "default_matrix.h"
#include "constants.h"
#include "errors.h"
#include <stdlib.h>

/**
 * @brief Функция для считывания матрицы из файла
 */
int create_default_matrix(FILE *file, matrix_t *matrix)
{
    int row, column;
    if (fscanf(file, "%d", &row) != 1)
        return ERR_FILE_INPUT;

    if (fscanf(file, "%d", &column) != 1)
        return ERR_FILE_INPUT;

    if (row < 1 || row > MAX_SIZE)
        return ERR_RANGE_MATRIX_SIZE;

    if (column < 1 || column > MAX_SIZE)
        return ERR_RANGE_MATRIX_SIZE;

    matrix->rows_count = (size_t)row;
    matrix->columns_count = (size_t)column;

    matrix->values = (int **)calloc(row, sizeof(int *));

    for (int i = 0; i < row; i++)
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
            printf("%d ", matrix.values[i][j]);
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