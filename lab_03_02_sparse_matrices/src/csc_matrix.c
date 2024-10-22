#include <stdio.h>
#include "csc_matrix.h"
#include "default_matrix.h"
#include <stdlib.h>
#include <string.h>
#include "errors.h"

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

void free_csc_matrix(csc_t *matrix)
{
    free(matrix->values);
    free(matrix->col_ptr);
    free(matrix->row_indices);

    memset(matrix, 0, sizeof(*matrix));
}

void print_csc_matrix(csc_t *matrix)
{
    if (matrix->nz_count == 0)
    {
        printf("Матрица - пустая\n");
        return;
    }

    printf("Values\n");
    for (size_t i = 0; i < matrix->nz_count; i++)
    {
        printf("%d ", matrix->values[i]);
    }
    printf("\n");

    printf("Row Indices\n");
    for (size_t i = 0; i < matrix->nz_count; i++)
    {
        printf("%d ", matrix->row_indices[i]);
    }
    printf("\n");

    printf("Column Pointers\n");
    for (size_t i = 0; i <= matrix->columns_count; i++)
    {
        printf("%d ", matrix->col_ptr[i]);
    }
    printf("\n");
}