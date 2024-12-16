#define _GNU_SOURCE

#include "graph.h"
#include "constants.h"
#include "errors.h"
#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define INF INT_MAX // Используем для обозначения бесконечности

struct _graph_type_
{
    size_t count_vertices; // Количество вершин
    int **matrix;          // Матрица смежности
};

/**
 * @brief Функция для инициализации структурной переменной типа graph_t
 * @param[in] vert_count Количество вершин
 */
graph_t *create_graph(size_t vert_count)
{
    graph_t *graph = malloc(sizeof(graph_t));
    if (graph == NULL)
        return NULL;

    graph->count_vertices = vert_count;
    graph->matrix = malloc(sizeof(int) * graph->count_vertices);
    if (graph->matrix == NULL)
        return NULL;

    for (size_t i = 0; i < vert_count; i++)
    {
        graph->matrix[i] = calloc(graph->count_vertices, sizeof(int));
    }

    return graph;
}

/**
 * @brief Функция для добавление веса в матрицу смежностей
 * @param[in] graph Указатель наструктурную переменную
 * @param[in] src Исходная вершина
 * @param[in] dest Конечная вершина
 * @param[in] weight Вес ребра
 * @param[out] graph Граф с изменной матрицей смежностей
 */
static void add_edge(graph_t *graph, size_t src, size_t dest, size_t weight)
{
    graph->matrix[src][dest] = weight;
}

/**
 * @brief Освобождение переменной типа graph_t
 * @param[in] graph
 */
void free_graph(graph_t *graph)
{
    if (graph)
    {
        for (size_t i = 0; i < graph->count_vertices; i++)
        {
            free(graph->matrix[i]);
        }
        free(graph->matrix);
    }
    free(graph);
}

/**
 * @brief Функция возвращает 0, если количество вершин меньше 2
 */
int is_graph(graph_t *graph)
{
    return (graph->count_vertices < 2) ? ERR_EMPTY : ERR_OK;
}

/**
 * @brief Функция для чтения графа из файла
 * @param[in] graph Структурная переменная типа graph_t для записи
 * @param filename Название файла
 */
int load_graph(graph_t **graph, char *filname)
{
    FILE *file = fopen(filname, "r");
    if (file == NULL)
    {
        return ERR_FILE;
    }

    size_t verts = 0;
    if (fscanf(file, "%zu", &verts) != 1)
    {
        fclose(file);
        return ERR_EDGE;
    }

    if (verts > MAX_GRAPH_SIZE)
    {
        fclose(file);
        return ERR_EDGE;
    }
    *graph = create_graph(verts);
    if (*graph == NULL)
    {
        fclose(file);
        return ERR_MEMORY;
    }

    for (size_t i = 0; i < verts; i++)
    {
        for (size_t j = 0; j < verts; j++)
        {
            int weight;
            if (fscanf(file, "%d", &weight) != 1)
            {
                fclose(file);
                free_graph(*graph);
                return ERR_EDGE;
            }
            add_edge(*graph, j, i, weight);
        }
    }
    fclose(file);

    return ERR_OK;
}

int graph_render_open(const char *gp_fname, const char *png_fname)
{
    pid_t pid = fork();
    if (pid == -1)
        return ERR_FORK;

    if (pid == 0)
    {
        execlp("dot", "dot", "-Tpng", gp_fname, "-o", png_fname, NULL);
        perror("execlp");
        _exit(EXIT_FAILURE);
    }
    else
    {
        int ret_code;
        wait(&ret_code);

        if (WEXITSTATUS(ret_code) != 0)
            return ERR_FORK;
    }

    pid = fork();
    if (pid == -1)
        return ERR_FORK;

    if (pid == 0)
    {
        int new_stderr = open("/dev/null", O_WRONLY);
        if (new_stderr < 0)
            return ERR_FORK;

        dup2(new_stderr, STDERR_FILENO);

        execlp("open", "open", png_fname, NULL);
        perror("execlp");
        close(new_stderr);
        _exit(EXIT_FAILURE);
    }
    else
    {
        int ret_code;
        wait(&ret_code);

        if (WEXITSTATUS(ret_code) != 0)
            return ERR_FORK;
    }

    return ERR_OK;
}

