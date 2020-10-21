#ifndef DISPLAY_H
#define DISPLAY_H

#include <tigcclib.h>

#include "TI/trigo.h"
#include "TI/draw.h"
#include "matrix.h"
#include "edge.h"
#include "graph.h"
#include "print.h"

void arrow_draw(point point1, point point2, point point3);

/**
 @brief Do an enclosure on a matrix(see the matematic glossary for more details)
 @param [in, out] The matrix to enclose
*/
void menu_enclosure(matrix *p_matrix);

/**
 @brief Display a menu to perfome a power operation on a matrix
 @param The matrix to preview
*/
void menu_pow(matrix *p_matrix);

/**
 @brief Display a menu for rename  nodes
 @param  nodes to preview
*/
void menu_node_rename( node *v_node, int i_nb_node);

/**
 @brief Temporize the display
 @param Time to wait in miliseconds
*/
void temporize(short int iTime);

/**
 @brief Display a menu to perform en encolsure 
 @param The matrix to check
 @param The graph to check
*/
void draw_transitive_closure(matrix *p_matrix, graph *p_graph);

#endif
