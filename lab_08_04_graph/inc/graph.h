#ifndef GRAPH_H__
#define GRAPH_H__

#include <stdio.h>

typedef struct _graph_type_ graph_t;

// Функции выделения и освобождения памяти
graph_t *create_graph(size_t vert_count);
void free_graph(graph_t *graph);

// Загрузка графа из памяти
int load_graph(graph_t **graph, char *filname);

// Служебные функции для работы с графом, как с АТД
int is_graph(graph_t *graph);
int graph_count(graph_t *graph);

// Вывод графа на экран
void show_graph(graph_t *graph, int const *distance);

// Вывод графа в консоль, бфс и дфс обход
void dfs_print_graph(graph_t *graph);
void bfs_print_graph(graph_t *graph);

// Алгоритм бельмана форда
int bellman_ford_alg(graph_t *graph, int start_vertex, int **output);

// Для решения задачи
void find_reachable_vertices(int *distance, int max_distance, size_t vertex_count);
#endif
