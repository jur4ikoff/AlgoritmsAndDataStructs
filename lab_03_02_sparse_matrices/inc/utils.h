#ifndef UTILS_H__
#define UTILS_H__
#include <stdbool.h>

#define MAX_WIDTH 1024

int input_string(char *string, size_t max_len, char *message);
bool random_chance(int percentage);
int input_integer(int *number, char* message, int low_edge, int max_edge);
int get_matrix_info(FILE *file, int *row, int *column);
void *max(void *value_1, void *value_2, size_t width);
#endif