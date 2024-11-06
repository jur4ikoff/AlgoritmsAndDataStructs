#ifndef CSC_MATRIX_H__
#define CSC_MATRIX_H__
#include <stdio.h>
#include "default_matrix.h"

// Структура для хранения разреженной матрицы в формате CSC
typedef struct
{
    int *values;
    int *row_indices;
    int *col_ptr;

    size_t rows_count;
    size_t columns_count;
    size_t nz_count;

    int rc;
} csc_t;

csc_t convert_to_csc(matrix_t matrix);
void free_csc_matrix(csc_t *matrix);
void print_csc_matrix(const csc_t matrix);
int sum_csc_matrix(csc_t matrix_1, csc_t matrix_2, csc_t *result);
#endif
