#ifndef PRINT_H
#define PRINT_H

#include "matrix.h"
#include "edge.h"
#include "graph.h"

void print_edge_list(const edge *v_edge, int i_nb_edge);
void print_node_list(node *v_node, int i_nb_node);
void node_list(node *v_node, int i_nb_node);
void print_matrix(matrix *p_matrix);
void print_dict_prev(const graph *p_graph);
void print_dict_next(const graph *p_graph);
#endif
