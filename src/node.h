#ifndef NODE_H
#define NODE_H

#ifdef __m68k__
#include <tigcclib.h>
#endif
#include <string.h>

#ifdef __m68k__
#include "TI/point.h"
#endif
#include "matrix.h"

/**
 @struct a data structure representing a  node of a graph
 @param the coordinat of the  node
 @param the level of the  node (see mathematic glossary for more details)
 @param the value associated with the  node
 @param the name of the  node
*/
typedef struct
{
#ifdef __m68k__
    point coord;
#endif
    int i_level;
    int i_value;
    char sz_name[5];
} node;

/**
 @brief Rename given nodes with a prefix and an index
 @param  nodes to be renamed
 @param The new prefix (name)
 @param The number of  nodes in the vector (the first param)
*/
void node_prefix(node *v_node, char szPrefix[5], int i_nb_node);

void node_rename(node *p_node, char sz_name[5]);

/**
 @brief Set the level of each  node 
 @param [in]The matrix where to check
 @param [in, out] The array of  node 
 @note The number of  node in the array is not required because it is calculated from the matrix size. 
The given matrix must no have loop
 @return 1 if no error, 0 otherwise
*/
char set_level(matrix *p_matrix, node *v_node);

int count_level(node *v_node, int i_level, int i_nb_node);

void sort_by_level(node *v_node, int i_nb_node);

char all_level_checked(const matrix *matrice, const node *v_node);

#endif
