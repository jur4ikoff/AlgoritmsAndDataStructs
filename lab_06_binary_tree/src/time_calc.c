#include "time_calc.h"
#include "binary_tree.h"
#include "constants.h"
#include "errors.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int input_string_from_file(char *filename, char *string)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        return ERR_FILE;
    }
    fgets(string, MAX_STRING_LEN - 1, file);

    char *newline = strchr(string, '\n');
    if (newline)
        *newline = 0;
    fclose(file);
    return ERR_OK;
}

int calc_inorder(char *filename, float *time)
{
    struct timespec start, end;
    char *result = malloc(MAX_STRING_LEN * sizeof(char));
    int rc = ERR_OK;
    if ((rc = input_string_from_file(filename, result)) != ERR_OK)
    {
        free(result);
        return rc;
    }

    tree_t *tree = NULL;
    convert_string_to_tree(&tree, result);
    if (!tree)
    {
        tree_free(tree);
        free(result);
        return ERR_STRING;
    }
    // tree_in_picture(tree);

    float sum = 0.0;
    int count = 30;
    for (int i = 0; i < count; i++)
    {
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        inorder_traversal(tree, 1, 0);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        float time_inf = (end.tv_sec - start.tv_sec) * 1e6f + (end.tv_nsec - start.tv_nsec) / 1e3f;
        sum += time_inf;
    }

    *time = sum / (float)count;
    return ERR_OK;
}

int calculte_search_time(char *filename, float *time, size_t exp_count)
{
    struct timespec start, end;
    float time_del = 0.0;
    char *result = malloc(MAX_STRING_LEN * sizeof(char));
    int rc = ERR_OK;
    if ((rc = input_string_from_file(filename, result)) != ERR_OK)
    {
        free(result);
        return rc;
    }

    tree_t *tree = NULL;
    convert_string_to_tree(&tree, result);
    if (!tree)
    {
        tree_free(tree);
        free(result);
        return ERR_STRING;
    }

    size_t count = 0;
    for (size_t i = 0; i < exp_count; i++)
    {
        char *ptr = result;
        while (*ptr)
        {
            data_t data = *ptr;
            clock_gettime(CLOCK_MONOTONIC_RAW, &start);
            tree_search(tree, data);
            clock_gettime(CLOCK_MONOTONIC_RAW, &end);
            time_del += (end.tv_sec - start.tv_sec) * 1e6f + (end.tv_nsec - start.tv_nsec) / 1e3f;
            count++;
            ptr++;
        }
    }

    free(result);
    *time = time_del / count;
    return ERR_OK;
}
