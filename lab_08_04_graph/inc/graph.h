#ifndef GRAPH_H__
#define GRAPH_H__

#include <stdio.h>

typedef struct _graph_type_ graph_t;


// Функции выделения и освобождения памяти
graph_t *create_graph(size_t vert_count);
void free_graph(graph_t *graph);
int load_graph(graph_t **graph, char *filname);

int is_graph(graph_t *graph);
int graph_count(graph_t *graph);

int graph_render_open(const char *gp_fname, const char *png_fname);
void generate_graphviz(graph_t *graph, const char *filename);

void find_reachable_vertices(graph_t *graph, int start, int max_distance);
#endif
