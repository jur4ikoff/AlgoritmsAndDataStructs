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

int create_default_matrix(FILE *file, matrix_t *matrix);
void print_matrix(const matrix_t matrix);
int fill_matrix(FILE *file, matrix_t *matrix);
void free_matrix(matrix_t *matrix);

#endif