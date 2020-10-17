/**
 @file graph.h
 @author DREVET Olivier 
 @brief 
*/

#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>

#include "io.h"
#include "node.h"
#include "edge.h"

/**
 @struct
*/
typedef struct
{
 edge *v_edge;
  node *v_node;
 int i_nb_edge;
 int i_nb_node;
 int i_ray;
} graph;

/**
 @brief
 @param
 @return
*/
void init_all(graph *p_graph, matrix *p_matrix, ESI EsiPtr);

/**
 @brief
 @param
 @return
*/
void free_all(graph *p_graph, matrix *p_matrix);

/**
 @brief Calculate the shortest or the longest edge between two  nodes
 @param a graph
 @todo return an array of integers instead of displaying the result direcly to the screen
*/
void ford_bellman(graph *p_graph);

/**
 @brief
 @param
 @return
*/
void set_edge(matrix *p_matrix, graph *p_graph);

/**
 @brief
 @param
 @return
*/
void  node_move(graph *p_graph);

#endif
