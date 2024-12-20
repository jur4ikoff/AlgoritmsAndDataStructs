#include "time_calc.h"
#include <time.h>
#include <stdio.h>
#include "binary_tree.h"
#include "constants.h"
#include <string.h>
#include <stdlib.h>
#include "errors.h"
#include "task.h"

int calc_inorder(void)
{

    struct timespec start, end;
    char *result = malloc(MAX_STRING_LEN * sizeof(char));
    FILE *file = fopen("./data/linear_15.txt", "r");
    if (file == NULL)
    {
        free(result);
        return ERR_FILE;
    }
    fgets(result, MAX_STRING_LEN - 1, file);
    fclose(file);

    char *newline = strchr(result, '\n');
    if (newline)
        *newline = 0;

    tree_t *tree = NULL;
    convert_string_to_tree(&tree, result);
    if (!tree)
    {
        tree_free(tree);
        free(result);
        return ERR_STRING;
    }

    float sum = 0.0;
    int count = 20;
    for (int i = 0; i < count; i++)
    {
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        inorder_traversal(tree, 1, 0);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        float time_inf = (end.tv_sec - start.tv_sec) * 1e6f + (end.tv_nsec - start.tv_nsec) / 1e3f;
        sum += time_inf;
    }
    printf("%sВремя инфиксного обхода: %.2f мкс\n%s", GREEN, (float)(sum / (float)count), RESET);
    return ERR_OK;
}
