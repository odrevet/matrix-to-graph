#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <stdio.h>

/**
 @struct matrix
 @note this is a squared matrix
 @todo renamme this struct squared_matrix to make later an another matrix struct
*/
typedef struct
{
 int i_size;
 int **ppi_data;
} matrix;

/**
 @brief Allocat memory to a matrix
 @param [in, out] Matrix to be allocated
 @note The i_size of the matrix must be set. 
 @todo this function should be more generic, and accept non square matrix
*/
void matrix_malloc(matrix *p_matrix);

/**
 @brief Free a matrix
 @param [out] Matrix to be un-allocated
 @todo this function should be more generic, and accept non square matrix
*/
void matrix_free(matrix *p_matrix);

/**
 @brief Addition of matrix
 @param a matrix
 @param a matrix 
 @param the result matrix
*/
void matrix_add(const matrix *MatriceA, const matrix *MatriceB, matrix *MatriceRes);

/**
 @brief product of matrix
 @param a matrix
 @param a matrix 
 @param the result matrix
 @note the two matrix to multiply must have the same size
 @todo this function should be more generic, and accept non square matrix
 @return 1 if sucess
     0 if the matrix have not the same size
     
*/
char matrix_product(const matrix *A, const matrix *B, matrix *Z);

/**
 @brief duplicate a matrix
 @param the matrix to duplicate
 @param the duplicated matrix
 @note this function does not allocat memory, you must pass a matrix allocated by yourself or with matrix_malloc

*/
void matrix_copy(const matrix *MatriceOrig, matrix *MatriceDest);

/**
 @brief Fill the matrix of zero at the specified line
 @param the matrix to be filled
 @param the line where to fill with zero
*/
void matrix_zero_at_line(matrix *p_matrix, int iLigne);

/**
 @brief Fill a matriw with zero
 @param the matrix to be filled
 @note you can use this function to initialize a matrix or reset values
*/
void matrix_zero(matrix *p_matrix);

/**
 @brief Check if all elements of a matrix is at zero
 @param The matrix to be checked
 @return 1 if the matrix is full of zeros or 0 if it is not
*/
char matrix_is_zero(matrix *p_matrix);

/**
 @brief Operation of power applied to matrix
 @param theleft operand matrix
 @param the power to elevat the matrix
 @param the result matrix
 @note this function does not allocat memory, you must pass a matrix allocated by yourself or with matrix_malloc
*/
void matrix_pow(const matrix *p_matrix, int Puissance, matrix *MatriceRes);

/**
 @brief Perform an transiftive encolsure
 @param the matrix to do the encolsure
 @param the result matrix
 @note this function does not allocat memory, you must pass a matrix allocated by yourself or with matrix_malloc
 @todo this is a graph-specialized function and it must be moved in a separated file
*/
void matrix_colsure(const matrix *p_matrix, matrix *MatriceRes);

/**
 @brief change a common matrix into a binary matrix. 
      It mean that every non-zero elemnt will be 1 
      and al zero elemnt will stay 0 
   
     example : if a matrix is 
     [0, 2]
     [4, 1]
     
     after a call, it will be 
     
     [0, 1]
     [1, 1]
     
 @param [in, out] The matrix to be binarized
*/
void matrix_bin(matrix *p_matrix);

/**
 @brief count the numbers of edge in a matrix
 @param the matrix where to count
 @return the number of edge
 @todo this is a graph-specialized function and it must be moved in a separated file
*/
int matrix_count_edge(matrix *p_matrix);

/**
 @brief Check if the matrix have at least one next at the specified line
 @param The matrix to check
 @param The line where to check
 @return 0 if has next and 1 if have not next
 @todo This is a graph-specialized function and it must be moved in a separated file
 @todo Reverse return value
*/
char has_next(const matrix *p_matrix, int iLigne);

/**
 @brief Check if the matrix have at least one next at the specified collumn
 @param The matrix to check
 @param The collumn where to check
 @return 0 if has next and 1 if have not next
 @todo This is a graph-specialized function and it must be moved in a separated file
 @todo Reverse return value
*/
char has_prev(const matrix *p_matrix, int iColonne);

/**
 @brief Check if the graph product from a matrix will have loop
 @param The matrix to ckeck
 @return 1 if the is a loop and 
 @todo This is a graph-specialized function and it must be moved in a separated file
*/
char has_loop(const matrix *matrice);

#endif