// Функция для генерации исходного текста для Graphviz
void generate_graphviz(graph_t *graph, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        perror("Не удалось открыть файл");
        return;
    }

    fprintf(file, "digraph G {\n");

    for (size_t i = 0; i < graph->count_vertices; i++)
        for (size_t j = 0; j < graph->count_vertices; j++)
            if (graph->matrix[i][j] != INF && graph->matrix[i][j] != 0)
                fprintf(file, "    %zu -> %zu [label=\"%d\"];\n", i, j, graph->matrix[i][j]);

    // Выделяем лучший город
    // fprintf(file, "    %zu [style=filled, fillcolor=yellow];\n", best_city);
    fprintf(file, "}\n");

    fclose(file);
}

int graph_count(graph_t *graph)
{
    if (!graph)
        return 0;
    return graph->count_vertices;
}

/**
 * @brief Алгоритм Беллмана-форда
 * @param[in] graph Указатель на граф
 * @param[in] start_vertex Вершнина начала
 * @param[in] output Массив для записи результата
 */
void bellman_ford_alg(graph_t *graph, int start_vertex, int *output)
{
}

/**
 * @brief Функция определяет в какие вершины можно попасть по пути не длиннее max_distance
 *
Сделать Алгоритм Беллмана-Форда предназначен для решения задачи поиска кратчайшего пути на граф
 */
void find_reachable_vertices(graph_t *graph, int start, int max_distance)
{
    bool visited[MAX_GRAPH_SIZE] = { false };
    int distance[MAX_GRAPH_SIZE] = { 0 };

    // Инициализируем очередь для BFS
    int queue[MAX_GRAPH_SIZE];
    int front = 0, rear = 0;

    visited[start] = true;
    queue[rear++] = start;

    printf("Вершины, доступные от %d с расстоянием не более %d:\n", start, max_distance);

    while (front < rear)
    {
        int current = queue[front++];

        // Если текущая вершина находится на допустимом расстоянии, выводим её
        printf("%d %d\n", current, distance[current]);
        if (distance[current] <= max_distance)
        {
            ;
            // printf("%d ", current);
        }

        // Исследуем соседние вершины
        for (size_t i = 0; i < graph->count_vertices; i++)
        {
            if (graph->matrix[current][i] && !visited[i])
            {
                visited[i] = true;
                queue[rear++] = i;
                // distance[i] = distance[current] + 1;
                distance[i] = distance[current] + graph->matrix[current][i];
            }
        }
    }
    printf("\n");
}

/**
 * @brief Функция обход в глубину
 * @param[in] vertex Текущая вершина
 * @param[in] visited Массив, посещенных вершин
 * @param[in] graph Указатель на граф
 */
static void dfs(int vertex, int *visited, graph_t *graph)
{
    visited[vertex] = 1;
    printf("%d ", vertex);

    for (size_t i = 0; i < graph->count_vertices; i++)
    {
        if (graph->matrix[vertex][i] != 0 && !visited[i])
            dfs(i, visited, graph);
    }
}

/**
 * @brief Функция вывода на экран графа, используя поиск в глубину
 * @param[in] graph Указатель на граф
 */
void dfs_print_graph(graph_t *graph)
{
    if (graph == NULL)
        return;

    int *visited = calloc(graph->count_vertices + 1, sizeof(int));
    if (!visited)
        return;

    printf("Обход графа в глубину:\n");
    // 0 - Начальная вершина
    dfs(0, visited, graph);
    printf("\n");

    free(visited);
}

/**
 * @brief Функция вывода на экран графа, используя поиск в ширину
 * @param[in] graph Указатель на граф
 */
void bfs_print_graph(graph_t *graph)
{
    if (graph == NULL)
        return;

    int *visited = calloc(graph->count_vertices + 1, sizeof(int));
    if (!visited)
        return;

    int queue[graph->count_vertices];
    int front = 0, rear = 0;

    int start_vertex = 0;
    visited[start_vertex] = 1;
    queue[rear++] = start_vertex;

    printf("Обход графа в ширину:\n");
    while (front < rear)
    {
        int current = queue[front++];
        printf("%d ", current);

        for (size_t i = 0; i < graph->count_vertices; i++)
        {
            if (graph->matrix[current][i] && !visited[i])
            {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }

    printf("\n");
    free(visited);
}
