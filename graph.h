/**
	@file graph.h
	@author DREVET Olivier 
	@brief 
*/

#ifndef GRAPH_H
#define GRAPH_H

#include "io.h"
#include "summit.h"
#include "path.h" 

/**
	@struct
*/
typedef struct{
	path *v_path;
	summit *v_summit;
	int i_nb_path;
	int i_nb_summit;
	int i_ray;
}graph;

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
	@brief Calculate the shortest or the longest path between two summits
	@param a graph
	@todo return an array of integers instead of displaying the result direcly to the screen
*/
void ford_bellman(graph *p_graph);

/**
	@brief
	@param
	@return
*/
void set_path(matrix *p_matrix, graph *p_graph);

/**
	@brief
	@param
	@return
*/
void summit_move(graph *p_graph);


#endif
