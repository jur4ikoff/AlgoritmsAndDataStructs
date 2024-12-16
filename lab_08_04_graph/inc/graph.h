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

// Вывод графа картинкой
int graph_render_open(const char *gp_fname, const char *png_fname);
void generate_graphviz(graph_t *graph, const char *filename);


// Вывод графа в консоль, бфс и дфс обход
void dfs_print_graph(graph_t *graph);
void bfs_print_graph(graph_t *graph);

// Алгоритм бельмана форда
void bellman_ford_alg(graph_t *graph, int start_vertex, int *output);

void find_reachable_vertices(graph_t *graph, int start, int max_distance);
#endif
