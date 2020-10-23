#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include <limits.h>

#include "node.h"
#include "edge.h"

typedef struct
{
    edge *v_edge;
    node *v_node;
    int i_nb_edge;
    int i_nb_node;
#ifdef __m68k__
    int i_ray;
#endif
} graph;

void graph_init(graph *p_graph, matrix *p_matrix);

void set_edge(matrix *p_matrix, graph *p_graph);

void graph_free(graph *p_graph);

/**
 @brief find the shortest or the longest path between two nodes
*/
void ford_bellman(graph *p_graph);

#endif
