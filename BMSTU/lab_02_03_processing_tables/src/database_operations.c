#include "database_operations.h"
#include <stdio.h>
#include "errors.h"
#include "constants.h"
#include <string.h>

int database_open(FILE **file, char *filename, char *mode)
{
    *file = fopen(filename, mode);

    if (*file == NULL)
        return ERR_FILENAME;

    return ERR_OK;
}

int database_choose_name(char *string)
{
    FILE *file;
    int rc;

    if (strlen(string) > MAX_PATH_LEN)
        return ERR_STRING_OVERFLOW;

    /*char *newline = strchr(string, '\n');
    if (!newline)
        return ERR_STRING_OVERFLOW;
    *newline = '\0';*/

    // Проверка файла на существование
    if ((rc = database_open(&file, string, "r")) != ERR_OK)
        return rc;
    fclose(file);

    return ERR_OK;
}

int database_count_rows(FILE *FILENAME)
{
    int count = 0;
}