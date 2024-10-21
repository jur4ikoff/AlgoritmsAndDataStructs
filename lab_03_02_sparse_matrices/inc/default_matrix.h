#ifndef DEFAULT_MATRIX_H__
#define DEFAULT_MATRIX_H__
#include <stdio.h>

// Пока матрица только целочисленная
typedef struct
{
    size_t rows_count;
    size_t columns_count;
    int **values;
} matrix_t;

void print_matrix(const matrix_t matrix);
int fill_matrix_from_file(FILE *file, matrix_t *matrix);
void free_default_matrix(matrix_t *matrix);
int random_fill_default_matrix(matrix_t *matrix);
int create_default_matrix(matrix_t *matrix, size_t row, size_t column);
int add_matrix_t(matrix_t matrix_1, matrix_t matrix_2, matrix_t *res);
#endif