#ifndef SCS_MATRIX_H__
#define SCS_MATRIX_H__
#include <stdio.h>

// Структура для хранения разреженной матрицы в формате SCS
typedef struct
{
    int *values;
    int *row_indices;
    int *col_ptr;

    size_t rows_count;
    size_t columns_count;
    size_t nz_count;
} scs_matrix_t;

#endif