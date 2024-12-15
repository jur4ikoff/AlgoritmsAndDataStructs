/*
ВАРИАНТ 4
Найти все вершины графа, к которым от заданной
вершины можно добраться по пути не длиннее А.
*/

#include "constants.h"
#include "errors.h"
#include <stdio.h>

void print_error_message(int arg)
{
    printf("%s", RED);
    switch (arg)
    {
        case ERR_FILE:
            printf("Ошибка чтения файла\n");
    }
    printf("%s", RESET);
}

void print_guide(void)
{
    printf("Программа считывает граф из файла и ищем все вершины графа, к которым от заданной вершины можно добраться по пути не длиннее А\n");
}

int main(void)
{
    int rc = ERR_OK;
    print_guide();

    return rc;
}
