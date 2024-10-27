#include <stdio.h>
#include "csc_matrix.h"
#include "default_matrix.h"
#include <stdlib.h>
#include <string.h>
#include "errors.h"

// Подсчет количества не нулевых символов
static size_t count_non_zero_elements(matrix_t matrix)
{
    size_t count = 0;
    for (size_t i = 0; i < matrix.rows_count; i++)
    {
        for (size_t j = 0; j < matrix.columns_count; j++)
        {
            if (matrix.values[i][j] != 0)
                count++;
        }
    }

    return count;
}

// Конвиртирует обычную матрицу, в csc матрицу
csc_t convert_to_csc(matrix_t matrix)
{
    // print_matrix(*matrix);
    csc_t csc_matrix = {0};
    csc_matrix.rows_count = matrix.rows_count;
    csc_matrix.columns_count = matrix.columns_count;
    csc_matrix.nz_count = count_non_zero_elements(matrix);

    csc_matrix.values = malloc(csc_matrix.nz_count * sizeof(int));
    if (csc_matrix.values == NULL)
    {
        csc_matrix.rc = ERR_MEMORY_ALLOCATION;
        return csc_matrix;
    }

    csc_matrix.row_indices = malloc(csc_matrix.nz_count * sizeof(int));
    if (csc_matrix.row_indices == NULL)
    {
        csc_matrix.rc = ERR_MEMORY_ALLOCATION;
        return csc_matrix;
    }

    csc_matrix.col_ptr = malloc((csc_matrix.columns_count + 1) * sizeof(int));
    if (csc_matrix.col_ptr == NULL)
    {
        csc_matrix.rc = ERR_MEMORY_ALLOCATION;
        return csc_matrix;
    }

    csc_matrix.rc = ERR_OK;

    csc_matrix.col_ptr[0] = 0;
    size_t cur_index = 0;

    for (size_t j = 0; j < matrix.columns_count; j++)
    {
        for (size_t i = 0; i < matrix.rows_count; i++)
        {
            if (matrix.values[i][j] != 0)
            {
                csc_matrix.values[cur_index] = matrix.values[i][j];
                csc_matrix.row_indices[cur_index] = i;
                cur_index++;
            }
        }
        csc_matrix.col_ptr[j + 1] = cur_index;
    }

    return csc_matrix;
}

// Освобождение csc матрицы
void free_csc_matrix(csc_t *matrix)
{
    free(matrix->values);
    free(matrix->col_ptr);
    free(matrix->row_indices);

    memset(matrix, 0, sizeof(*matrix));
}

// Вывод csc матрицы на экран
void print_csc_matrix(const csc_t matrix)
{
    if (matrix.nz_count == 0)
    {
        printf("Матрица - пустая\n");
        return;
    }

    printf("Values\n");
    for (size_t i = 0; i < matrix.nz_count; i++)
    {
        printf("%d ", matrix.values[i]);
    }
    printf("\n");

    printf("Row Indices\n");
    for (size_t i = 0; i < matrix.nz_count; i++)
    {
        printf("%d ", matrix.row_indices[i]);
    }
    printf("\n");

    printf("Column Pointers\n");
    for (size_t i = 0; i <= matrix.columns_count; i++)
    {
        printf("%d ", matrix.col_ptr[i]);
    }
    printf("\n");
}

// Сложение csc матрицы
int sum_csc_matrix(csc_t matrix_1, csc_t matrix_2, csc_t *result)
{
    if (matrix_1.rows_count != matrix_2.rows_count || matrix_1.columns_count != matrix_2.columns_count)
    {
        return ERR_MATRIX_SIZE_NOT_EQ;
    }

    size_t rows = matrix_1.rows_count;
    size_t cols = matrix_1.columns_count;

    // Инициализация результирующей матрицы
    result->rows_count = rows;
    result->columns_count = cols;

    // В худшем максимальное количество ненулевых элементов будет равно сумме ненулевых элементов обеих матриц
    result->nz_count = matrix_1.nz_count + matrix_2.nz_count;
    result->values = (int *)malloc(result->nz_count * sizeof(int));
    if (result->values == NULL)
        return ERR_MEMORY_ALLOCATION;

    result->row_indices = (int *)malloc(result->nz_count * sizeof(int));
    if (result->row_indices == NULL)
        return ERR_MEMORY_ALLOCATION;

    result->col_ptr = (int *)calloc((cols + 1), sizeof(int));
    if (result->col_ptr == NULL)
        return ERR_MEMORY_ALLOCATION;
    result->rc = 0;

    // Суммируем две матрицы
    int pos_result = 0; // Текущая позиция для заполнения в результирующей матрице
    for (size_t j = 0; j < cols; ++j)
    {
        int idx_1 = matrix_1.col_ptr[j];
        int idx_2 = matrix_2.col_ptr[j];

        while (idx_1 < matrix_1.col_ptr[j + 1] || idx_2 < matrix_2.col_ptr[j + 1])
        {
            if (idx_1 < matrix_1.col_ptr[j + 1] && (idx_2 >= matrix_2.col_ptr[j + 1] || matrix_1.row_indices[idx_1] < matrix_2.row_indices[idx_2]))
            {
                // Добавляем элемент из первой матрицы
                result->values[pos_result] = matrix_1.values[idx_1];
                result->row_indices[pos_result] = matrix_1.row_indices[idx_1];
                idx_1++;
            }
            else if (idx_2 < matrix_2.col_ptr[j + 1] && (idx_1 >= matrix_1.col_ptr[j + 1] || matrix_2.row_indices[idx_2] < matrix_1.row_indices[idx_1]))
            {
                // Добавляем элемент из второй матрицы
                result->values[pos_result] = matrix_2.values[idx_2];
                result->row_indices[pos_result] = matrix_2.row_indices[idx_2];
                idx_2++;
            }
            else
            {
                // Элементы на одной строке, суммируем
                result->values[pos_result] = matrix_1.values[idx_1] + matrix_2.values[idx_2];
                result->row_indices[pos_result] = matrix_1.row_indices[idx_1];
                idx_1++;
                idx_2++;
            }
            pos_result++;
        }

        // Обновим указатель на столбцы
        result->col_ptr[j + 1] = pos_result;
    }

    // Обновляем количество ненулевых элементов
    result->nz_count = pos_result;

    return ERR_OK;
}
