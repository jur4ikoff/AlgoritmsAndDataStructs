/*
ВАРИАНТ 4
Найти все вершины графа, к которым от заданной
вершины можно добраться по пути не длиннее А.
*/

#define _GNU_SOURCE

#include "constants.h"
#include "errors.h"
#include "graph.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int input_string(char **string, FILE *file, ssize_t max)
{
    ssize_t read;
    size_t len;
    if ((read = getline(string, &len, file)) == -1)
        return ERR_STRING;

    if (read > max)
    {
        return ERR_STRING;
    }

    char *newline = strchr(*string, '\n');
    if (!newline)
        return ERR_STRING;
    *newline = 0;

    if (strlen(*string) < 1)
        return ERR_STRING;

    return ERR_OK;
}

void print_error_message(int arg)
{
    printf("%s", RED);
    switch (arg)
    {
        case ERR_FILE:
            printf("Ошибка чтения файла\n");
            break;
        case ERR_STRING:
            printf("Ошибка при вводе строки\n");
            break;
        case ERR_MEMORY:
            printf("Ошибка при работе с памятью\n");
            break;
        case ERR_EDGE:
            printf("Ошибка при считывании матрицы смежности из файла\n");
            break;
        case ERR_EMPTY:
            printf("Ошибка. Граф пустой\n");
            break;
        case ERR_INT:
            printf("Ошибка ввода числа\n");
            break;
        case ERR_FIND:
            printf("Ошибка во время определения кратчайшего пути\n");
            break;
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
    printf(">>Введите путь к файлу: ");
    char *filepath = NULL;
    if ((rc = input_string(&filepath, stdin, MAX_PATH_LEN)) != ERR_OK)
    {
        free(filepath);
        print_error_message(rc);
        return rc;
    }

    graph_t *graph = NULL;
    if ((rc = load_graph(&graph, filepath)) != ERR_OK)
    {
        free_graph(graph);
        print_error_message(rc);
        return rc;
    }
    free(filepath);

    if (is_graph(graph) == ERR_EMPTY)
    {
        free_graph(graph);
        print_error_message(ERR_EMPTY);
        return ERR_EMPTY;
    }

    int max_dist = 0, start_vertex = 0;
    printf(">>Введите вершину старта: ");
    if (scanf("%d", &start_vertex) != 1)
    {
        free_graph(graph);
        print_error_message(ERR_INT);
        return ERR_INT;
    }

    printf(">>Введите расстояние A: ");
    if (scanf("%d", &max_dist) != 1)
    {
        free_graph(graph);
        print_error_message(ERR_INT);
        return ERR_INT;
    }
    fgetc(stdin);

    dfs_print_graph(graph);
    bfs_print_graph(graph);

    // Получаем список вершин с расстоянием до них
    int *dist = NULL;
    if ((rc = bellman_ford_alg(graph, start_vertex, &dist)) != ERR_OK)
    {
        free(dist);
        free_graph(graph);
        print_error_message(rc);
        return rc;
    }

    printf("\nРасстояние от вершины %d до\n", start_vertex);
    for (size_t i = 0; (int)i < graph_count(graph); i++)
    {
        if ((int)i == start_vertex)
            continue;
        if (dist[i] != INT_MAX)
            printf("-вершины %zu - %d\n", i, dist[i]);
        else
            printf("-вершины %zu не существует\n", i);
    }

    // Оставляем в массиве только те вершины, то которых можно добраться
    find_reachable_vertices(dist, max_dist, (int)graph_count(graph));
    printf("%sВершины, до которых расстояние от вершины %d меньше %d: ", GREEN, start_vertex, max_dist);
    for (size_t i = 0; (int)i < graph_count(graph); i++)
    {
        if (dist[i] < INT_MAX)
        {
            printf("%zu ", i);
        }

    }
    printf("%s\n", RESET);
    
    show_graph(graph, dist);

    free(dist);
    free_graph(graph);
    return rc;
}
