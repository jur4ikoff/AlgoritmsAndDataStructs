#ifndef UTILS_H__
#define UTILS_H__
#include <stdbool.h>

int input_string(char *string, size_t max_len, char *message);
bool random_chance(int percentage);
int input_integer(int *number, char* message, int low_edge, int max_edge);
int get_matrix_info(FILE *file, int *row, int *column);
#endif