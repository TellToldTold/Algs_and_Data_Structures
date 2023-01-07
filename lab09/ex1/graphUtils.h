
#ifndef GRAPHUTILS_H
#define GRAPHUTILS_H

#include "graph.h"

extern int graph_bfs_count (graph_t *g, vertex_t *n);
extern int graph_bfs_distance (graph_t *g, vertex_t *n);

void graph_dfs_type (graph_t *g, vertex_t *n, int **types);
int graph_dfs_depth (graph_t *g, vertex_t *n);
int graph_dfs_r_max_path(graph_t *g, vertex_t *n);

#endif
