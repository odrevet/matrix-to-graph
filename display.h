/**
	@file  display.h
	@author DREVET Olivier 
	@brief Display on screen function
*/

#ifndef DISPLAY_H
#define DISPLAY_H

#include <tigcclib.h>

#include "arrow.h"
#include "trigo.h"
#include "matrix.h"
#include "path.h"
#include "graph.h"

/**
	@brief Display the top menu
	@return The selected menu identifier
*/
short menu_display();

/**
	@brief Display a list of summits (name, location...)
	@param An array of summits
	@param The number of summits in the array
*/
void summit_list(summit *v_summit, int i_nb_summit);

/**
	@brief Display a list of paths (value, ...)
	@param An array of paths
	@param The number of paths in the array
*/
void path_list(const path *v_path, int i_nb_path);

/**
	@brief
	@param
*/
void arrow_draw(point point1, point point2, point point3);

/**
	@brief Draw a graph on screen 
	@param The graph to draw
*/
void graph_draw(const graph *p_graph);

/**
	@brief Draw a line
	@param The source point
	@param The destination point
*/
void line_draw(point pointSource, point pointDest);

/**
	@brief Draw a matrix on screen 
	@param The matrix to be draw
*/
void matrix_draw(matrix *matrice);

/**
	@brief Dislay the dictionnary of precedents
	@param The graph where to check
*/
void dict_prev(const graph *p_graph);

/**
	@brief Dislay the dictionnary of follows
	@param The graph where to check
*/
void dict_next(const graph *p_graph);

/**
	@brief Display a menu to swap two summits
	@param Array of summits 
	@param Number of summit in the array
*/
void summit_swap_coord(summit *v_summit, int i_nb_summit);

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
	@brief Display a menu for rename summits
	@param Summits to preview
*/
void menu_summit_rename(summit *v_summit, int i_nb_summit);

/**
	@brief Display weight of paths on the screen 
	@param array of path to display the weight
	@param number of path in the array
*/
void path_display_weight(path *v_path, int i_nb_path);

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
void MenuDessinFermetureTransitive(matrix *p_matrix, graph *p_graph);



#endif
