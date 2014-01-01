/**
	@file summit.h
	@author DREVET Olivier 
	@brief 
*/

#ifndef SUMMIT_H
#define SUMMIT_H

#include <tigcclib.h>

#include "point.h"
#include "matrix.h"

/**
	@struct a data structure representing a summit of a graph
	@param the coordinat of the summit
	@param the level of the summit (see mathematic glossary for more details)
	@param the value associated with the summit
	@param the name of the summit
*/
typedef struct{
	point coord;
	int i_level;
	int i_value;
	char sz_name[5];
}summit;

/**
	@brief Rename all summit passed 
	@param Summit to be renamed
	@param The new prefix (name)
	@param The number of summits in the vector (the first param)
	@note this function is called 'prefix', because it rename summit with a prefix_value format, where prefix is the second param and value a sequantial number
*/
void summit_prefix(summit *v_summit, char szPrefi_x[5], int i_nb_summit);

/**
	@brief
	@param
	@return
*/
void summit_rename(summit *UnSommet, char szNouveauNom[5]);

/**
	@brief
	@param
	@return
*/
void summit_swap(summit *UnSommetA, summit *UnSommetB);

/**
	@brief Set the level of each summit 
	@param [in]The matrix where to check
	@param [in, out] The array of summit 
	@note The number of summit in the array is not required because it is calculated from the matrix size
	@return 1 if ok 
					0 if the matrix have a loop
*/
char set_level(matrix *p_matrix, summit *v_summit);

/**
	@brief
	@param
	@return
*/
int count_level(summit *v_summit, int i_level, int i_nb_summit);

/**
	@brief
	@param
	@return
*/
void sort_by_level(summit *v_summit, int i_nb_summit);

/**
	@brief
	@param
	@return
*/
char all_level_checked(const matrix *matrice, const summit *v_summit);

/**
	@brief
	@param
	@return
*/
void summit_list(summit *v_summit, int i_nb_summit);

#endif
